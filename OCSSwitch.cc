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

#include "OCSSwitch.h"
Define_Module(OCSSwitch);
OCSSwitch::OCSSwitch() {
	// TODO Auto-generated constructor stub

}

OCSSwitch::~OCSSwitch() {
	// TODO Auto-generated destructor stub
}

int OCSSwitch::numInitStages() const {
	return 4;
}

void OCSSwitch::initialize(int stage) {
	int sz = gateSize("ports");
	if (stage == 1) {
		for (int i = 0; i < sz; ++i) {
			cModule *m = gate("ports$o", i)->getNextGate()->getOwnerModule();
			int rank =
					check_and_cast<GPU*>(m->getSubmodule("host_gpus", 0))->get_rank();
			router[rank] = i;
		}
	}
}

void OCSSwitch::handleMessage(cMessage *msg) {
	SimPacket *pkt = check_and_cast<SimPacket*>(msg);
	int rank = pkt->getDestRank();
	int p = router[rank];
	cChannel *txChannel = gate("ports$o", p)->getTransmissionChannel();
	simtime_t txFinishTime = txChannel->getTransmissionFinishTime();
	if (txFinishTime <= simTime()) {
		// channel free; send out packet immediately
		send(msg, "ports$o", p);
	} else {
		// store packet and schedule timer; when the timer expires,
		// the packet should be removed from the queue and sent out
		scheduleAt(txFinishTime, msg);
	}
}

