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

#include "PcieSwitch.h"
#include "GPU.h"
using namespace omnetpp;

Define_Module(PcieSwitch);

PcieSwitch::PcieSwitch() {

}

PcieSwitch::~PcieSwitch() {

}

int PcieSwitch::numInitStages() const {
	return 2;
}

void PcieSwitch::initialize(int stage) {
	switch (stage) {
	case 0: {
		//gpu��ʼ��rank
		break;
	}
	case 1: {
		//�˿�ӳ���ʼ��
		int port_size = gateSize("ports");
		for (int i = 0; i < port_size - 1; ++i) { //���һ���˿����ӵ�����
			cModule *m = gate("ports$o", i)->getNextGate()->getOwnerModule();
			GPU *g = check_and_cast<GPU*>(m);
			router[std::make_tuple(g->get_rank(), g->get_localRank())] = i;
		}
		break;
	}
	}
}

void PcieSwitch::handleMessage(cMessage *msg) {
	//switch ת����ʱ��
	SimPacket *pkt = check_and_cast<SimPacket*>(msg);

	auto dest_p = std::make_tuple(pkt->getDestRank(), pkt->getDestLocalRank());
	int port_size = gateSize("ports");

	int p = 0;
	if (router.count(dest_p)) { //ͬһ���ڵ���
		p = router[dest_p];
//		send(msg, "ports$o", router[dest_p]);
	} else { //nic
		p = port_size - 1;
//		send(msg, "ports$o", port_size - 1);
	}
	cChannel *txChannel = gate("ports$o", p)->getTransmissionChannel();
	simtime_t txFinishTime = txChannel->getTransmissionFinishTime();
	if (txFinishTime <= simTime()) {
		// channel free; send out packet immediately
		send(msg, "ports$o", p);
	} else {
		// store packet and schedule timer; when the timer expires,
		// the packet should be removed from the queue and sent out
		scheduleAt(txFinishTime+87.0/1e6, msg);
	}

//	//NIC���������ݰ�
//	if (msg->arrivedOn("ports$i", port_size - 1)) {
//		if (router.count(dest_p)) {
//			send(msg, "ports$o", router[dest_p]);
//		} else {
//			throw "PcieSwitch Error packet!!!";
//		}
//	} else {
//		if (router.count(dest_p)) { //ͬһ���ڵ���
//			send(msg, "ports$o", router[dest_p]);
//		} else { //nic
//			send(msg, "ports$o", port_size - 1);
//		}
//	}
}
