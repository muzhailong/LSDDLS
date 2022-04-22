#head 16 num layer
./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_8_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_8_HOST_1024.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_16_GPU_8_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_16_GPU_8_HOST_1024.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_24_GPU_8_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_24_GPU_8_HOST_1024.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_32_GPU_8_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_32_GPU_8_HOST_1024.txt &

#head 32 num layer
./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_8_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_8_HOST_1024.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_16_GPU_8_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_16_GPU_8_HOST_1024.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_24_GPU_8_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_24_GPU_8_HOST_1024.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_32_GPU_8_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_32_GPU_8_HOST_1024.txt &

### head 16 acc
./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_8_HOST_1024_1_acc --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_8_HOST_1024_1_acc.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_8_HOST_1024_2_acc --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_8_HOST_1024_2_acc.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_8_HOST_1024_3_acc --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_8_HOST_1024_3_acc.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_8_HOST_1024_4_acc --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_8_HOST_1024_4_acc.txt &

#head 32 acc
./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_8_HOST_1024_1_acc --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_8_HOST_1024_1_acc.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_8_HOST_1024_2_acc --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_8_HOST_1024_2_acc.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_8_HOST_1024_3_acc --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_8_HOST_1024_3_acc.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_8_HOST_1024_4_acc --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_8_HOST_1024_4_acc.txt &


### head 16 gpu num
./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_1_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_1_HOST_1024.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_2_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_2_HOST_1024.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_4_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_4_HOST_1024.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_16_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_16_HOST_1024.txt &


### head 32 gpu num
./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_1_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_1_HOST_1024.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_2_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_2_HOST_1024.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_4_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_4_HOST_1024.txt &

./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_16_HOST_1024 --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_16_HOST_1024.txt &
