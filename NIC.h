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

#ifndef NIC_H_
#define NIC_H_

#include <omnetpp.h>
#include <unordered_set>
#include "SimPacket_m.h"
#include "SimPacket_m.h"
#include "Utils.h"
#include "GPU.h"
using namespace omnetpp;

class NIC: public cSimpleModule {
public:
	NIC();
	virtual ~NIC();
	virtual void handleMessage(cMessage *msg) override;
	virtual int numInitStages() const override;
	virtual void initialize(int) override;
private:
	std::unordered_set<cMessage*> host_st;
	std::unordered_set<cMessage*> net_st;
	std::unordered_set<cMessage*> up_st;
	std::unordered_set<cMessage*> down_st;
	int up_rank;
	int down_rank;
};

#endif /* NIC_H_ */
