##TCL file for implementation, and generate bitstream in non-project mode

read_checkpoint -cell design_1_i/design_1 vivado_designs/new/prj.dcp

opt_design -directive Explore
place_design -directive Explore
phys_opt_design -directive Explore
phys_opt_design -directive Explore -force_replication_on_nets [get_nets microblaze_0_Clk]

write_checkpoint -force vivado_designs/new_routed.dcp
write_bitstream -force vivado_designs/prj.bit 
report_timing_summary -delay_type min_max -report_unconstrained -check_timing_verbose -max_paths 10 -input_pins -name timing_1 -file 8v3_shell/new.timing
