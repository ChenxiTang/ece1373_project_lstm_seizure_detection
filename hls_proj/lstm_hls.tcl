cd hls_proj
open_project lstm_proj
set_top lstm
add_files ../c_code/ElemWiseTanh/ElemWiseTanh.cpp
add_files ../c_code/ElemWiseSigmoid/ElemWiseSigmoid.cpp
add_files ../c_code/ElemWiseVecAdd/ElemWiseVecAdd.cpp
add_files ../c_code/ElemWiseVecMul/ElemWiseVecMul.cpp
add_files ../c_code/matrix_vector_mult/mv_input.cpp
add_files ../c_code/matrix_vector_mult/mv_output.cpp
add_files ../c_code/matrix_vector_mult/mv_state.cpp


add_files ../c_code/top/lstm.cpp
add_files ../c_code/top/lstm_test.cpp -cflags "-I .  -std=c++0x"

add_files ../data/tensorflow_data/bi.txt
add_files ../data/tensorflow_data/bc.txt
add_files ../data/tensorflow_data/bf.txt
add_files ../data/tensorflow_data/bo.txt
add_files ../data/tensorflow_data/by.txt

add_files ../data/tensorflow_data/Whc.txt
add_files ../data/tensorflow_data/Whf.txt
add_files ../data/tensorflow_data/Whi.txt
add_files ../data/tensorflow_data/Who.txt

add_files ../data/tensorflow_data/Wxc.txt
add_files ../data/tensorflow_data/Wxf.txt
add_files ../data/tensorflow_data/Wxi.txt
add_files ../data/tensorflow_data/Wxo.txt

add_files ../data/tensorflow_data/Wy.txt
add_files ../data/tensorflow_data/x_test_se.txt
add_files ../data/tensorflow_data/predictions_series.txt
add_files ../data/tensorflow_data/states_series.txt
add_files ../data/tensorflow_data/logits_series.txt
add_files -tb ../c_code/top/lstm_test.cpp -cflags "-I .  -std=c++0x"
open_solution "solution1"
set_part {xcvu095-ffvc1517-2-e} -tool vivado
create_clock -period 250MHz -name default
config_interface -m_axi_addr64 -m_axi_offset off -register_io off
#csim_design -compiler gcc
csynth_design
#cosim_design
export_design -format ip_catalog
