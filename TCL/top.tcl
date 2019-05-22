#Top level TCL for ECE1373 final project, built with Vivado 2017.2

#####################################################################
#Set up project details and create a block design                   #
#####################################################################

create_project prj_design1 vivado_designs/ -part xcvu095-ffvc1517-2-e -force 

set_property  ip_repo_paths  {IP_REPO/ocl_ips\
hls_proj/ph_proj/solution1/impl/ip } [current_project]

add_files -fileset constrs_1 -norecurse { \
support/bitstream.xdc  \
support/ddr4sdram_b0_lane8.xdc \
support/ddr4sdram_b0_unused.xdc \
support/ddr4sdram_locs_b0_twin_die.xdc \
support/ddr4sdram_locs_b0_x64.xdc \
support/ddr4sdram_locs_b0_x72.xdc \
support/ddr4sdram_props_b0_twin_die.xdc \
support/pcie_constr.xdc}

update_ip_catalog

source TCL/system_mbz.tcl

validate_bd_design 

make_wrapper -files [get_files vivado_designs/prj_design1.srcs/sources_1/bd/system/system.bd] -top

add_files -norecurse vivado_designs/prj_design1.srcs/sources_1/bd/system/hdl/system_wrapper.v

update_compile_order -fileset sources_1
reset_run synth_1
launch_runs synth_1 -jobs 12
start_gui

