

set projName test_design2
set designName prj_design2
set rootDir vivado_designs
set dir $rootDir/$projName
file mkdir $dir
set partNU xcvu095-ffvc1517-2-e


source TCL/top.tcl
source TCL/vivado_settings.tcl

start_gui
