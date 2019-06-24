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

// Set bias
float output_element = 0;
// Columns
for (int col = 0; col < 64; col++){
//#pragma HLS UNROLL
	output_element += input1[col]*input2[col];
}
// Write output
outputs = output_element;
}

