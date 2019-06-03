cd hls_proj
open_project ElemWiseSigmoid_proj
set_top ElemWiseSigmoid 
add_files ../c_code/ElemWiseSigmoid/ElemWiseSigmoid.cpp
add_files -tb ../c_code/ElemWiseSigmoid_test.cpp -cflags "-I .  -std=c++0x"
open_solution "solution1"
set_part {xcvu095-ffvc1517-2-e} -tool vivado
create_clock -period 250MHz -name default
config_interface -m_axi_addr64 -m_axi_offset off -register_io off
#csim_design -compiler gcc
csynth_design
#cosim_design
export_design -format ip_catalog
