all_hls: ElemWiseTanh_hls ElemWiseSigmoid_hls ElemWiseVecAdd_hls ElemWiseVecMul_hls mv_input_hls mv_output_hls mv_state_hls


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

prj: all_hls
	vivado -mode batch -source TCL/build.tcl
