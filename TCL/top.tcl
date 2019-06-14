#Top level TCL for ECE1373 final project, built with Vivado 2017.2

#####################################################################
#Set up project details and create a block design                   #
#####################################################################

create_project $designName $dir -part xcvu095-ffvc1517-2-e -force 

set_property  ip_repo_paths  {IP_REPO/ocl_ips\
				  IP_REPO/pcie_status\
hls_proj/ph_proj/solution1/impl/ip \
hls_proj/ElemWiseSigmoid_proj/solution1/impl/ip\
hls_proj/ElemWiseTanh_proj/solution1/impl/ip\
hls_proj/ElemWiseVecAdd_proj/solution1/impl/ip\
hls_proj/ElemWiseVecMul_proj/solution1/impl/ip\
hls_proj/mv_input_proj/solution1/impl/ip\
hls_proj/mv_output_proj/solution1/impl/ip\
hls_proj/mv_state_proj/solution1/impl/ip} [current_project]

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

source TCL/xdma_fir_mvs_dummies_v2.tcl

validate_bd_design

#start_gui
#open_bd_design {$dir/$designName.srcs/sources_1/bd/design_1/design_1.bd}



