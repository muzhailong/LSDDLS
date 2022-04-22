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

simple GPU
{
    parameters:
        int num_nvlink_port=default(4);
        double timeout @unit(s) @prompt("Connection timeout")=default(2s);
        string profile_file;
        int num_layers_per_gpu;
        int num_acc;
        int epochs;
 	gates:
 	    inout switch_port;
 	    inout nvlink_port[];   
}