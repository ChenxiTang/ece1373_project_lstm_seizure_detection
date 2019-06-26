#include <iostream>
#include <fstream>
#include <hls_math.h>
#include <vector>
#include <cassert>
#include "ElemWiseSigmoid.h"
#include "ap_int.h"
#include "ap_fixed.h"

void ElemWiseSigmoid(
		dataType inputs[],       // offset of inputs
        dataType outputs[]      // offset of outputs
		){
/*
	// Global memory interface
	#pragma HLS INTERFACE m_axi port=mem depth=2147483648
	// Bind all control ports to a single bundle
	#pragma HLS INTERFACE s_axilite port=input_offset
	#pragma HLS INTERFACE s_axilite port=output_offset
	#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
*/
			for(int i = 0; i < 64; i++){
//#pragma HLS UNROLL factor=32
				//out[i] = in[i]/(1+abs(in[i]));

				//Hsigm
				if(inputs[i] > 4)
					outputs[i] = 1;
				else if(inputs[i] <= -4)
					outputs[i] = 0;
				else
					outputs[i] = 0.25*inputs[i] + 0.5;
	}
}

void sigmoidSingle(dataType inputs, dataType & outputs){
	if(inputs > 4)
		outputs = 1;
	else if(inputs <= -4)
		outputs = 0;
	else
		outputs = 0.25*inputs + 0.5;
}
