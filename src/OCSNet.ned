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

import ned.*;

channel NetworkChanOfAllreduce extends DatarateChannel
{
    datarate = 32000000Gbps;
}

channel NetworkChanOfActivate extends DatarateChannel
{
    datarate = 32Gbps;
}


network OCSNet
{
    parameters:
        int num_splits = default(8);//ģ�Ͳ�����Ŀ
        int num_hosts = default(1024); //host�����ĸ���
        int num_hosts_in_world = int(num_hosts / num_splits); //ͬһ��ͨ�����ڵ�host����

    gates:
        inout dead[num_hosts_in_world*2];

    submodules:
        switchs[num_splits]: OCSSwitch {
            name = "ocs_switch";
            @display("p=$px,$py");
            py = 75+50*index;
            px = 50;
        }
        servers[num_hosts]: Host {
            name = "host";
            @display("p=$px,$py");
            px = 100+50*(index % num_hosts_in_world);
            py = 50+50*int((index / num_hosts_in_world));
        }
    connections:

        for i=0..sizeof(servers)-1 {
            servers[i].port <--> NetworkChanOfAllreduce <--> switchs[int(i/num_hosts_in_world)].ports++;//direct link
            
            servers[i].down_port <--> dead++ if i < num_hosts_in_world;
            servers[i].up_port <--> dead++ if int(i/num_hosts_in_world)==num_splits-1;
            servers[i].down_port <--> NetworkChanOfActivate <--> servers[i-num_hosts_in_world].up_port if i >= num_hosts_in_world;
        }
}
