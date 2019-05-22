# Create interface connections
  connect_bd_intf_net -intf_net axi_smc_M00_AXI [get_bd_intf_pins axi_smc/M00_AXI] [get_bd_intf_pins ddr4_0/C0_DDR4_S_AXI]
  connect_bd_intf_net -intf_net ddr4_0_C0_DDR4 [get_bd_intf_ports c0_ddr4] [get_bd_intf_pins ddr4_0/C0_DDR4]
  connect_bd_intf_net -intf_net diff_clock_rtl_1 [get_bd_intf_ports pcie_clk] [get_bd_intf_pins util_ds_buf/CLK_IN_D]
  connect_bd_intf_net -intf_net diff_clock_rtl_2 [get_bd_intf_ports c0_sys_clk] [get_bd_intf_pins ddr4_0/C0_SYS_CLK]
  connect_bd_intf_net -intf_net pr_decoupler_0_rp_ctrl [get_bd_intf_pins pr_decoupler_0/rp_ctrl] [get_bd_intf_pins pr_region/s_axi]
connect_bd_intf_net -intf_net [get_bd_intf_nets pr_decoupler_0_rp_ctrl] [get_bd_intf_pins pr_decoupler_0/rp_ctrl] [get_bd_intf_pins system_ila_0/SLOT_1_AXI]
  connect_bd_intf_net -intf_net pr_decoupler_0_s_gmem [get_bd_intf_pins axi_smc/S01_AXI] [get_bd_intf_pins pr_decoupler_0/s_gmem]
connect_bd_intf_net -intf_net [get_bd_intf_nets pr_decoupler_0_s_gmem] [get_bd_intf_pins axi_smc/S01_AXI] [get_bd_intf_pins system_ila_0/SLOT_0_AXI]
  connect_bd_intf_net -intf_net pr_region_m_axi [get_bd_intf_pins pr_decoupler_0/rp_gmem] [get_bd_intf_pins pr_region/m_axi]
  connect_bd_intf_net -intf_net xdma_0_M_AXI [get_bd_intf_pins axi_smc/S00_AXI] [get_bd_intf_pins xdma_0/M_AXI]
  connect_bd_intf_net -intf_net xdma_0_M_AXI_LITE [get_bd_intf_pins xdma_0/M_AXI_LITE] [get_bd_intf_pins xdma_0_axi_periph/S00_AXI]
  connect_bd_intf_net -intf_net xdma_0_axi_periph_M00_AXI [get_bd_intf_pins pr_decoupler_0/s_axi_reg] [get_bd_intf_pins xdma_0_axi_periph/M00_AXI]
  connect_bd_intf_net -intf_net xdma_0_axi_periph_M01_AXI [get_bd_intf_pins pr_decoupler_0/s_ctrl] [get_bd_intf_pins xdma_0_axi_periph/M01_AXI]
  connect_bd_intf_net -intf_net xdma_0_axi_periph_M02_AXI [get_bd_intf_pins axi_gpio_0/S_AXI] [get_bd_intf_pins xdma_0_axi_periph/M02_AXI]
  connect_bd_intf_net -intf_net xdma_0_pcie_mgt [get_bd_intf_ports pcie_7x_mgt_rtl] [get_bd_intf_pins xdma_0/pcie_mgt]

  # Create port connections
  connect_bd_net -net S00_ACLK_1 [get_bd_pins axi_gpio_0/s_axi_aclk] [get_bd_pins axi_smc/aclk1] [get_bd_pins pr_region/S00_ACLK] [get_bd_pins rst_ddr4_0_300M/slowest_sync_clk] [get_bd_pins system_ila_0/clk] [get_bd_pins vio_0/clk] [get_bd_pins xdma_0/axi_aclk] [get_bd_pins xdma_0_axi_periph/ACLK] [get_bd_pins xdma_0_axi_periph/M00_ACLK] [get_bd_pins xdma_0_axi_periph/M01_ACLK] [get_bd_pins xdma_0_axi_periph/M02_ACLK] [get_bd_pins xdma_0_axi_periph/S00_ACLK]
  #connect_bd_net -net S00_ARESETN_1 [get_bd_pins decouple_resetn/Res] [get_bd_pins pr_region/S00_ARESETN]
  connect_bd_net -net ddr4_0_c0_ddr4_ui_clk [get_bd_pins axi_smc/aclk] [get_bd_pins ddr4_0/c0_ddr4_ui_clk] [get_bd_pins proc_sys_reset_0/slowest_sync_clk]
  connect_bd_net -net ddr4_0_c0_ddr4_ui_clk_sync_rst [get_bd_pins ddr4_0/c0_ddr4_ui_clk_sync_rst] [get_bd_pins proc_sys_reset_0/aux_reset_in] [get_bd_pins rst_ddr4_0_300M/aux_reset_in]
  connect_bd_net -net ddr4_0_c0_init_calib_complete [get_bd_pins ddr4_0/c0_init_calib_complete] [get_bd_pins vio_0/probe_in0]
  #connect_bd_net -net pr_decoupler_0_decouple_status [get_bd_pins pr_decoupler_0/decouple_status] [get_bd_pins util_vector_logic_1/Op1]
  connect_bd_net -net proc_sys_reset_0_peripheral_aresetn [get_bd_pins ddr4_0/c0_ddr4_aresetn] [get_bd_pins proc_sys_reset_0/peripheral_aresetn]
  connect_bd_net -net reset_rtl_1 [get_bd_ports reset_rtl] [get_bd_pins xdma_0/sys_rst_n]
  connect_bd_net -net resetn_gate_Res [get_bd_pins axi_smc/aresetn] [get_bd_pins proc_sys_reset_0/ext_reset_in] [get_bd_pins rst_ddr4_0_300M/ext_reset_in] [get_bd_pins xdma_0/axi_aresetn] [get_bd_pins xdma_0_axi_periph/S00_ARESETN]
  #connect_bd_net -net rst_ddr4_0_300M_interconnect_aresetn [get_bd_pins pr_decoupler_0/s_axi_reg_aresetn] [get_bd_pins rst_ddr4_0_300M/interconnect_aresetn] [get_bd_pins system_ila_0/resetn] [get_bd_pins xdma_0_axi_periph/ARESETN]
  #connect_bd_net -net rst_ddr4_0_300M_peripheral_aresetn [get_bd_pins axi_gpio_0/s_axi_aresetn] [get_bd_pins decouple_resetn/Op2] [get_bd_pins rst_ddr4_0_300M/peripheral_aresetn] [get_bd_pins xdma_0_axi_periph/M00_ARESETN] [get_bd_pins xdma_0_axi_periph/M01_ARESETN] [get_bd_pins xdma_0_axi_periph/M02_ARESETN]
  connect_bd_net -net util_ds_buf_IBUF_DS_ODIV2 [get_bd_pins util_ds_buf/IBUF_DS_ODIV2] [get_bd_pins xdma_0/sys_clk]
  connect_bd_net -net util_ds_buf_IBUF_OUT [get_bd_pins util_ds_buf/IBUF_OUT] [get_bd_pins xdma_0/sys_clk_gt]
  #connect_bd_net -net util_vector_logic_1_Res [get_bd_pins decouple_resetn/Op1] [get_bd_pins util_vector_logic_1/Res]
  connect_bd_net -net vio_0_probe_out0 [get_bd_pins ddr4_0/sys_rst] [get_bd_pins vio_0/probe_out0]
  connect_bd_net -net vio_0_probe_out1 [get_bd_pins axi_gpio_0/gpio_io_i] [get_bd_pins vio_0/probe_out1]

  # Create address segments
  create_bd_addr_seg -range 0x00010000 -offset 0x00090000 [get_bd_addr_spaces xdma_0/M_AXI_LITE] [get_bd_addr_segs axi_gpio_0/S_AXI/Reg] SEG_axi_gpio_0_Reg
  create_bd_addr_seg -range 0x000200000000 -offset 0x00000000 [get_bd_addr_spaces xdma_0/M_AXI] [get_bd_addr_segs ddr4_0/C0_DDR4_MEMORY_MAP/C0_DDR4_ADDRESS_BLOCK] SEG_ddr4_0_C0_DDR4_ADDRESS_BLOCK
  create_bd_addr_seg -range 0x00080000 -offset 0x00000000 [get_bd_addr_spaces xdma_0/M_AXI_LITE] [get_bd_addr_segs pr_region/dummy1_0/s_axi_ctrl/Reg] SEG_dummy1_0_Reg
  create_bd_addr_seg -range 0x00010000 -offset 0x00080000 [get_bd_addr_spaces xdma_0/M_AXI_LITE] [get_bd_addr_segs pr_decoupler_0/s_axi_reg/Reg] SEG_pr_decoupler_0_Reg
  create_bd_addr_seg -range 0x000200000000 -offset 0x00000000 [get_bd_addr_spaces pr_region/dummy1_0/Data_m_axi_gmem] [get_bd_addr_segs ddr4_0/C0_DDR4_MEMORY_MAP/C0_DDR4_ADDRESS_BLOCK] SEG_ddr4_0_C0_DDR4_ADDRESS_BLOCK
