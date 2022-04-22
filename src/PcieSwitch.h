/*
 * PcieSwitch.h
 *
 *  Created on: 2021Äê11ÔÂ25ÈÕ
 *      Author: MI
 */

#ifndef PCIESWITCH_H_
#define PCIESWITCH_H_

#include <omnetpp.h>
#include <map>
#include <iostream>
#include <vector>
using namespace omnetpp;

class PcieSwitch: public cSimpleModule {
private:
    std::map<std::tuple<int,int>, int> router;
public:
    PcieSwitch();
    virtual ~PcieSwitch();
    virtual int numInitStages() const override;
    virtual void initialize(int) override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif /* PCIESWITCH_H_ */
