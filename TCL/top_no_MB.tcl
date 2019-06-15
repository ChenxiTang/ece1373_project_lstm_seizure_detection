#Top level TCL for ECE1373 final project, built with Vivado 2017.2

#####################################################################
#Set up project details and create a block design                   #
#####################################################################

create_project $designName $dir -part xcvu095-ffvc1517-2-e -force 

set_property  ip_repo_paths  {IP_REPO/ocl_ips} [current_project]

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

source TCL/bd_no_MB_pcie.tcl

start_gui
open_bd_design ${dir}/${designName}.srcs/sources_1/bd/${designName}/${designName}.bd

validate_bd_design
make_wrapper -files [get_files ${dir}/${designName}.srcs/sources_1/bd/${designName}/${designName}.bd] -top
add_files -norecurse  ${dir}/${designName}.srcs/sources_1/bd/${designName}/hdl/${designName}_wrapper.v



