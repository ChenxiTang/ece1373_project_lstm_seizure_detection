#implementation in non-project mode

# Opt Design 
opt_design -directive Explore
write_checkpoint -force $rootDir/${designName}_post_opt.dcp

report_timing_summary -file $rootDir/${designName}_post_opt_tim.rpt
report_utilization -file $rootDir/${designName}_post_opt_util.rpt

# Place Design
place_design -directive Explore 
write_checkpoint -force $rootDir/${designName}_post_place.dcp

report_timing_summary -file $rootDir/${designName}_post_place_tim.rpt
report_utilization -file $rootDir/${designName}_post_place_util.rpt
set WNS1 [ get_property SLACK [get_timing_paths -max_paths 1 -nworst 1 -setup] ]

# Post Place Phys Opt
# phys_opt_design -directive AggressiveExplore
# write_checkpoint -force $rootDir/${designName}_post_place_physopt.dcp

# report_timing_summary -file $rootDir/${designName}_post_place_physopt_tim.rpt
# report_utilization -file $rootDir/${designName}_post_place_physopt_util.rpt

if {$WNS1 < 0.000} {
	set N 5
    for {set i 0} {$i < $N} {incr i} {
        phys_opt_design -directive AggressiveExplore 
        phys_opt_design -directive AggressiveFanoutOpt
        phys_opt_design -directive AlternateReplication
    }
    report_timing_summary -file $rootDir/${designName}_post_place_physopt_tim.rpt
    report_design_analysis -logic_level_distribution \
        -of_timing_paths [get_timing_paths -max_paths 10000 \
        -slack_lesser_than 0] \ 
        -file $rootDir/post_place_physopt_vios.rpt
    write_checkpoint -force $rootDir/${designName}_post_place_physopt.dcp
}
# Route Design
route_design -directive Explore
write_checkpoint -force $rootDir/${designName}_post_route.dcp

report_timing_summary -file $rootDir/${designName}_post_route_tim.rpt
report_utilization -hierarchical -file $rootDir/${designName}_post_route_util.rpt

set WNS [get_property SLACK [get_timing_paths -max_paths 1 -nworst 1 -setup]]
puts "Post Route WNS = $WNS"
# Write out bitfile
set BUILD_DATE [ clock format [ clock seconds ] -format %d%m%Y ]
set BUILD_TIME [ clock format [ clock seconds ] -format %H%M%S ]
write_debug_probes -force $rootDir/${designName}_${BUILD_DATE}_${BUILD_TIME}_${WNS}ns.ltx
write_bitstream -force $rootDir/${designName}_${BUILD_DATE}_${BUILD_TIME}_${WNS}ns.bit \
 -bin_file