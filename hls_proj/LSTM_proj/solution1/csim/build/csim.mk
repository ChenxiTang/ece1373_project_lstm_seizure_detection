# ==============================================================
# File generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
# Version: 2017.2
# Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
# 
# ==============================================================

CSIM_DESIGN = 1

__SIM_FPO__ = 1

__SIM_OPENCV__ = 1

__SIM_FFT__ = 1

__SIM_FIR__ = 1

__SIM_DDS__ = 1

ObjDir = obj

HLS_SOURCES = ../../../../../c_code/top/lstm_test.cpp ../../../../../c_code/ElemWiseSigmoid/ElemWiseSigmoid.cpp ../../../../../c_code/ElemWiseTanh/ElemWiseTanh.cpp ../../../../../c_code/ElemWiseVecAdd/ElemWiseVecAdd.cpp ../../../../../c_code/ElemWiseVecMul/ElemWiseVecMul.cpp ../../../../../c_code/top/lstm.cpp ../../../../../c_code/matrix_vector_mult/mv_input.cpp ../../../../../c_code/matrix_vector_mult/mv_output.cpp ../../../../../c_code/matrix_vector_mult/mv_state.cpp

TARGET := csim.exe

AUTOPILOT_ROOT := /opt/Xilinx/Vivado_HLS/2017.2
AUTOPILOT_MACH := lnx64
ifdef AP_GCC_M32
  AUTOPILOT_MACH := Linux_x86
  IFLAG += -m32
endif
IFLAG += -fPIC
ifndef AP_GCC_PATH
  AP_GCC_PATH := /opt/Xilinx/Vivado_HLS/2017.2/lnx64/tools/gcc/bin
endif
AUTOPILOT_TOOL := ${AUTOPILOT_ROOT}/${AUTOPILOT_MACH}/tools
AP_CLANG_PATH := ${AUTOPILOT_TOOL}/clang-3.9/bin
AUTOPILOT_TECH := ${AUTOPILOT_ROOT}/common/technology


IFLAG += -I "${AUTOPILOT_TOOL}/systemc/include"
IFLAG += -I "${AUTOPILOT_ROOT}/include"
IFLAG += -I "${AUTOPILOT_ROOT}/include/opencv"
IFLAG += -I "${AUTOPILOT_ROOT}/include/ap_sysc"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC/AESL_FP_comp"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC/AESL_comp"
IFLAG += -I "${AUTOPILOT_TOOL}/auto_cc/include"
IFLAG += -I "/usr/include/x86_64-linux-gnu"
IFLAG += -D__SIM_FPO__

IFLAG += -D__SIM_OPENCV__

IFLAG += -D__SIM_FFT__

IFLAG += -D__SIM_FIR__

IFLAG += -D__SIM_DDS__

IFLAG += -I../../. -std=c++0x 
IFLAG += -g
DFLAG += -D__xilinx_ip_top= -DAESL_TB
CCFLAG += 



include ./Makefile.rules

all: $(TARGET)



$(ObjDir)/lstm_test.o: ../../../../../c_code/top/lstm_test.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../c_code/top/lstm_test.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD -I../../../../. -std=c++0x  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/lstm_test.d

$(ObjDir)/ElemWiseSigmoid.o: ../../../../../c_code/ElemWiseSigmoid/ElemWiseSigmoid.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../c_code/ElemWiseSigmoid/ElemWiseSigmoid.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/ElemWiseSigmoid.d

$(ObjDir)/ElemWiseTanh.o: ../../../../../c_code/ElemWiseTanh/ElemWiseTanh.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../c_code/ElemWiseTanh/ElemWiseTanh.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/ElemWiseTanh.d

$(ObjDir)/ElemWiseVecAdd.o: ../../../../../c_code/ElemWiseVecAdd/ElemWiseVecAdd.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../c_code/ElemWiseVecAdd/ElemWiseVecAdd.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/ElemWiseVecAdd.d

$(ObjDir)/ElemWiseVecMul.o: ../../../../../c_code/ElemWiseVecMul/ElemWiseVecMul.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../c_code/ElemWiseVecMul/ElemWiseVecMul.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/ElemWiseVecMul.d

$(ObjDir)/lstm.o: ../../../../../c_code/top/lstm.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../c_code/top/lstm.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/lstm.d

$(ObjDir)/mv_input.o: ../../../../../c_code/matrix_vector_mult/mv_input.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../c_code/matrix_vector_mult/mv_input.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/mv_input.d

$(ObjDir)/mv_output.o: ../../../../../c_code/matrix_vector_mult/mv_output.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../c_code/matrix_vector_mult/mv_output.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/mv_output.d

$(ObjDir)/mv_state.o: ../../../../../c_code/matrix_vector_mult/mv_state.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../c_code/matrix_vector_mult/mv_state.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/mv_state.d
