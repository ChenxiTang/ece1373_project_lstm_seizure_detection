all_hls: ElemWiseTanh_hls ElemWiseSigmoid_hls ElemWiseVecAdd_hls ElemWiseVecMul_hls mv_input_hls mv_output_hls mv_state_hls fir_top_hls


ElemWiseTanh_hls: 
	vivado_hls hls_proj/ElemWiseTanh_hls.tcl

ElemWiseSigmoid_hls:
	vivado_hls hls_proj/ElemWiseSigmoid_hls.tcl

ElemWiseVecAdd_hls:
	vivado_hls hls_proj/ElemWiseVecAdd_hls.tcl

ElemWiseVecMul_hls:
	vivado_hls hls_proj/ElemWiseVecMul_hls.tcl

mv_input_hls:
	vivado_hls hls_proj/mv_input_hls.tcl

mv_output_hls:
	vivado_hls hls_proj/mv_output_hls.tcl

mv_state_hls:
	vivado_hls hls_proj/mv_state_hls.tcl

fir_top_hls:
	vivado_hls hls_proj/fir_top_hls.tcl

prj: all_hls
	vivado -mode batch -source TCL/flow.tcl

ip_test:
	vivado -mode batch -source TCL/build.tcl

test:
	g++ src/*.cpp src/*.c -I src -I./ -o test -std=c++11

rescan:
	echo ekYD3qPUAMbm49UD > /dev/rescan-fpga
