//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "NIC.h"
using namespace omnetpp;
Define_Module(NIC);
NIC::NIC() :
		up_rank(-1), down_rank(-1) {
	// TODO Auto-generated constructor stub

}

NIC::~NIC() {
	// TODO Auto-generated destructor stub
}
int NIC::numInitStages() const {
	return 2;
}

void NIC::initialize(int stage) {
	if (stage == 1) {
		cModule *m = getParentModule();
//		findSubmodule("switchs")-s
		int num_switchs =
				m->getParentModule()->getSubmodule("switchs", 0)->getVectorSize();
//				m->gate("net_port$o")->getNextGate()->getOwnerModule()->getSubmodule(
//						"switchs")->size();
		int num_ranks_in_world = m->getParentModule()->getSubmodule("switchs",
				0)->gateSize("ports");
		int rank =
				check_and_cast<GPU*>(m->getSubmodule("host_gpus", 0))->get_rank();
		int idx = m->getIndex();

		if (idx < num_ranks_in_world) {
			down_rank = -1;
		} else {
			down_rank =
					check_and_cast<GPU*>(
							m->gate("down_port$o")->getNextGate()->getOwnerModule()->getSubmodule(
									"host_gpus", 0))->get_rank();
		}

		if (idx / num_ranks_in_world == num_switchs - 1) {
			up_rank = -1;
		} else {
			up_rank =
					check_and_cast<GPU*>(
							m->gate("up_port$o")->getNextGate()->getOwnerModule()->getSubmodule(
									"host_gpus", 0))->get_rank();
		}

	}
}

void NIC::handleMessage(cMessage *msg) {
	SimPacket *pkg = check_and_cast<SimPacket*>(msg);
	std::string port_str = "";
	if (!msg->isSelfMessage()) {
		if (msg->arrivedOn("host_port$i")) {
			if (pkg->getDestRank() == up_rank) {
				port_str = "up_net_port$o";
			} else if (pkg->getDestRank() == down_rank) {
				port_str = "down_net_port$o";
			} else {
				port_str = "net_port$o";
			}
		} else {
			port_str = "host_port$o";
		}
		cChannel *txChannel = gate(port_str.c_str())->getTransmissionChannel();
		simtime_t txFinishTime = txChannel->getTransmissionFinishTime();
		if (txFinishTime <= simTime()) {
			send(msg, port_str.c_str());
		} else {
			if (msg->arrivedOn("host_port$i")) {
				host_st.insert(msg);
			} else if (msg->arrivedOn("net_port$i")) {
				net_st.insert(msg);
			} else if (msg->arrivedOn("up_net_port$i")) {
				up_st.insert(msg);
			} else if (msg->arrivedOn("down_net_port$i")) {
				down_st.insert(msg);
			}
			scheduleAt(txFinishTime+5.0/1e6, msg);
		}
	} else {
		if (host_st.count(msg)) {
			if (pkg->getDestRank() == up_rank) {
				port_str = "up_net_port$o";
			} else if (pkg->getDestRank() == down_rank) {
				port_str = "down_net_port$o";
			} else {
				port_str = "net_port$o";
			}
		} else {
			port_str = "host_port$o";
		}
		cChannel *txChannel = gate(port_str.c_str())->getTransmissionChannel();
		simtime_t txFinishTime = txChannel->getTransmissionFinishTime();
		if (txFinishTime <= simTime()) {
			// channel free; send out packet immediately
			send(msg, port_str.c_str());
			if (host_st.count(msg)) {
				host_st.erase(msg);
			} else if (net_st.count(msg)) {
				net_st.erase(msg);
			} else if (up_st.count(msg)) {
				up_st.erase(msg);
			} else if (down_st.count(msg)) {
				down_st.erase(msg);
			}
		} else {
			// store packet and schedule timer; when the timer expires,
			// the packet should be removed from the queue and sent out
			scheduleAt(txFinishTime+5.0/1e6, msg);
		}
	}
}
