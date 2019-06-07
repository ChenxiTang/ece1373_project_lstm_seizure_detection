file mkdir vivado_designs/new/prj_design1.sdk
file mkdir hw.sdk
file copy -force vivado_designs/new/prj_design1.runs/impl_1/design_1_wrapper.sysdef hw.sdk/design_1_wrapper.hdf

launch_sdk -workspace hw.sdk -hwspec hw.sdk/design_1_wrapper.hdf
