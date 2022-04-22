#include "GPU.h"
using namespace omnetpp;

static std::unordered_map<cModule*, int> rank_manager;
static std::mutex _mtx;

Define_Module(GPU);
GPU::GPU() :
		cnt_epoch(0) {
}
GPU::~GPU() {

}

int GPU::get_rank() {
	return rank;
}
int GPU::get_localRank() {
	return local_rank;
}
int GPU::numInitStages() const {
	return 4;
}

void GPU::initialize(int stage) {
	switch (stage) {
	case 0: {
		std::string profile_file = par("profile_file");
		int num_layers = par("num_layers_per_gpu");
		num_acc = par("num_acc");
		all_epochs = par("epochs");

		model = std::make_shared<Model>(profile_file, num_layers);

		for (int i = 0; i < model->get_ops_size(); ++i) {
			grad_acc[i] = 0;
		}

		local_size = gate("switch_port$o")->getNextGate()->getVectorSize() - 1;
		local_rank = gate("switch_port$o")->getNextGate()->getIndex(); //pcie switch �еĶ˿�����
		cModule *fa = getParentModule();
		{
			std::lock_guard<std::mutex> lck(_mtx);
			if (rank_manager.count(fa)) {
				rank = rank_manager[fa];
			} else {
				rank_manager[fa] = unique_id();
				rank = rank_manager[fa];
			}
		}

		break;
	}
	case 1: {
		{
			cModule *m = getParentModule();
			num_switchs =
					m->getParentModule()->getSubmodule("switchs", 0)->getVectorSize();
			world_size =
					m->getParentModule()->getSubmodule("switchs", 0)->gateSize(
							"ports");

			int idx = m->getIndex();
			world_idx = idx;
			if (idx < world_size) {
				down_rank = -1;
			} else {
				down_rank =
						check_and_cast<GPU*>(
								m->gate("down_port$o")->getNextGate()->getOwnerModule()->getSubmodule(
										"host_gpus", 0))->get_rank();
			}

			if (idx / world_size == num_switchs - 1) {
				up_rank = -1;
			} else {
				up_rank =
						check_and_cast<GPU*>(
								m->gate("up_port$o")->getNextGate()->getOwnerModule()->getSubmodule(
										"host_gpus", 0))->get_rank();
			}
		}

		size = rank_manager.size();
		int d = gateSize("nvlink_port");
		for (int i = 0; i < d; ++i) {
			cModule *m =
					gate("nvlink_port$o", i)->getNextGate()->getOwnerModule();
			GPU *g = check_and_cast<GPU*>(m);
			router[std::make_tuple(g->get_localRank(), g->get_rank())] = i;
		}
		break;
	}
	case 2: {
		for (int i = 0; i < model->get_ops_size(); ++i) {
			allreduceManager.push_back(
					std::make_pair(false,
							OpAllReduceManager(local_rank, rank, local_size,
									world_size, model->get_backward_op(i).nb,
									i)));
		}

		if (world_idx < world_size) {
			for (int i = 0; i < num_acc; ++i) {
				scheduleAt(simTime(),
						createMessage("start training",
								SimPacketType::FORWARD_STARTED,
								std::make_tuple(local_rank, rank)));
			}
		}

		for (int i = 0; i < model->get_ops_size(); ++i) {
			EV << model->get_backward_op(i).r_finished_time << "\n";
		}
		break;
	}
	case 3: {
		cModule *fa = getParentModule();
		OCSSwitch *sw = check_and_cast<OCSSwitch*>(
				fa->gate("port$o")->getNextGate()->getOwnerModule());
		const auto mp = sw->router;
		for (int i = 0; i < mp.size(); ++i) {
			world_ranks.push_back(-1);
		}
		for (auto it = mp.begin(); it != mp.end(); ++it) {
			world_ranks[it->second] = it->first;
		}

		for (auto &x : allreduceManager) {
			x.second.build(world_ranks);
		}
		break;
	}
	}
}
//�ڵ���ģ�Ͳ��У��ڵ�����ݲ���
void GPU::handleMessage(cMessage *msg) {
	if (wait_queue.count(msg)) {
		sendRoute(msg);
		return;
	}

	SimPacket *pkg = check_and_cast<SimPacket*>(msg);
	///forward
//	EV << "opId:" << pkg->getOpId() << "\n";
	if (pkg->getKind() == SimPacketType::FORWARD_STARTED) {
		if (access_st.empty()) {
			//��ÿ���Ȩ
			access_st.insert(AccessType::FORWARD);
			scheduleAtSelf(simTime() + model->get_forward_time(),
					createMessage("start training",
							SimPacketType::FORWARD_FINISHED,
							std::make_tuple(local_rank, rank)));
			free(pkg);
		} else {
			msg_queue.push_back(pkg);
		}
	} else if (pkg->getKind() == SimPacketType::FORWARD_FINISHED) {
		//�ͷ�gpu����Ȩ
		if (!access_st.count(AccessType::FORWARD)) {
			throw "forward access Error!";
		}
		access_st.erase(AccessType::FORWARD);
		//���ݸ���һ�� or ���򴫲�
		if (world_idx / world_size == num_switchs - 1) { //���һ��
			cMessage *tmp = createMessage("start backward",
					SimPacketType::BACKWARD_STARTED,
					std::make_tuple(local_rank, rank));
			SimPacket *pkg_tmp = check_and_cast<SimPacket*>(tmp);
			msg_queue.push_back(pkg_tmp);
//			scheduleAtSelf(simTime() + model->get_cal_loss_time(),
//					createMessage("start backward",
//							ECSSimPacketType::BACKWARD_STARTED,
//							std::make_tuple(local_rank, rank)));
			free(pkg);
		} else { //���ݸ���һ��
//			EV << "next_layer*******\n";
			sendRoute(
					createMessage("forward", SimPacketType::FORWARD_STARTED,
							std::make_tuple(local_rank, up_rank),
							model->get_forward_nb()),
					model->get_send_latency());
			free(pkg);
		}
	} else if (pkg->getKind() == SimPacketType::BACKWARD_STARTED) {
		if (access_st.empty()) {
			//��ÿ���Ȩ
			access_st.insert(AccessType::BACKWARD);
			for (int i = 0; i < model->get_ops_size(); ++i) {
				const auto &op = model->get_backward_op(i);
				scheduleAtSelf(simTime() + op.r_finished_time,
						createMessage("backward op finished",
								SimPacketType::BACKWARD_OP_FINISHED,
								std::make_tuple(local_rank, rank), 0, i));
				if (i == model->get_ops_size() - 1) {
					scheduleAtSelf(simTime() + op.r_finished_time,
							createMessage("backward  finished",
									SimPacketType::BACKWARD_FINISHED,
									std::make_tuple(local_rank, rank), 0, 0));
				}
			}
			free(pkg);
		} else {
			msg_queue.push_back(pkg);
		}
	} else if (pkg->getKind() == SimPacketType::BACKWARD_OP_FINISHED) {
		if (!access_st.count(AccessType::BACKWARD)) {
			throw "this not has backward access!!!!";
		}
		int opId = pkg->getOpId();
		grad_acc[opId] += 1;
		EV << "(" << rank << "," << local_rank << ")" << "  opId:"
					<< pkg->getOpId() << " grad_acc:" << grad_acc[opId] << "\n";
		if (grad_acc[opId] == num_acc) {
//			access_st.insert(AccessType::ALLREDUCE);
			scheduleAtSelf(simTime(),
					createMessage("allreduce start",
							SimPacketType::ALLREDUCE_STARTED,
							std::make_tuple(local_rank, rank), 0, opId));
		}
		free(pkg);
	} else if (pkg->getKind() == SimPacketType::BACKWARD_FINISHED) {
		access_st.erase(AccessType::BACKWARD);
		if (world_idx < world_size) {
//			scheduleAtSelf(simTime(),
//					createMessage("start training",
//							ECSSimPacketType::FORWARD_STARTED,
//							std::make_tuple(local_rank, rank)));
		} else {
			sendRoute(
					createMessage("backward", SimPacketType::BACKWARD_STARTED,
							std::make_tuple(local_rank, down_rank),
							model->get_backward_nb()),
					model->get_send_latency());
		}
		free(pkg);
	} else if (pkg->getKind() == SimPacketType::ALLREDUCE_STARTED) {
		access_st.insert(AccessType::ALLREDUCE);
//		msg_queue.push_back(pkg);
//		EV << "opId:" << pkg->getOpId() << "  allreduce start!!!!!\n";
		allreduceManager[pkg->getOpId()].first = true;
		free(pkg);

	} else if (pkg->getKind() == SimPacketType::ALLREDUCE_FINISHED) {
		EV << "allreduce finished!!!!\n";
		if (!access_st.count(AccessType::ALLREDUCE)) {
			throw "allreduce not in access!!";
		}
		for (auto &it : grad_acc) {
			it.second = 0;
		}
		for (auto &m : allreduceManager) {
			m.first = false;
			m.second.reset();
		}
		access_st.erase(AccessType::ALLREDUCE);
		free(pkg);
		if (local_rank == 0) {
			++cnt_epoch;
			if (cnt_epoch < all_epochs) {
				for (int i = 0; i < num_acc; ++i) {
					scheduleAtSelf(simTime(),
							createMessage("start training",
									SimPacketType::FORWARD_STARTED,
									std::make_tuple(local_rank, rank)));
				}
			}
		}
	} else if (pkg->getKind() == SimPacketType::ALLREDUCE_RUNNING) {
		EV << "(" << pkg->getSrcRank() << "," << pkg->getSrcLocalRank() << ")->"
					<< "(" << rank << "," << local_rank << ")" << " opId:"
					<< pkg->getOpId() << "  allreduce running!!!!!\n";
		msg_queue.push_back(pkg);
	}

	if (access_st.count(AccessType::ALLREDUCE)) {
		std::vector<Primitive> vec;
		for (int i = 0; i < allreduceManager.size(); ++i) {
			auto &m = allreduceManager[i];
			if (m.first && m.second.isFinished()) {
				continue;
			}

			if (m.first) {
				m.second.consume(msg_queue, vec);
				for (auto &mp : vec) {
					sendRoute(
							createMessage("allreduce",
									SimPacketType::ALLREDUCE_RUNNING,
									std::make_tuple(mp.local_rank, mp.rank),
									mp.nb, i), model->get_send_latency());
				}
				vec.clear();
			}

			if (m.first && m.second.isFinished()) {

			} else {
				break;
			}
		}

		int finished_size = 0;
		for (auto &m : allreduceManager) {
			if (m.first && m.second.isFinished()) {
				finished_size += 1;
			}
		}
		//allreduce ���
		if (finished_size == allreduceManager.size()) {
			scheduleAtSelf(simTime(),
					createMessage("allreduce finished",
							SimPacketType::ALLREDUCE_FINISHED,
							std::make_tuple(local_rank, rank)));
		}
	}
//allreduce����
	if (access_st.empty()) {
		int i = 0;
		while (i < msg_queue.size()) {
			auto &msg = msg_queue[i];
			//backward ���ȵ���
			if (msg->getKind() == SimPacketType::BACKWARD_STARTED) {
				break;
			}
			++i;
		}
		if (i < msg_queue.size()) {
			cMessage *tmp = msg_queue[i];
			msg_queue.erase(msg_queue.begin() + i);
			scheduleAtSelf(simTime(), tmp);
			return;
		}

		i = 0;
		while (i < msg_queue.size()) {
			auto &msg = msg_queue[i];
			//backward ���ȵ���
			if (msg->getKind() == SimPacketType::FORWARD_STARTED) {
				break;
			}
			++i;
		}
		if (i < msg_queue.size()) {
			cMessage *tmp = msg_queue[i];
			msg_queue.erase(msg_queue.begin() + i);
			scheduleAtSelf(simTime(), tmp);
		}

	}
}

cMessage* GPU::createMessage(std::string name, SimPacketType kind,
		std::tuple<int, int> dest_rank, size_t nb, int opId) const {
	SimPacket *pkg = new SimPacket(name.c_str(), kind);
	pkg->setSrcLocalRank(local_rank);
	pkg->setSrcRank(rank);
	pkg->setDestLocalRank(std::get<0>(dest_rank));
	pkg->setDestRank(std::get<1>(dest_rank));
	pkg->setByteLength(nb);
	pkg->setOpId(opId);
	return pkg;
}

void GPU::sendRoute(cMessage *msg, double delay) {
	SimPacket *pkg = check_and_cast<SimPacket*>(msg);
	auto r = std::make_tuple(pkg->getDestLocalRank(), pkg->getDestRank());

	if (router.count(r)) {
		int idx = router.at(r);
		cChannel *txChannel =
				gate("nvlink_port$o", idx)->getTransmissionChannel();
		simtime_t txFinishTime = txChannel->getTransmissionFinishTime();
		if (txFinishTime <= simTime() + delay) {
			if (wait_queue.count(msg)) {
				wait_queue.erase(msg);
			}
			this->sendDelayed(msg, delay, "nvlink_port$o", idx);
		} else {
			wait_queue.insert(msg);
			scheduleAt(txFinishTime, msg);
		}
	} else {
		cChannel *txChannel = gate("switch_port$o")->getTransmissionChannel();
		simtime_t txFinishTime = txChannel->getTransmissionFinishTime();
		//pcie
		if (txFinishTime <= simTime() + delay) {
			if (wait_queue.count(msg)) {
				wait_queue.erase(msg);
			}
			this->sendDelayed(msg, delay, "switch_port$o");
		} else {
			wait_queue.insert(msg);
			scheduleAt(txFinishTime, msg);
		}
	}
}

void GPU::scheduleAtSelf(simtime_t t, cMessage *msg) {
	this->scheduleAt(t, msg);
}

