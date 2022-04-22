/*
 * Model.h
 *
 *  Created on: 2021年12月30日
 *      Author: MI
 */

#ifndef MODEL_H_
#define MODEL_H_
#include <iostream>
#include <fstream>
#include "Utils.h"
#include <vector>
#include <omnetpp.h>
#include "SimPacket_m.h"
#include <algorithm>


using namespace omnetpp;

#define BASE_NB 4

enum PrimitiveType {
	MPISEND = 0, MPIRECV = 1
};

class Op {
public:
	std::string name;
	double r_finished_time;
	size_t nb;
	explicit Op(std::string name, double r_finished_time, size_t nb) :
			name(name), r_finished_time(r_finished_time), nb(nb) {
	}
};

class Model {
public:
	explicit Model(std::string profile_file, int num_layers);
	virtual ~Model();
	double get_forward_time() const;
	size_t get_forward_nb() const;
	size_t get_backward_nb() const;
	const Op get_backward_op(int index) const;
	double get_cal_loss_time() const;
	double get_send_latency() const;
	int get_ops_size() const;

private:
	double forward_time; //当前模型完成前向传播的时间
	size_t a_sz; //激活值的数据量
	size_t g_sz; //梯度值的数据量
	std::vector<Op> backward_ops; //反向传播的op
	size_t batch_size;
	size_t num_layers;
};

class Primitive {
public:
	int local_rank;
	int rank;
	size_t nb;
	PrimitiveType type;
	int opId;
	Primitive(int local_rank, int rank, size_t nb, PrimitiveType type) :
			local_rank(local_rank), rank(rank), nb(nb), type(type) {
	}
};

class OpAllReduceManager {
public:
	explicit OpAllReduceManager(int local_rank, int rank, int local_size,
			int world_size, size_t data_size, int opId, std::string strategy =
					"local");
	bool consume(std::vector<cMessage*> &msg_queue,
			std::vector<Primitive> &vec);
	bool build(std::vector<int> &world_rank);
	bool reset();
	bool isFinished();

private:
	int local_rank;
	int rank;
	int local_size;
	int world_size;
	size_t data_size;
	int opId;
	std::string strategy;
	std::vector<Primitive> process;
	int step;
	std::vector<int> world_ranks;
};

#endif /* MODEL_H_ */
