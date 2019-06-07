
################################################################
# This is a generated script based on design: design_1
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

namespace eval _tcl {
proc get_script_folder {} {
   set script_path [file normalize [info script]]
   set script_folder [file dirname $script_path]
   return $script_folder
}
}
variable script_folder
set script_folder [_tcl::get_script_folder]

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2017.2
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   catch {common::send_msg_id "BD_TCL-109" "ERROR" "This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."}

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source design_1_script.tcl

# If there is no project opened, this script will create a
# project, but make sure you do not have an existing project
# <./myproj/project_1.xpr> in the current working folder.

set list_projs [get_projects -quiet]
if { $list_projs eq "" } {
   create_project project_1 myproj -part xcvu095-ffvc1517-2-e
}


# CHANGE DESIGN NAME HERE
set design_name design_1

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
   # USE CASES:
   #    1) Design_name not set

   set errMsg "Please set the variable <design_name> to a non-empty value."
   set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
   # USE CASES:
   #    2): Current design opened AND is empty AND names same.
   #    3): Current design opened AND is empty AND names diff; design_name NOT in project.
   #    4): Current design opened AND is empty AND names diff; design_name exists in project.

   if { $cur_design ne $design_name } {
      common::send_msg_id "BD_TCL-001" "INFO" "Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   common::send_msg_id "BD_TCL-002" "INFO" "Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
   # USE CASES:
   #    5) Current design opened AND has components AND same names.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
   # USE CASES: 
   #    6) Current opened design, has components, but diff names, design_name exists in project.
   #    7) No opened design, design_name exists in project.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 2

} else {
   # USE CASES:
   #    8) No opened design, design_name not in project.
   #    9) Current opened design, has components, but diff names, design_name not in project.

   common::send_msg_id "BD_TCL-003" "INFO" "Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design $design_name

   common::send_msg_id "BD_TCL-004" "INFO" "Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

common::send_msg_id "BD_TCL-005" "INFO" "Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   catch {common::send_msg_id "BD_TCL-114" "ERROR" $errMsg}
   return $nRet
}

##################################################################
# DESIGN PROCs
##################################################################


# Hierarchical cell: microblaze_0_local_memory
proc create_hier_cell_microblaze_0_local_memory { parentCell nameHier } {

  variable script_folder

  if { $parentCell eq "" || $nameHier eq "" } {
     catch {common::send_msg_id "BD_TCL-102" "ERROR" "create_hier_cell_microblaze_0_local_memory() - Empty argument(s)!"}
     return
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     catch {common::send_msg_id "BD_TCL-100" "ERROR" "Unable to find parent cell <$parentCell>!"}
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     catch {common::send_msg_id "BD_TCL-101" "ERROR" "Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."}
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode MirroredMaster -vlnv xilinx.com:interface:lmb_rtl:1.0 DLMB
  create_bd_intf_pin -mode MirroredMaster -vlnv xilinx.com:interface:lmb_rtl:1.0 ILMB

  # Create pins
  create_bd_pin -dir I -type clk LMB_Clk
  create_bd_pin -dir I -type rst SYS_Rst

  # Create instance: dlmb_bram_if_cntlr, and set properties
  set dlmb_bram_if_cntlr [ create_bd_cell -type ip -vlnv xilinx.com:ip:lmb_bram_if_cntlr:4.0 dlmb_bram_if_cntlr ]
  set_property -dict [ list \
CONFIG.C_ECC {0} \
 ] $dlmb_bram_if_cntlr

  # Create instance: dlmb_v10, and set properties
  set dlmb_v10 [ create_bd_cell -type ip -vlnv xilinx.com:ip:lmb_v10:3.0 dlmb_v10 ]

  # Create instance: ilmb_bram_if_cntlr, and set properties
  set ilmb_bram_if_cntlr [ create_bd_cell -type ip -vlnv xilinx.com:ip:lmb_bram_if_cntlr:4.0 ilmb_bram_if_cntlr ]
  set_property -dict [ list \
CONFIG.C_ECC {0} \
 ] $ilmb_bram_if_cntlr

  # Create instance: ilmb_v10, and set properties
  set ilmb_v10 [ create_bd_cell -type ip -vlnv xilinx.com:ip:lmb_v10:3.0 ilmb_v10 ]

  # Create instance: lmb_bram, and set properties
  set lmb_bram [ create_bd_cell -type ip -vlnv xilinx.com:ip:blk_mem_gen:8.3 lmb_bram ]
  set_property -dict [ list \
CONFIG.Memory_Type {True_Dual_Port_RAM} \
CONFIG.use_bram_block {BRAM_Controller} \
 ] $lmb_bram

  # Create interface connections
  connect_bd_intf_net -intf_net microblaze_0_dlmb [get_bd_intf_pins DLMB] [get_bd_intf_pins dlmb_v10/LMB_M]
  connect_bd_intf_net -intf_net microblaze_0_dlmb_bus [get_bd_intf_pins dlmb_bram_if_cntlr/SLMB] [get_bd_intf_pins dlmb_v10/LMB_Sl_0]
  connect_bd_intf_net -intf_net microblaze_0_dlmb_cntlr [get_bd_intf_pins dlmb_bram_if_cntlr/BRAM_PORT] [get_bd_intf_pins lmb_bram/BRAM_PORTA]
  connect_bd_intf_net -intf_net microblaze_0_ilmb [get_bd_intf_pins ILMB] [get_bd_intf_pins ilmb_v10/LMB_M]
  connect_bd_intf_net -intf_net microblaze_0_ilmb_bus [get_bd_intf_pins ilmb_bram_if_cntlr/SLMB] [get_bd_intf_pins ilmb_v10/LMB_Sl_0]
  connect_bd_intf_net -intf_net microblaze_0_ilmb_cntlr [get_bd_intf_pins ilmb_bram_if_cntlr/BRAM_PORT] [get_bd_intf_pins lmb_bram/BRAM_PORTB]

  # Create port connections
  connect_bd_net -net SYS_Rst_1 [get_bd_pins SYS_Rst] [get_bd_pins dlmb_bram_if_cntlr/LMB_Rst] [get_bd_pins dlmb_v10/SYS_Rst] [get_bd_pins ilmb_bram_if_cntlr/LMB_Rst] [get_bd_pins ilmb_v10/SYS_Rst]
  connect_bd_net -net microblaze_0_Clk [get_bd_pins LMB_Clk] [get_bd_pins dlmb_bram_if_cntlr/LMB_Clk] [get_bd_pins dlmb_v10/LMB_Clk] [get_bd_pins ilmb_bram_if_cntlr/LMB_Clk] [get_bd_pins ilmb_v10/LMB_Clk]

  # Restore current instance
  current_bd_instance $oldCurInst
}


# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  variable script_folder

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     catch {common::send_msg_id "BD_TCL-100" "ERROR" "Unable to find parent cell <$parentCell>!"}
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     catch {common::send_msg_id "BD_TCL-101" "ERROR" "Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."}
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports
  set c0_ddr4 [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:ddr4_rtl:1.0 c0_ddr4 ]
  set c0_sys_clk [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:diff_clock_rtl:1.0 c0_sys_clk ]
  set_property -dict [ list \
CONFIG.FREQ_HZ {300120000} \
 ] $c0_sys_clk
  set pcie_7x_mgt [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:pcie_7x_mgt_rtl:1.0 pcie_7x_mgt ]
  set pcie_clk [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:diff_clock_rtl:1.0 pcie_clk ]
  set_property -dict [ list \
CONFIG.FREQ_HZ {100000000} \
 ] $pcie_clk

  # Create ports
  set reset_rtl [ create_bd_port -dir I -type rst reset_rtl ]
  set_property -dict [ list \
CONFIG.POLARITY {ACTIVE_LOW} \
 ] $reset_rtl

  # Create instance: axi_interconnect_0, and set properties
  set axi_interconnect_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_interconnect_0 ]
  set_property -dict [ list \
CONFIG.NUM_MI {7} \
 ] $axi_interconnect_0

  # Create instance: axi_mm2s_mapper_0, and set properties
  set axi_mm2s_mapper_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_mm2s_mapper:1.1 axi_mm2s_mapper_0 ]
  set_property -dict [ list \
CONFIG.TDATA_NUM_BYTES {4} \
 ] $axi_mm2s_mapper_0

  # Create instance: axi_pcie3_0, and set properties
  set axi_pcie3_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_pcie3:3.0 axi_pcie3_0 ]
  set_property -dict [ list \
CONFIG.BASEADDR {0x00000000} \
CONFIG.HIGHADDR {0x001FFFFF} \
CONFIG.axi_data_width {256_bit} \
CONFIG.axisten_freq {250} \
CONFIG.coreclk_freq {500} \
CONFIG.dedicate_perst {false} \
CONFIG.device_port_type {Root_Port_of_PCI_Express_Root_Complex} \
CONFIG.en_axi_master_if {true} \
CONFIG.enable_jtag_dbg {true} \
CONFIG.pcie_blk_locn {X0Y1} \
CONFIG.pf0_bar0_scale {Megabytes} \
CONFIG.pf0_base_class_menu {Bridge_device} \
CONFIG.pf0_class_code {060700} \
CONFIG.pf0_class_code_base {06} \
CONFIG.pf0_class_code_sub {07} \
CONFIG.pf0_device_id {8138} \
CONFIG.pf0_sub_class_interface_menu {CardBus_bridge} \
CONFIG.pl_link_cap_max_link_speed {8.0_GT/s} \
CONFIG.pl_link_cap_max_link_width {X8} \
CONFIG.plltype {QPLL1} \
CONFIG.select_quad {GTH_Quad_228} \
 ] $axi_pcie3_0

  # Create instance: ddr4_0, and set properties
  set ddr4_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:ddr4:2.2 ddr4_0 ]
  set_property -dict [ list \
CONFIG.ADDN_UI_CLKOUT1_FREQ_HZ {100} \
CONFIG.C0.DDR4_AxiAddressWidth {33} \
CONFIG.C0.DDR4_AxiDataWidth {512} \
CONFIG.C0.DDR4_CustomParts {../../../../../../../../adm-pcie-8v3_custom_parts_2400.csv} \
CONFIG.C0.DDR4_DataWidth {64} \
CONFIG.C0.DDR4_InputClockPeriod {3332} \
CONFIG.C0.DDR4_MemoryPart {CUSTOM_MT40A1G8PM-083E} \
CONFIG.C0.DDR4_isCustom {true} \
 ] $ddr4_0

  # Create instance: dummy1_1, and set properties
  set dummy1_1 [ create_bd_cell -type ip -vlnv xilinx.com:hls:dummy1:1.0 dummy1_1 ]

  set_property -dict [ list \
CONFIG.NUM_READ_OUTSTANDING {1} \
CONFIG.NUM_WRITE_OUTSTANDING {1} \
 ] [get_bd_intf_pins /dummy1_1/s_axi_ctrl]

  # Create instance: dummy1_2, and set properties
  set dummy1_2 [ create_bd_cell -type ip -vlnv xilinx.com:hls:dummy1:1.0 dummy1_2 ]

  set_property -dict [ list \
CONFIG.NUM_READ_OUTSTANDING {1} \
CONFIG.NUM_WRITE_OUTSTANDING {1} \
 ] [get_bd_intf_pins /dummy1_2/s_axi_ctrl]

  # Create instance: dummy1_3, and set properties
  set dummy1_3 [ create_bd_cell -type ip -vlnv xilinx.com:hls:dummy1:1.0 dummy1_3 ]

  set_property -dict [ list \
CONFIG.NUM_READ_OUTSTANDING {1} \
CONFIG.NUM_WRITE_OUTSTANDING {1} \
 ] [get_bd_intf_pins /dummy1_3/s_axi_ctrl]

  # Create instance: dummy1_6, and set properties
  set dummy1_6 [ create_bd_cell -type ip -vlnv xilinx.com:hls:dummy1:1.0 dummy1_6 ]

  set_property -dict [ list \
CONFIG.NUM_READ_OUTSTANDING {1} \
CONFIG.NUM_WRITE_OUTSTANDING {1} \
 ] [get_bd_intf_pins /dummy1_6/s_axi_ctrl]

  # Create instance: fir_compiler_0, and set properties
  set fir_compiler_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:fir_compiler:7.2 fir_compiler_0 ]
  set_property -dict [ list \
CONFIG.CoefficientSource {COE_File} \
CONFIG.Coefficient_File {../../../../../../../../FIR_coe/FIR_0.5Hz_4Hz.coe} \
CONFIG.Coefficient_Fractional_Bits {0} \
CONFIG.Coefficient_Sets {1} \
CONFIG.Coefficient_Sign {Signed} \
CONFIG.Coefficient_Structure {Inferred} \
CONFIG.Coefficient_Width {16} \
CONFIG.Data_Width {32} \
CONFIG.Output_Rounding_Mode {Truncate_LSBs} \
CONFIG.Output_Width {32} \
CONFIG.Quantization {Integer_Coefficients} \
 ] $fir_compiler_0

  # Create instance: mdm_1, and set properties
  set mdm_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:mdm:3.2 mdm_1 ]

  # Create instance: microblaze_0, and set properties
  set microblaze_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:microblaze:10.0 microblaze_0 ]
  set_property -dict [ list \
CONFIG.C_CACHE_BYTE_SIZE {8192} \
CONFIG.C_DCACHE_BYTE_SIZE {8192} \
CONFIG.C_DEBUG_ENABLED {1} \
CONFIG.C_D_AXI {1} \
CONFIG.C_D_LMB {1} \
CONFIG.C_I_LMB {1} \
CONFIG.C_USE_DCACHE {1} \
CONFIG.C_USE_ICACHE {1} \
 ] $microblaze_0

  # Create instance: microblaze_0_axi_intc, and set properties
  set microblaze_0_axi_intc [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_intc:4.1 microblaze_0_axi_intc ]
  set_property -dict [ list \
CONFIG.C_HAS_FAST {1} \
 ] $microblaze_0_axi_intc

  # Create instance: microblaze_0_axi_periph, and set properties
  set microblaze_0_axi_periph [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 microblaze_0_axi_periph ]
  set_property -dict [ list \
CONFIG.NUM_MI {5} \
 ] $microblaze_0_axi_periph

  # Create instance: microblaze_0_local_memory
  create_hier_cell_microblaze_0_local_memory [current_bd_instance .] microblaze_0_local_memory

  # Create instance: microblaze_0_xlconcat, and set properties
  set microblaze_0_xlconcat [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 microblaze_0_xlconcat ]

  # Create instance: mv_input_0, and set properties
  set mv_input_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:mv_input:1.0 mv_input_0 ]

  set_property -dict [ list \
CONFIG.NUM_READ_OUTSTANDING {1} \
CONFIG.NUM_WRITE_OUTSTANDING {1} \
 ] [get_bd_intf_pins /mv_input_0/s_axi_CTRL_BUS]

  # Create instance: mv_output_0, and set properties
  set mv_output_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:mv_output:1.0 mv_output_0 ]

  set_property -dict [ list \
CONFIG.NUM_READ_OUTSTANDING {1} \
CONFIG.NUM_WRITE_OUTSTANDING {1} \
 ] [get_bd_intf_pins /mv_output_0/s_axi_CTRL_BUS]

  # Create instance: mv_state_0, and set properties
  set mv_state_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:mv_state:1.0 mv_state_0 ]

  set_property -dict [ list \
CONFIG.NUM_READ_OUTSTANDING {1} \
CONFIG.NUM_WRITE_OUTSTANDING {1} \
 ] [get_bd_intf_pins /mv_state_0/s_axi_CTRL_BUS]

  # Create instance: proc_sys_reset_300M, and set properties
  set proc_sys_reset_300M [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 proc_sys_reset_300M ]

  # Create instance: rst_clk_wiz_0_250M, and set properties
  set rst_clk_wiz_0_250M [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 rst_clk_wiz_0_250M ]

  # Create instance: smartconnect_0, and set properties
  set smartconnect_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:smartconnect:1.0 smartconnect_0 ]
  set_property -dict [ list \
CONFIG.NUM_CLKS {2} \
CONFIG.NUM_SI {11} \
 ] $smartconnect_0

  # Create instance: util_ds_buf, and set properties
  set util_ds_buf [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_ds_buf:2.1 util_ds_buf ]
  set_property -dict [ list \
CONFIG.C_BUF_TYPE {IBUFDSGTE} \
 ] $util_ds_buf

  # Create instance: util_vector_logic_2, and set properties
  set util_vector_logic_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 util_vector_logic_2 ]
  set_property -dict [ list \
CONFIG.C_OPERATION {not} \
CONFIG.C_SIZE {1} \
CONFIG.LOGO_FILE {data/sym_notgate.png} \
 ] $util_vector_logic_2

  # Create instance: vio_0, and set properties
  set vio_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:vio:3.0 vio_0 ]

  # Create instance: xlconstant_0, and set properties
  set xlconstant_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_0 ]
  set_property -dict [ list \
CONFIG.CONST_VAL {0} \
 ] $xlconstant_0

  # Create interface connections
  connect_bd_intf_net -intf_net C0_SYS_CLK_1 [get_bd_intf_ports c0_sys_clk] [get_bd_intf_pins ddr4_0/C0_SYS_CLK]
  connect_bd_intf_net -intf_net S00_AXI_1 [get_bd_intf_pins axi_interconnect_0/S00_AXI] [get_bd_intf_pins microblaze_0_axi_periph/M04_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_0_M00_AXI [get_bd_intf_pins axi_interconnect_0/M00_AXI] [get_bd_intf_pins dummy1_6/s_axi_ctrl]
  connect_bd_intf_net -intf_net axi_interconnect_0_M01_AXI [get_bd_intf_pins axi_interconnect_0/M01_AXI] [get_bd_intf_pins mv_state_0/s_axi_CTRL_BUS]
  connect_bd_intf_net -intf_net axi_interconnect_0_M02_AXI [get_bd_intf_pins axi_interconnect_0/M02_AXI] [get_bd_intf_pins mv_output_0/s_axi_CTRL_BUS]
  connect_bd_intf_net -intf_net axi_interconnect_0_M03_AXI [get_bd_intf_pins axi_interconnect_0/M03_AXI] [get_bd_intf_pins dummy1_1/s_axi_ctrl]
  connect_bd_intf_net -intf_net axi_interconnect_0_M04_AXI [get_bd_intf_pins axi_interconnect_0/M04_AXI] [get_bd_intf_pins dummy1_2/s_axi_ctrl]
  connect_bd_intf_net -intf_net axi_interconnect_0_M05_AXI [get_bd_intf_pins axi_interconnect_0/M05_AXI] [get_bd_intf_pins dummy1_3/s_axi_ctrl]
  connect_bd_intf_net -intf_net axi_interconnect_0_M06_AXI [get_bd_intf_pins axi_interconnect_0/M06_AXI] [get_bd_intf_pins mv_input_0/s_axi_CTRL_BUS]
  connect_bd_intf_net -intf_net axi_mm2s_mapper_0_M_AXI [get_bd_intf_pins axi_mm2s_mapper_0/M_AXI] [get_bd_intf_pins smartconnect_0/S03_AXI]
  connect_bd_intf_net -intf_net axi_mm2s_mapper_0_M_AXIS [get_bd_intf_pins axi_mm2s_mapper_0/M_AXIS] [get_bd_intf_pins fir_compiler_0/S_AXIS_DATA]
  connect_bd_intf_net -intf_net axi_pcie3_0_M_AXI [get_bd_intf_pins axi_pcie3_0/M_AXI] [get_bd_intf_pins smartconnect_0/S00_AXI]
  connect_bd_intf_net -intf_net axi_pcie3_0_pcie_7x_mgt [get_bd_intf_ports pcie_7x_mgt] [get_bd_intf_pins axi_pcie3_0/pcie_7x_mgt]
  connect_bd_intf_net -intf_net ddr4_0_C0_DDR4 [get_bd_intf_ports c0_ddr4] [get_bd_intf_pins ddr4_0/C0_DDR4]
  connect_bd_intf_net -intf_net diff_clock_rtl_1 [get_bd_intf_ports pcie_clk] [get_bd_intf_pins util_ds_buf/CLK_IN_D]
  connect_bd_intf_net -intf_net dummy1_1_m_axi_gmem [get_bd_intf_pins dummy1_1/m_axi_gmem] [get_bd_intf_pins smartconnect_0/S07_AXI]
  connect_bd_intf_net -intf_net dummy1_2_m_axi_gmem [get_bd_intf_pins dummy1_2/m_axi_gmem] [get_bd_intf_pins smartconnect_0/S08_AXI]
  connect_bd_intf_net -intf_net dummy1_3_m_axi_gmem [get_bd_intf_pins dummy1_3/m_axi_gmem] [get_bd_intf_pins smartconnect_0/S09_AXI]
  connect_bd_intf_net -intf_net dummy1_6_m_axi_gmem [get_bd_intf_pins dummy1_6/m_axi_gmem] [get_bd_intf_pins smartconnect_0/S04_AXI]
  connect_bd_intf_net -intf_net fir_compiler_0_M_AXIS_DATA [get_bd_intf_pins axi_mm2s_mapper_0/S_AXIS] [get_bd_intf_pins fir_compiler_0/M_AXIS_DATA]
  connect_bd_intf_net -intf_net microblaze_0_M_AXI_DC [get_bd_intf_pins microblaze_0/M_AXI_DC] [get_bd_intf_pins smartconnect_0/S01_AXI]
  connect_bd_intf_net -intf_net microblaze_0_M_AXI_IC [get_bd_intf_pins microblaze_0/M_AXI_IC] [get_bd_intf_pins smartconnect_0/S02_AXI]
  connect_bd_intf_net -intf_net microblaze_0_axi_dp [get_bd_intf_pins microblaze_0/M_AXI_DP] [get_bd_intf_pins microblaze_0_axi_periph/S00_AXI]
  connect_bd_intf_net -intf_net microblaze_0_axi_periph_M01_AXI [get_bd_intf_pins axi_pcie3_0/S_AXI_CTL] [get_bd_intf_pins microblaze_0_axi_periph/M01_AXI]
  connect_bd_intf_net -intf_net microblaze_0_axi_periph_M02_AXI [get_bd_intf_pins axi_pcie3_0/S_AXI] [get_bd_intf_pins microblaze_0_axi_periph/M02_AXI]
  connect_bd_intf_net -intf_net microblaze_0_axi_periph_M03_AXI [get_bd_intf_pins axi_mm2s_mapper_0/S_AXI] [get_bd_intf_pins microblaze_0_axi_periph/M03_AXI]
  connect_bd_intf_net -intf_net microblaze_0_debug [get_bd_intf_pins mdm_1/MBDEBUG_0] [get_bd_intf_pins microblaze_0/DEBUG]
  connect_bd_intf_net -intf_net microblaze_0_dlmb_1 [get_bd_intf_pins microblaze_0/DLMB] [get_bd_intf_pins microblaze_0_local_memory/DLMB]
  connect_bd_intf_net -intf_net microblaze_0_ilmb_1 [get_bd_intf_pins microblaze_0/ILMB] [get_bd_intf_pins microblaze_0_local_memory/ILMB]
  connect_bd_intf_net -intf_net microblaze_0_intc_axi [get_bd_intf_pins microblaze_0_axi_intc/s_axi] [get_bd_intf_pins microblaze_0_axi_periph/M00_AXI]
  connect_bd_intf_net -intf_net microblaze_0_interrupt [get_bd_intf_pins microblaze_0/INTERRUPT] [get_bd_intf_pins microblaze_0_axi_intc/interrupt]
  connect_bd_intf_net -intf_net mv_input_0_m_axi_mem [get_bd_intf_pins mv_input_0/m_axi_mem] [get_bd_intf_pins smartconnect_0/S10_AXI]
  connect_bd_intf_net -intf_net mv_output_0_m_axi_mem [get_bd_intf_pins mv_output_0/m_axi_mem] [get_bd_intf_pins smartconnect_0/S06_AXI]
  connect_bd_intf_net -intf_net mv_state_0_m_axi_mem [get_bd_intf_pins mv_state_0/m_axi_mem] [get_bd_intf_pins smartconnect_0/S05_AXI]
  connect_bd_intf_net -intf_net smartconnect_0_M00_AXI [get_bd_intf_pins ddr4_0/C0_DDR4_S_AXI] [get_bd_intf_pins smartconnect_0/M00_AXI]

  # Create port connections
  connect_bd_net -net Net [get_bd_pins microblaze_0_xlconcat/In0] [get_bd_pins microblaze_0_xlconcat/In1] [get_bd_pins xlconstant_0/dout]
  connect_bd_net -net axi_pcie3_0_axi_aresetn [get_bd_pins axi_interconnect_0/ARESETN] [get_bd_pins axi_interconnect_0/M00_ARESETN] [get_bd_pins axi_interconnect_0/M01_ARESETN] [get_bd_pins axi_interconnect_0/M02_ARESETN] [get_bd_pins axi_interconnect_0/M03_ARESETN] [get_bd_pins axi_interconnect_0/M04_ARESETN] [get_bd_pins axi_interconnect_0/M05_ARESETN] [get_bd_pins axi_interconnect_0/M06_ARESETN] [get_bd_pins axi_interconnect_0/S00_ARESETN] [get_bd_pins axi_mm2s_mapper_0/aresetn] [get_bd_pins axi_pcie3_0/axi_aresetn] [get_bd_pins dummy1_1/ap_rst_n] [get_bd_pins dummy1_2/ap_rst_n] [get_bd_pins dummy1_3/ap_rst_n] [get_bd_pins dummy1_6/ap_rst_n] [get_bd_pins microblaze_0_axi_periph/M03_ARESETN] [get_bd_pins microblaze_0_axi_periph/M04_ARESETN] [get_bd_pins mv_input_0/ap_rst_n] [get_bd_pins mv_output_0/ap_rst_n] [get_bd_pins mv_state_0/ap_rst_n]
  connect_bd_net -net ddr4_0_c0_ddr4_ui_clk [get_bd_pins ddr4_0/c0_ddr4_ui_clk] [get_bd_pins proc_sys_reset_300M/slowest_sync_clk] [get_bd_pins smartconnect_0/aclk]
  connect_bd_net -net ddr4_0_c0_ddr4_ui_clk_sync_rst [get_bd_pins ddr4_0/c0_ddr4_ui_clk_sync_rst] [get_bd_pins proc_sys_reset_300M/ext_reset_in] [get_bd_pins rst_clk_wiz_0_250M/ext_reset_in] [get_bd_pins util_vector_logic_2/Op1]
  connect_bd_net -net ddr4_0_c0_init_calib_complete [get_bd_pins ddr4_0/c0_init_calib_complete] [get_bd_pins vio_0/probe_in0]
  connect_bd_net -net mdm_1_debug_sys_rst [get_bd_pins mdm_1/Debug_SYS_Rst] [get_bd_pins rst_clk_wiz_0_250M/mb_debug_sys_rst]
  connect_bd_net -net microblaze_0_Clk [get_bd_pins axi_interconnect_0/ACLK] [get_bd_pins axi_interconnect_0/M00_ACLK] [get_bd_pins axi_interconnect_0/M01_ACLK] [get_bd_pins axi_interconnect_0/M02_ACLK] [get_bd_pins axi_interconnect_0/M03_ACLK] [get_bd_pins axi_interconnect_0/M04_ACLK] [get_bd_pins axi_interconnect_0/M05_ACLK] [get_bd_pins axi_interconnect_0/M06_ACLK] [get_bd_pins axi_interconnect_0/S00_ACLK] [get_bd_pins axi_mm2s_mapper_0/aclk] [get_bd_pins axi_pcie3_0/axi_aclk] [get_bd_pins dummy1_1/ap_clk] [get_bd_pins dummy1_2/ap_clk] [get_bd_pins dummy1_3/ap_clk] [get_bd_pins dummy1_6/ap_clk] [get_bd_pins fir_compiler_0/aclk] [get_bd_pins microblaze_0/Clk] [get_bd_pins microblaze_0_axi_intc/processor_clk] [get_bd_pins microblaze_0_axi_intc/s_axi_aclk] [get_bd_pins microblaze_0_axi_periph/ACLK] [get_bd_pins microblaze_0_axi_periph/M00_ACLK] [get_bd_pins microblaze_0_axi_periph/M01_ACLK] [get_bd_pins microblaze_0_axi_periph/M02_ACLK] [get_bd_pins microblaze_0_axi_periph/M03_ACLK] [get_bd_pins microblaze_0_axi_periph/M04_ACLK] [get_bd_pins microblaze_0_axi_periph/S00_ACLK] [get_bd_pins microblaze_0_local_memory/LMB_Clk] [get_bd_pins mv_input_0/ap_clk] [get_bd_pins mv_output_0/ap_clk] [get_bd_pins mv_state_0/ap_clk] [get_bd_pins rst_clk_wiz_0_250M/slowest_sync_clk] [get_bd_pins smartconnect_0/aclk1] [get_bd_pins vio_0/clk]
  connect_bd_net -net microblaze_0_intr [get_bd_pins microblaze_0_axi_intc/intr] [get_bd_pins microblaze_0_xlconcat/dout]
  connect_bd_net -net proc_sys_reset_300M_peripheral_aresetn [get_bd_pins ddr4_0/c0_ddr4_aresetn] [get_bd_pins proc_sys_reset_300M/peripheral_aresetn]
  connect_bd_net -net reset_rtl_1 [get_bd_ports reset_rtl] [get_bd_pins axi_pcie3_0/sys_rst_n]
  connect_bd_net -net rst_clk_wiz_0_250M_bus_struct_reset [get_bd_pins microblaze_0_local_memory/SYS_Rst] [get_bd_pins rst_clk_wiz_0_250M/bus_struct_reset]
  connect_bd_net -net rst_clk_wiz_0_250M_interconnect_aresetn [get_bd_pins microblaze_0_axi_periph/ARESETN] [get_bd_pins rst_clk_wiz_0_250M/interconnect_aresetn]
  connect_bd_net -net rst_clk_wiz_0_250M_mb_reset [get_bd_pins microblaze_0/Reset] [get_bd_pins microblaze_0_axi_intc/processor_rst] [get_bd_pins rst_clk_wiz_0_250M/mb_reset]
  connect_bd_net -net rst_clk_wiz_0_250M_peripheral_aresetn [get_bd_pins microblaze_0_axi_intc/s_axi_aresetn] [get_bd_pins microblaze_0_axi_periph/M00_ARESETN] [get_bd_pins microblaze_0_axi_periph/M01_ARESETN] [get_bd_pins microblaze_0_axi_periph/M02_ARESETN] [get_bd_pins microblaze_0_axi_periph/S00_ARESETN] [get_bd_pins rst_clk_wiz_0_250M/peripheral_aresetn]
  connect_bd_net -net util_ds_buf_IBUF_DS_ODIV2 [get_bd_pins axi_pcie3_0/refclk] [get_bd_pins util_ds_buf/IBUF_DS_ODIV2]
  connect_bd_net -net util_ds_buf_IBUF_OUT [get_bd_pins axi_pcie3_0/sys_clk_gt] [get_bd_pins util_ds_buf/IBUF_OUT]
  connect_bd_net -net util_vector_logic_2_Res [get_bd_pins smartconnect_0/aresetn] [get_bd_pins util_vector_logic_2/Res]
  connect_bd_net -net vio_0_probe_out0 [get_bd_pins ddr4_0/sys_rst] [get_bd_pins vio_0/probe_out0]

  # Create address segments
  create_bd_addr_seg -range 0x80000000 -offset 0x80000000 [get_bd_addr_spaces axi_mm2s_mapper_0/Bridge] [get_bd_addr_segs ddr4_0/C0_DDR4_MEMORY_MAP/C0_DDR4_ADDRESS_BLOCK] SEG_ddr4_0_C0_DDR4_ADDRESS_BLOCK
  create_bd_addr_seg -range 0x80000000 -offset 0x80000000 [get_bd_addr_spaces axi_pcie3_0/M_AXI] [get_bd_addr_segs ddr4_0/C0_DDR4_MEMORY_MAP/C0_DDR4_ADDRESS_BLOCK] SEG_ddr4_0_C0_DDR4_ADDRESS_BLOCK
  create_bd_addr_seg -range 0x80000000 -offset 0x80000000 [get_bd_addr_spaces dummy1_1/Data_m_axi_gmem] [get_bd_addr_segs ddr4_0/C0_DDR4_MEMORY_MAP/C0_DDR4_ADDRESS_BLOCK] SEG_ddr4_0_C0_DDR4_ADDRESS_BLOCK
  create_bd_addr_seg -range 0x80000000 -offset 0x80000000 [get_bd_addr_spaces dummy1_2/Data_m_axi_gmem] [get_bd_addr_segs ddr4_0/C0_DDR4_MEMORY_MAP/C0_DDR4_ADDRESS_BLOCK] SEG_ddr4_0_C0_DDR4_ADDRESS_BLOCK
  create_bd_addr_seg -range 0x80000000 -offset 0x80000000 [get_bd_addr_spaces dummy1_3/Data_m_axi_gmem] [get_bd_addr_segs ddr4_0/C0_DDR4_MEMORY_MAP/C0_DDR4_ADDRESS_BLOCK] SEG_ddr4_0_C0_DDR4_ADDRESS_BLOCK
  create_bd_addr_seg -range 0x80000000 -offset 0x80000000 [get_bd_addr_spaces dummy1_6/Data_m_axi_gmem] [get_bd_addr_segs ddr4_0/C0_DDR4_MEMORY_MAP/C0_DDR4_ADDRESS_BLOCK] SEG_ddr4_0_C0_DDR4_ADDRESS_BLOCK
  create_bd_addr_seg -range 0x00010000 -offset 0x44A00000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs axi_mm2s_mapper_0/S_AXI/Reg] SEG_axi_mm2s_mapper_0_Reg
  create_bd_addr_seg -range 0x00100000 -offset 0x76000000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs axi_pcie3_0/S_AXI/BAR0] SEG_axi_pcie3_0_BAR0
  create_bd_addr_seg -range 0x10000000 -offset 0x10000000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs axi_pcie3_0/S_AXI_CTL/CTL0] SEG_axi_pcie3_0_CTL0
  create_bd_addr_seg -range 0x80000000 -offset 0x80000000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs ddr4_0/C0_DDR4_MEMORY_MAP/C0_DDR4_ADDRESS_BLOCK] SEG_ddr4_0_C0_DDR4_ADDRESS_BLOCK
  create_bd_addr_seg -range 0x80000000 -offset 0x80000000 [get_bd_addr_spaces microblaze_0/Instruction] [get_bd_addr_segs ddr4_0/C0_DDR4_MEMORY_MAP/C0_DDR4_ADDRESS_BLOCK] SEG_ddr4_0_C0_DDR4_ADDRESS_BLOCK
  create_bd_addr_seg -range 0x00020000 -offset 0x00000000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs microblaze_0_local_memory/dlmb_bram_if_cntlr/SLMB/Mem] SEG_dlmb_bram_if_cntlr_Mem
  create_bd_addr_seg -range 0x00010000 -offset 0x44A20000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs dummy1_1/s_axi_ctrl/Reg] SEG_dummy1_1_Reg
  create_bd_addr_seg -range 0x00010000 -offset 0x44A30000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs dummy1_2/s_axi_ctrl/Reg] SEG_dummy1_2_Reg
  create_bd_addr_seg -range 0x00010000 -offset 0x44A40000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs dummy1_3/s_axi_ctrl/Reg] SEG_dummy1_3_Reg
  create_bd_addr_seg -range 0x00010000 -offset 0x44A70000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs dummy1_6/s_axi_ctrl/Reg] SEG_dummy1_6_Reg
  create_bd_addr_seg -range 0x00020000 -offset 0x00000000 [get_bd_addr_spaces microblaze_0/Instruction] [get_bd_addr_segs microblaze_0_local_memory/ilmb_bram_if_cntlr/SLMB/Mem] SEG_ilmb_bram_if_cntlr_Mem
  create_bd_addr_seg -range 0x00010000 -offset 0x41200000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs microblaze_0_axi_intc/S_AXI/Reg] SEG_microblaze_0_axi_intc_Reg
  create_bd_addr_seg -range 0x00010000 -offset 0x44A10000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs mv_input_0/s_axi_CTRL_BUS/Reg] SEG_mv_input_0_Reg
  create_bd_addr_seg -range 0x00010000 -offset 0x44A50000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs mv_output_0/s_axi_CTRL_BUS/Reg] SEG_mv_output_0_Reg
  create_bd_addr_seg -range 0x00010000 -offset 0x44A60000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs mv_state_0/s_axi_CTRL_BUS/Reg] SEG_mv_state_0_Reg
  create_bd_addr_seg -range 0x80000000 -offset 0x80000000 [get_bd_addr_spaces mv_input_0/Data_m_axi_mem] [get_bd_addr_segs ddr4_0/C0_DDR4_MEMORY_MAP/C0_DDR4_ADDRESS_BLOCK] SEG_ddr4_0_C0_DDR4_ADDRESS_BLOCK
  create_bd_addr_seg -range 0x80000000 -offset 0x80000000 [get_bd_addr_spaces mv_output_0/Data_m_axi_mem] [get_bd_addr_segs ddr4_0/C0_DDR4_MEMORY_MAP/C0_DDR4_ADDRESS_BLOCK] SEG_ddr4_0_C0_DDR4_ADDRESS_BLOCK
  create_bd_addr_seg -range 0x80000000 -offset 0x80000000 [get_bd_addr_spaces mv_state_0/Data_m_axi_mem] [get_bd_addr_segs ddr4_0/C0_DDR4_MEMORY_MAP/C0_DDR4_ADDRESS_BLOCK] SEG_ddr4_0_C0_DDR4_ADDRESS_BLOCK


  # Restore current instance
  current_bd_instance $oldCurInst

  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


