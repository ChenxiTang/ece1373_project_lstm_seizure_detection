#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cassert>
#include "ElemWiseVecAdd.h"
#include "ap_int.h"
#include "ap_fixed.h"

void ElemWiseVecAdd(
		dataType input1[],       // offset of inputs A
		dataType input2[],       // offset of inputs B
        dataType outputs[]      // offset of outputs
		){
/*
	// Global memory interface
	#pragma HLS INTERFACE m_axi port=mem depth=2147483648
	// Bind all control ports to a single bundle
	#pragma HLS INTERFACE s_axilite port=input1_offset
	#pragma HLS INTERFACE s_axilite port=input2_offset
	#pragma HLS INTERFACE s_axilite port=output_offset
	#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
*/

		for(int i = 0; i < 64; i++){
#pragma HLS UNROLL factor=32
			const dataType temp =  input1[i] + input2[i];
#pragma HLS RESOURCE variable=temp core=FAddSub_nodsp
			outputs[i] = temp;
			//outputs[i] = input1[i] + input2[i];
		}
}


void ElemWiseVecAdd3(
		dataType input1[],       // offset of inputs A
		dataType input2[],       // offset of inputs B
		dataType input3[],       // offset of inputs C
        dataType outputs[]      // offset of outputs
){
	/*
	// Global memory interface
	#pragma HLS INTERFACE m_axi port=mem depth=2147483648
	// Bind all control ports to a single bundle
	#pragma HLS INTERFACE s_axilite port=input1_offset
	#pragma HLS INTERFACE s_axilite port=input2_offset
	#pragma HLS INTERFACE s_axilite port=input3_offset
	#pragma HLS INTERFACE s_axilite port=output_offset
	#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
*/

		for(int i = 0; i < 64; i++){
#pragma HLS UNROLL factor=32
			const dataType temp1 = input1[i] + input2[i];
#pragma HLS RESOURCE variable=temp1 core=FAddSub_nodsp
			const dataType temp2 = temp1 + input3[i];
#pragma HLS RESOURCE variable=temp2 core=FAddSub_nodsp
			outputs[i] = temp2;
	}
}
