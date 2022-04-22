### head 16 acc
./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_8_HOST_432 --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_8_HOST_432.txt

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_8_HOST_128 --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_8_HOST_128.txt

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_8_GPU_8_HOST_16 --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_8_GPU_8_HOST_16.txt


#head 32 acc
./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_8_HOST_432 --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_8_HOST_432.txt

./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_8_HOST_128 --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_8_HOST_128.txt

./ddp_sim -r 0 -u Cmdenv -c HEAD_32_LAYERS_8_GPU_8_HOST_16 --debug-on-errors=false omnetpp.ini > HEAD_32_LAYERS_8_GPU_8_HOST_16.txt
