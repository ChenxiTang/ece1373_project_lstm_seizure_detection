cd hls_proj
open_project LSTM_proj
set_top lstm 
add_files ../c_code/ElemWiseVecAdd/ElemWiseVecAdd.cpp
add_files ../c_code/ElemWiseVecMul/ElemWiseVecMul.cpp
add_files ../c_code/ElemWiseVecTanh/ElemWiseVecTanh.cpp
add_files ../c_code/ElemWiseVecSigmoid/ElemWiseVecSigmoid.cpp
add_files ../c_code/matrix_vector_mult/mv_state.cpp
add_files ../c_code/matrix_vector_mult/mv_input.cpp
add_files ../c_code/matrix_vector_mult/mv_output.cpp
add_files ../c_code/top/lstm.cpp

add_files -tb ../c_code/ElemWiseVecAdd_test.cpp -cflags "-I .  -std=c++0x"
open_solution "solution1"
set_part {xcvu095-ffvc1517-2-e} -tool vivado
create_clock -period 250MHz -name default
config_interface -m_axi_addr64 -m_axi_offset off -register_io off
#csim_design -compiler gcc
csynth_design
#cosim_design
export_design -format ip_catalog
