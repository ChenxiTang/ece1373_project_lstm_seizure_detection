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
ExecStep $xv_path/bin/xelab -wto b2fd7c94d4894f02b4ed71b34f805f65 -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot PCIE_Status_v2_0_behav xil_defaultlib.PCIE_Status_v2_0 xil_defaultlib.glbl -log elaborate.log
