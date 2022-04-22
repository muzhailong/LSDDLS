enum SimPacketType
{
    ECSSIM_CONN_REQ = 0;
    ECSSIM_CONN_ACK = 1;
    ECSSIM_DISC_REQ = 2;
    ECSSIM_DISC_ACK = 3;
    ECSSIM_DATA_W = 4;//权重
    ECSSIM_DATA_A = 5;//激活
    ECSSIM_DATA_BACKFORWARD_G = 6;//集合通信
    ECSSIM_DATA_ALLREDUCE_G=7;//反向传播
    ECSSIM_CONFIG = 8;//配置
    ECSSIM_BUSY = 9;
    ECSSIM_SYNC_REQ = 10;
    ECSSIM_SYNC_ACK = 11;
    ECSSIM_OP_FINISHED =12;
    ECSSIM_START_MICRO_BATCH = 13;
    ECSSIM_FORWARD_OP_FINISHED = 14;
    ECSSIM_BACKWARD_OP_FINISHED = 15;
    
    FORWARD_STARTED = 16;
    FORWARD_FINISHED = 17;
    
    BACKWARD_STARTED = 18;
    BACKWARD_FINISHED = 19;
    BACKWARD_OP_FINISHED =20;
    
   	ALLREDUCE_STARTED = 21;
   	ALLREDUCE_FINISHED = 22;
   	ALLREDUCE_RUNNING = 23;
   	
   	
    
  
    
};

packet SimPacket
{
    int srcLocalRank;
    int srcRank;
    int destLocalRank;
    int destRank;
    int opId;
};