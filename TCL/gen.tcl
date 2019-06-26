##TCL file for synthesise, implementation, and generate bitstream in non-project mode


make_wrapper -files [get_files $dir/$designName.srcs/sources_1/bd/design_1/design_1.bd] -top
add_files -norecurse $dir/$designName.srcs/sources_1/bd/design_1/hdl/design_1_wrapper.v
update_compile_order -fileset sources_1



generate_target {synthesis implementation} [get_files $dir/$designName.srcs/sources_1/bd/design_1/design_1.bd] -force
export_ip_user_files -of_objects [get_files $dir/$designName.srcs/sources_1/bd/design_1/design_1.bd] -no_script -sync -force -quiet

set ooc_runs [get_runs *_synth*]
foreach run $ooc_runs { reset_run $run }


create_ip_run [get_files -of_objects [get_fileset sources_1] $dir/$designName.srcs/sources_1/bd/design_1/design_1.bd]
launch_runs [get_runs *_synth*] -jobs 24

foreach run_name [get_runs *_synth*] {
  wait_on_run ${run_name}
}

eval "synth_design $SYNTH_ARGS -top design_1_wrapper -part $partNU -mode out_of_context"

write_checkpoint -force $rootDir/$projName.dcp
