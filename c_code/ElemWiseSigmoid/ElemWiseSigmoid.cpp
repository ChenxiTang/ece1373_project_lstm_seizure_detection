#include <iostream>
#include <fstream>
#include <hls_math.h>
#include <vector>
#include <cassert>
#include "ElemWiseSigmoid.h"
#include "ap_int.h"
#include "ap_fixed.h"

void ElemWiseSigmoid(dataType * mem,            // global memory pointer
		int input_offset,       // offset of inputs
        int output_offset      // offset of outputs
		){

	// Global memory interface
	//#pragma HLS INTERFACE m_axi port=mem depth=2147483648
	// Bind all control ports to a single bundle
	//#pragma HLS INTERFACE s_axilite port=input_offset
	//#pragma HLS INTERFACE s_axilite port=output_offset
	//#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS

			for(int i = 0; i < 64; i++){
				//out[i] = in[i]/(1+abs(in[i]));

				//Hsigm
				if(mem[i+input_offset/sizeof(dataType)] > 4)
					mem[i+output_offset/sizeof(dataType)] = 1;
				else if(mem[i+input_offset/sizeof(dataType)] <= -4)
					mem[i+output_offset/sizeof(dataType)] = 0;
				else
					mem[i+output_offset/sizeof(dataType)] = 0.25*mem[i+input_offset/sizeof(dataType)] + 0.5;
	}
}

void ElemWiseSigmoid_single(dataType * mem,            // global memory pointer
                     int input_offset,       // offset of inputs
                     int output_offset      // offset of outputs
){
    
    // Global memory interface
//#pragma HLS INTERFACE m_axi port=mem depth=2147483648
    // Bind all control ports to a single bundle
//#pragma HLS INTERFACE s_axilite port=input_offset
//#pragma HLS INTERFACE s_axilite port=output_offset
//#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
    	//printf("jere\n");
        //out[i] = in[i]/(1+abs(in[i]));
        
        //Hsigm
        if(mem[input_offset/sizeof(dataType)] > 4)
            mem[output_offset/sizeof(dataType)] = 1;
        else if(mem[input_offset/sizeof(dataType)] <= -4)
            mem[output_offset/sizeof(dataType)] = 0;
        else
            mem[output_offset/sizeof(dataType)] = 0.25*mem[input_offset/sizeof(dataType)] + 0.5;
    
}
