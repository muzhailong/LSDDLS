#head 16 num layer
./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_16_GPU_8_HOST_128 --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_16_GPU_8_HOST_128.txt

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_24_GPU_8_HOST_128 --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_24_GPU_8_HOST_128.txt

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_32_GPU_8_HOST_128 --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_32_GPU_8_HOST_128.txt

./ddp_sim -r 0 -u Cmdenv -c HEAD_16_LAYERS_40_GPU_8_HOST_128 --debug-on-errors=false omnetpp.ini > HEAD_16_LAYERS_40_GPU_8_HOST_128.txt
