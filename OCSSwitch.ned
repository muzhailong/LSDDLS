simple OCSSwitch
{
    parameters:
        string name=default("ocs switch");
        int px;
        int py;
    gates:
        inout ports[];
}