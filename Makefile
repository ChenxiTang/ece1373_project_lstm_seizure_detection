all_hls:fir_top_hls lstm_top_hls

prj: all_hls
	vivado -mode batch -source TCL/flow.tcl

test:
	g++ src/*.cpp src/*.c -I src -I./ -o test -std=c++11

rescan:
	echo ekYD3qPUAMbm49UD > /dev/rescan-fpga

fir_top_hls:
	vivado_hls hls_proj/fir_top_hls.tcl

lstm_top_hls:
	vivado_hls hls_proj/LSTM_hls.tcl