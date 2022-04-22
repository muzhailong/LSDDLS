/*
 * Model.cpp
 *
 *  Created on: 2021��12��30��
 *      Author: MI
 */

#include "Model.h"

Model::Model(std::string profile_file, int num_layers) {
	std::ifstream in(profile_file);
	if (in) {
		std::string line;
		std::vector<std::string> vec;

		getline(in, line);
		split(line, vec, ",");
		batch_size = to<int>(trim(vec[0]));
		a_sz = to<int>(trim(vec[1])) * batch_size * BASE_NB;
		g_sz = to<int>(trim(vec[1])) * BASE_NB;

		this->num_layers = num_layers;
		forward_time = to<double>(trim(vec[2])) * num_layers;

		vec.clear();
		while (getline(in, line)) {
			split(line, vec, ",");
			backward_ops.push_back(
					Op(trim(vec[0]), to<double>(trim(vec[2])),
							to<int>(trim(vec[1]))));
			vec.clear();
		}
	} else {
		throw "backward_profile_file not found!!!";
	}
	in.close();
	for (int i = 1; i < backward_ops.size(); ++i) {
		backward_ops[i].r_finished_time -= backward_ops[0].r_finished_time;
	}

	backward_ops.erase(backward_ops.begin());
	int sz = backward_ops.size();
	for (int n = 1; n < num_layers; ++n) {
		double base = backward_ops.back().r_finished_time;
		for (int i = 0; i < sz; ++i) {
			backward_ops.push_back(
					Op(backward_ops[i].name,
							backward_ops[i].r_finished_time + base,
							backward_ops[i].nb));
		}
	}
}

double Model::get_forward_time() const {
	return forward_time;
}

const Op Model::get_backward_op(int index) const {
	if (index >= backward_ops.size()) {
		throw "index out of index!!!!";
	}
	return backward_ops[index];
}

size_t Model::get_forward_nb() const {
	return a_sz;
}

double Model::get_cal_loss_time() const {
	return 0.021;
}

double Model::get_send_latency() const {
	return 0.001;
}

int Model::get_ops_size() const {
	return backward_ops.size();
}

size_t Model::get_backward_nb() const {
	return g_sz;
}

Model::~Model() {
	// TODO Auto-generated destructor stub
}

OpAllReduceManager::OpAllReduceManager(int local_rank, int rank, int local_size,
		int world_size, size_t data_size, int opId, std::string strategy) :
		local_rank(local_rank), rank(rank), local_size(local_size), world_size(
				world_size), data_size(data_size), opId(opId), strategy(
				strategy) {
	step = 0;

}

bool OpAllReduceManager::build(std::vector<int> &world_rank) {
    int p_rank = std::find(world_rank.begin(), world_rank.end(), rank)
                - world_rank.begin();
        int world_size = world_rank.size();
        //¸ù¾ÝÏûÏ¢µÄ´óÐ¡Ñ¡Ôñ²»Í¬µÄ¼¯ºÏÍ¨ÐÅËã·¨
        size_t th = 16 * 1024 * 1024/8; //16Mb
        size_t cnt_sz = data_size * 4 * 8;

        int new_rank = local_size * p_rank + local_rank;
        int all_size = local_size * world_size;
        if (cnt_sz < th && (all_size&(all_size-1)==0)) { //hdËã·¨
    //      EV << "hdËã·¨\n";
            int step = 0;
            do {
                int fa = (1 << (step + 1));
                int remote_rank = 0;
                int remote_local_rank = 0;

                if (new_rank % fa < fa / 2) {
                    int t_rank = new_rank + fa / 2;
                    remote_rank = world_rank[t_rank / local_size];
                    remote_local_rank = t_rank % local_size;
                } else {
                    int t_rank = new_rank - fa / 2;
                    remote_rank = world_rank[t_rank / local_size];
                    remote_local_rank = t_rank % local_size;
                }
                process.push_back(
                        Primitive(remote_local_rank, remote_rank, data_size / fa,
                                PrimitiveType::MPISEND));
                process.push_back(
                        Primitive(remote_local_rank, remote_rank, data_size / fa,
                                PrimitiveType::MPIRECV));
                ++step;
            } while ((1 << step) < all_size / 2);

            --step;

            do {
                int fa = (1 << (step + 1));
                int remote_rank = 0;
                int remote_local_rank = 0;

                if (new_rank % fa < fa / 2) {
                    int t_rank = new_rank + fa / 2;
                    remote_rank = world_rank[t_rank / local_size];
                    remote_local_rank = t_rank % local_size;
                } else {
                    int t_rank = new_rank - fa / 2;
                    remote_rank = world_rank[t_rank / local_size];
                    remote_local_rank = t_rank % local_size;
                }
                process.push_back(
                        Primitive(remote_local_rank, remote_rank, data_size / fa,
                                PrimitiveType::MPISEND));
                process.push_back(
                        Primitive(remote_local_rank, remote_rank, data_size / fa,
                                PrimitiveType::MPIRECV));
                --step;
            } while (step > -1);

        } else { //ring
    //      EV<<"ring Ëã·¨\n";
            int left = (new_rank - 1 + all_size) % all_size;
            int left_rank = world_rank[left / local_size];
            int left_local_rank = left % local_size;

            int right = (new_rank + 1) % all_size;
            int right_rank = world_rank[right / local_size];
            int right_local_rank = right % local_size;

            size_t block_size = data_size / all_size;
            //reducescatter
            for (int i = 0; i < all_size - 1; ++i) {
                process.push_back(
                        Primitive(right_local_rank, right_rank, block_size,
                                PrimitiveType::MPISEND));
                process.push_back(
                        Primitive(left_local_rank, left_rank, block_size,
                                PrimitiveType::MPIRECV));
            }
            //allgather
            for (int i = 0; i < all_size - 1; ++i) {
                process.push_back(
                        Primitive(right_local_rank, right_rank, block_size,
                                PrimitiveType::MPISEND));
                process.push_back(
                        Primitive(left_local_rank, left_rank, block_size,
                                PrimitiveType::MPIRECV));
            }
        }

    //  if (strategy == "local") { //¾Ö²¿ÐÔËã·¨
    //      if (local_rank == 0) {
    //          for (int i = 1; i < local_size; ++i) {
    //              process.push_back(
    //                      Primitive(i, rank, data_size, PrimitiveType::MPIRECV));
    //          }
    //      } else {
    //          process.push_back(
    //                  Primitive(0, rank, data_size, PrimitiveType::MPISEND));
    //      }
    //      if (local_rank == 0) {
    //          //ring
    //          int left = (new_rank - 1 + world_size) % world_size;
    //          int right = (new_rank + 1) % world_size;
    //          size_t block_size = data_size / world_size;
    //          //reducescatter
    //          for (int i = 0; i < world_size - 1; ++i) {
    //              process.push_back(
    //                      Primitive(0, world_rank[right], block_size,
    //                              PrimitiveType::MPISEND));
    //              process.push_back(
    //                      Primitive(0, world_rank[left], block_size,
    //                              PrimitiveType::MPIRECV));
    //          }
    //          //allgather
    //          for (int i = 0; i < world_size - 1; ++i) {
    //              process.push_back(
    //                      Primitive(0, world_rank[right], block_size,
    //                              PrimitiveType::MPISEND));
    //              process.push_back(
    //                      Primitive(0, world_rank[left], block_size,
    //                              PrimitiveType::MPIRECV));
    //          }
    //
    //      }
    //
    //      if (local_rank == 0) {
    //          for (int i = 1; i < local_size; ++i) {
    //              process.push_back(
    //                      Primitive(i, rank, data_size, PrimitiveType::MPISEND));
    //          }
    //      } else {
    //          process.push_back(
    //                  Primitive(0, rank, data_size, PrimitiveType::MPIRECV));
    //      }
    //  }
        return true;
}

bool OpAllReduceManager::consume(std::vector<cMessage*> &msg_queue,
		std::vector<Primitive> &vec) {
	while (step < process.size()) {
		auto &p = process[step];
		if (p.type == PrimitiveType::MPISEND) {
			vec.push_back(p);
			step++;
			continue;
		}
//
//		if (step == 3) {
//			step -= 1;
//			step += 1;
//		}
		int i = 0;
		for (; i < msg_queue.size(); ++i) {
			SimPacket *pkg = check_and_cast<SimPacket*>(msg_queue[i]);
			//size_t sz = pkg->getByteLength();

			if (pkg->getOpId() == opId && pkg->getDestLocalRank() == local_rank
					&& pkg->getDestRank() == rank
					&& pkg->getByteLength() == process[step].nb) {
				break;
			}
		}

		if (i >= msg_queue.size()) {
			break;
		} else {
			++step;
			free(msg_queue[i]);
			msg_queue.erase(msg_queue.begin() + i);
		}
	}

	if (step >= process.size()) {
		return true;
	}
	return false;
}

bool OpAllReduceManager::reset() {
	step = 0;
	return true;
}

bool OpAllReduceManager::isFinished() {
	return step >= process.size();
}
