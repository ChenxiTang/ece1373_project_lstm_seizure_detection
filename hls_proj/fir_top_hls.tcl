cd hls_proj
open_project FIR_top_proj
set_top fir_top
add_files ../c_code/fir_top/fir_top.cpp
add_files ../c_code/fir_top/channel_1_band_5.cpp
add_files ../c_code/fir_top/sig_band_energy.h

open_solution "solution1"
set_part {xcvu095-ffvc1517-2-e} -tool vivado
create_clock -period 250MHz -name default
config_interface -m_axi_addr64 -m_axi_offset off -register_io off

csynth_design

export_design -format ip_catalog
