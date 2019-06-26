## FPGA design flow in non-project mode

set projName test_design2
set designName prj_design2
set rootDir vivado_designs
set dir $rootDir/$projName
file mkdir $dir
set partNU xcvu095-ffvc1517-2-e


source TCL/top.tcl
source TCL/settings.tcl

##run synthesis
source TCL/gen.tcl
##run implementation
source TCL/impl.tcl

mkdir hw.sdk
file copy -force vivado_designs/test_design2/prj_design2.runs/impl_1/design_1_wrapper.sysdef hw.sdk/design_1_wrapper.hdf
launch_sdk -workspace hw.sdk -hwspec hw.sdk/design_1_wrapper.hdf
start_gui

