#ifndef GPU_H_
#define GPU_H_
#include <omnetpp.h>
#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <unordered_map>
#include <mutex>
#include "Utils.h"
#include "SimPacket_m.h"
#include "Model.h"
#include <memory>
#include "OCSSwitch.h"
#include <unordered_set>

using namespace omnetpp;


enum AccessType{
    ANY=0,
    FORWARD=1,
    BACKWARD=2,
	ALLREDUCE=3
};


class GPU: public cSimpleModule {
private:
	int rank;
	int local_rank;
	int size;
	int local_size;
	std::shared_ptr<Model> model;
	std::vector<cMessage*>msg_queue;
	std::unordered_set<AccessType> access_st;
	std::map<std::tuple<int,int>, int> router;//路由
	std::unordered_map<int,int>grad_acc;
	int num_acc;
	std::vector<std::pair<bool,OpAllReduceManager>>allreduceManager;
	void scheduleAtSelf(simtime_t t, cMessage *msg);
	int cnt_epoch;
	int all_epochs;
	std::unordered_set<cMessage*>wait_queue;
	std::vector<int>world_ranks;//可以直接从交换机的路由表获取
	int up_rank;
	int down_rank;
	int world_size;
	int num_switchs;
	int world_idx;




public:
	GPU();
	virtual ~GPU();
	int get_rank();
	int get_localRank();
protected:
	virtual int numInitStages() const override;
	virtual void initialize(int) override;
	virtual void handleMessage(cMessage *msg) override;
	cMessage* createMessage(std::string name,
			SimPacketType kind,
			std::tuple<int,int>dest_rank,
			size_t nb=0,
			int opId=0) const;
	void sendRoute(cMessage *msg, double delay=.0);

};

#endif /* GPU_H_ */
