file mkdir hw.sdk
file copy -force vivado_designs/test_design2/prj_design2.runs/impl_1/design_1_wrapper.sysdef hw.sdk/design_1_wrapper.hdf
launch_sdk -workspace hw.sdk -hwspec hw.sdk/design_1_wrapper.hdf
