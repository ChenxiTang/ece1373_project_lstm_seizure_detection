#include <algorithm>
#include <float.h>
#include "matrix_vector.h"

// matrix-vector multiplication with state vector to produce output (scalar)
void mv_output(
                dataType input1[],       // offset of input A
				dataType input2[],       // offset of input B,
                dataType &outputs      // offset of outputs
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

//int num_input = b*id*ix*iy;
//int num_output = b*od*ox*oy;

    dataType mult[64];
#pragma HLS ARRAY_PARTITION variable=mult complete dim=1
    dataType add1[32];
#pragma HLS ARRAY_PARTITION variable=add1 complete dim=1
    dataType add2[16];
#pragma HLS ARRAY_PARTITION variable=add2 complete dim=1
    dataType add3[8];
#pragma HLS ARRAY_PARTITION variable=add3 complete dim=1
    dataType add4[4];
#pragma HLS ARRAY_PARTITION variable=add4 complete dim=1
    dataType add5[2];
#pragma HLS ARRAY_PARTITION variable=add5 complete dim=1


// Set bias
float output_element = 0;
// Columns
for (int col = 0; col < 64; col++){
    #pragma HLS UNROLL
    mult[col] = input1[col]*input2[col];
}

    for (int i = 0; i < 32; i++){
#pragma HLS UNROLL
    	const dataType temp = mult[2*i] + mult[2*i+1];
#pragma HLS RESOURCE variable=temp core=FAddSub_nodsp
        add1[i] = temp;
    }
    for (int i = 0; i < 16; i++){
#pragma HLS UNROLL
    	const dataType temp = add1[2*i] + add1[2*i+1];
#pragma HLS RESOURCE variable=temp core=FAddSub_nodsp
        add2[i] = temp;
    }
    for (int i = 0; i < 8; i++){
#pragma HLS UNROLL
    	const dataType temp = add2[2*i] + add2[2*i+1];
#pragma HLS RESOURCE variable=temp core=FAddSub_nodsp
        add3[i] = temp;
    }
    for (int i = 0; i < 4; i++){
#pragma HLS UNROLL
    	const dataType temp = add3[2*i] + add3[2*i+1];
#pragma HLS RESOURCE variable=temp core=FAddSub_nodsp
        add4[i] = temp;
    }
    for (int i = 0; i < 2; i++){
#pragma HLS UNROLL
    	const dataType temp = add4[2*i] + add4[2*i+1];
#pragma HLS RESOURCE variable=temp core=FAddSub_nodsp
        add5[i] = temp;
    }
    outputs = add5[0] + add5[1];
    /*
	output_element += input1[col]*input2[col];
}
// Write output
    outputs = output_element;
     */
}

