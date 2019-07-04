#!/bin/bash -f
xv_path="/opt/Xilinx/Vivado/2017.2"
ExecStep()
{
"$@"
RETVAL=$?
if [ $RETVAL -ne 0 ]
then
exit $RETVAL
fi
}
ExecStep $xv_path/bin/xsim PCIE_Status_v2_0_behav -key {Behavioral:sim_1:Functional:PCIE_Status_v2_0} -tclbatch PCIE_Status_v2_0.tcl -log simulate.log
