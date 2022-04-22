//
// Generated file, do not edit! Created by nedtool 5.0 from SimPacket.msg.
//

#ifndef __SIMPACKET_M_H
#define __SIMPACKET_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0500
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Enum generated from <tt>SimPacket.msg:2</tt> by nedtool.
 * <pre>
 * enum SimPacketType
 * {
 * 
 *     ECSSIM_CONN_REQ = 0;
 *     ECSSIM_CONN_ACK = 1;
 *     ECSSIM_DISC_REQ = 2;
 *     ECSSIM_DISC_ACK = 3;
 *     ECSSIM_DATA_W = 4;//权重
 *     ECSSIM_DATA_A = 5;//激活
 *     ECSSIM_DATA_BACKFORWARD_G = 6;//集合通信
 *     ECSSIM_DATA_ALLREDUCE_G = 7;//反向传播
 *     ECSSIM_CONFIG = 8;//配置
 *     ECSSIM_BUSY = 9;
 *     ECSSIM_SYNC_REQ = 10;
 *     ECSSIM_SYNC_ACK = 11;
 *     ECSSIM_OP_FINISHED = 12;
 *     ECSSIM_START_MICRO_BATCH = 13;
 *     ECSSIM_FORWARD_OP_FINISHED = 14;
 *     ECSSIM_BACKWARD_OP_FINISHED = 15;
 * 
 *     FORWARD_STARTED = 16;
 *     FORWARD_FINISHED = 17;
 * 
 *     BACKWARD_STARTED = 18;
 *     BACKWARD_FINISHED = 19;
 *     BACKWARD_OP_FINISHED = 20;
 * 
 *     ALLREDUCE_STARTED = 21;
 *     ALLREDUCE_FINISHED = 22;
 *     ALLREDUCE_RUNNING = 23;
 * 
 * 
 * 
 * 
 * 
 * }
 * </pre>
 */
enum SimPacketType {
    ECSSIM_CONN_REQ = 0,
    ECSSIM_CONN_ACK = 1,
    ECSSIM_DISC_REQ = 2,
    ECSSIM_DISC_ACK = 3,
    ECSSIM_DATA_W = 4,
    ECSSIM_DATA_A = 5,
    ECSSIM_DATA_BACKFORWARD_G = 6,
    ECSSIM_DATA_ALLREDUCE_G = 7,
    ECSSIM_CONFIG = 8,
    ECSSIM_BUSY = 9,
    ECSSIM_SYNC_REQ = 10,
    ECSSIM_SYNC_ACK = 11,
    ECSSIM_OP_FINISHED = 12,
    ECSSIM_START_MICRO_BATCH = 13,
    ECSSIM_FORWARD_OP_FINISHED = 14,
    ECSSIM_BACKWARD_OP_FINISHED = 15,
    FORWARD_STARTED = 16,
    FORWARD_FINISHED = 17,
    BACKWARD_STARTED = 18,
    BACKWARD_FINISHED = 19,
    BACKWARD_OP_FINISHED = 20,
    ALLREDUCE_STARTED = 21,
    ALLREDUCE_FINISHED = 22,
    ALLREDUCE_RUNNING = 23
};

/**
 * Class generated from <tt>SimPacket.msg:38</tt> by nedtool.
 * <pre>
 * packet SimPacket
 * {
 *     int srcLocalRank;
 *     int srcRank;
 *     int destLocalRank;
 *     int destRank;
 *     int opId;
 * }
 * </pre>
 */
class SimPacket : public ::omnetpp::cPacket
{
  protected:
    int srcLocalRank;
    int srcRank;
    int destLocalRank;
    int destRank;
    int opId;

  private:
    void copy(const SimPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SimPacket&);

  public:
    SimPacket(const char *name=nullptr, int kind=0);
    SimPacket(const SimPacket& other);
    virtual ~SimPacket();
    SimPacket& operator=(const SimPacket& other);
    virtual SimPacket *dup() const {return new SimPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b);

    // field getter/setter methods
    virtual int getSrcLocalRank() const;
    virtual void setSrcLocalRank(int srcLocalRank);
    virtual int getSrcRank() const;
    virtual void setSrcRank(int srcRank);
    virtual int getDestLocalRank() const;
    virtual void setDestLocalRank(int destLocalRank);
    virtual int getDestRank() const;
    virtual void setDestRank(int destRank);
    virtual int getOpId() const;
    virtual void setOpId(int opId);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const SimPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, SimPacket& obj) {obj.parsimUnpack(b);}


#endif // ifndef __SIMPACKET_M_H

