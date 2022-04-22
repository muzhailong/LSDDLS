### head 16 acc
./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_8_HOST_1024_1_acc --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_8_HOST_1024_1_acc.txt

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_8_HOST_1024_2_acc --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_8_HOST_1024_2_acc.txt

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_8_HOST_1024_3_acc --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_8_HOST_1024_3_acc.txt

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_8_HOST_1024_4_acc --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_8_HOST_1024_4_acc.txt

#head 32 acc
./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_8_HOST_1024_1_acc --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_8_HOST_1024_1_acc.txt

./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_8_HOST_1024_2_acc --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_8_HOST_1024_2_acc.txt

./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_8_HOST_1024_3_acc --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_8_HOST_1024_3_acc.txt

./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_8_HOST_1024_4_acc --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_8_HOST_1024_4_acc.txt
