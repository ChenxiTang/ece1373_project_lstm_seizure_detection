## FPGA design flow in non-project mode

set projName noMB
set designName noMB
set rootDir vivado_designs
set dir ${rootDir}/${projName}
file mkdir $dir
set partNU xcvu095-ffvc1517-2-e


source TCL/top_no_MB.tcl
