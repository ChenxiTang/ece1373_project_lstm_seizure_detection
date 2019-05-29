cd hls_proj
open_project mv_input_proj 
set_top mv_input
add_files ../c_code/matrix_vector_mult/mv_input.cpp 

open_solution "solution1"

set_part {xcvu095-ffvc1517-2-e} -tool vivado

create_clock -period 250MHz -name default

config_interface -m_axi_addr64 -m_axi_offset off -register_io off

csynth_design

export_design -format ip_catalog
