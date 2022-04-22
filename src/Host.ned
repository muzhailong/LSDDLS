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

import ned.*;
//nvlink、pcie、network三种信道
channel NvlinkChan extends DatarateChannel
{
    datarate = 4800Gbps;
}

channel PcieChan extends DatarateChannel
{
    datarate = 120Gbps;
}


module Host
{
    parameters:
        int numGpus = default(2);
        string name = default("Host");
        int px;
        int py;
        @display("bgb=369,240");
    gates:
        inout port;
        inout up_port;
        inout down_port;

    submodules:
        host_gpus[numGpus]: GPU {
            @display("p=58,164");
        }
        host_switch: PcieSwitch {
            @display("p=185,103");
        }
        host_nic: NIC;
    connections:

        //gpu <--> switch
        for i=0..numGpus-1 {
            host_gpus[i].switch_port <--> PcieChan <--> host_switch.ports++;
        }
        //switch<--> nic
        host_switch.ports++ <--> PcieChan <--> host_nic.host_port;
        host_nic.net_port <--> port;
        host_nic.up_net_port <--> up_port;
        host_nic.down_net_port <--> down_port;
        

        //gpu <--> gpu nvlink
        for i=1..int(numGpus/2)-1, for j=0..i-1 {
            host_gpus[i].nvlink_port++ <--> NvlinkChan <--> host_gpus[j].nvlink_port++;
            host_gpus[i+int(numGpus/2)].nvlink_port++ <--> NvlinkChan <--> host_gpus[j+int(numGpus/2)].nvlink_port++;

        }
        for i=0..int(numGpus/2)-1 {
            host_gpus[i].nvlink_port++ <--> NvlinkChan <--> host_gpus[i+int(numGpus/2)].nvlink_port++;
        }
}
