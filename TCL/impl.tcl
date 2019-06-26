#implementation in non-project mode

# Opt Design 
opt_design -directive Explore
write_checkpoint -force $rootDir/${designName}_post_opt.dcp

report_timing_summary -file $rootDir/${designName}_post_opt_tim.rpt
report_utilization -file $rootDir/${designName}_post_opt_util.rpt

# Place Design
place_design -directive ExtraNetDelay_low 
write_checkpoint -force $rootDir/${designName}_post_place.dcp

report_timing_summary -file $rootDir/${designName}_post_place_tim.rpt
report_utilization -file $rootDir/${designName}_post_place_util.rpt
set WNS1 [ get_property SLACK [get_timing_paths -max_paths 1 -nworst 1 -setup] ]

# Post Place Phys Opt
phys_opt_design -directive AggressiveExplore
write_checkpoint -force $rootDir/${designName}_post_place_physopt.dcp

report_timing_summary -file $rootDir/${designName}_post_place_physopt_tim.rpt
report_utilization -file $rootDir/${designName}_post_place_physopt_util.rpt


# Route Design
route_design -directive NoTimingRelaxation
write_checkpoint -force $rootDir/${designName}_post_route.dcp

report_timing_summary -file $rootDir/${designName}_post_route_tim.rpt
report_utilization -hierarchical -file $rootDir/${designName}_post_route_util.rpt

#post rout phys_opt_design
phys_opt_design -directive AggressiveExplore
write_checkpoint -force $rootDir/${designName}_post_route_physopt.dcp

report_timing_summary -file $rootDir/${designName}_post_route_physopt_tim.rpt
report_utilization -file $rootDir/${designName}_post_route_physopt_util.rpt

# Write out bitfile
set BUILD_DATE [ clock format [ clock seconds ] -format %d%m%Y ]
set BUILD_TIME [ clock format [ clock seconds ] -format %H%M%S ]
write_debug_probes -force $rootDir/${designName}_${BUILD_DATE}_${BUILD_TIME}.ltx
write_bitstream -force $rootDir/${designName}_${BUILD_DATE}_${BUILD_TIME}.bit -force
