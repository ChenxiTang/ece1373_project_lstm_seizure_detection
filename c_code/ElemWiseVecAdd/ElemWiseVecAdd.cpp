#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cassert>
#include "ElemWiseVecAdd.h"
#include "ap_int.h"
#include "ap_fixed.h"

void ElemWiseVecAdd(dataType * mem,            // global memory pointer
		int input1_offset,       // offset of inputs A
		int input2_offset,       // offset of inputs B
        int output_offset      // offset of outputs
		){

	// Global memory interface
	#pragma HLS INTERFACE m_axi port=mem depth=2147483648
	// Bind all control ports to a single bundle
	#pragma HLS INTERFACE s_axilite port=input1_offset bundle=CTRL_BUS
	#pragma HLS INTERFACE s_axilite port=input2_offset bundle=CTRL_BUS
	#pragma HLS INTERFACE s_axilite port=output_offset bundle=CTRL_BUS
	#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS

		for(int i = 0; i < 64; i++){
			mem[output_offset/sizeof(dataType)+i] = mem[input1_offset/sizeof(dataType)+i] + mem[input2_offset/sizeof(dataType)+i];
	}
}


void ElemWiseVecAdd3(dataType * mem,            // global memory pointer
		int input1_offset,       // offset of inputs A
		int input2_offset,       // offset of inputs B
		int input3_offset,       // offset of inputs C
        int output_offset      // offset of outputs
){
	// Global memory interface
	#pragma HLS INTERFACE m_axi port=mem depth=2147483648
	// Bind all control ports to a single bundle
	#pragma HLS INTERFACE s_axilite port=input1_offset bundle=CTRL_BUS
	#pragma HLS INTERFACE s_axilite port=input2_offset bundle=CTRL_BUS
	#pragma HLS INTERFACE s_axilite port=input3_offset bundle=CTRL_BUS
	#pragma HLS INTERFACE s_axilite port=output_offset bundle=CTRL_BUS
	#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS

		for(int i = 0; i < 64; i++){
			mem[output_offset/sizeof(dataType)+i] = mem[input1_offset/sizeof(dataType)+i] + mem[input2_offset/sizeof(dataType)+i] + mem[input3_offset/sizeof(dataType)+i];
	}
}
