#include <algorithm>
#include <float.h>
#include "matrix_vector.h"

// matrix-vector multiplication with state vector to produce output (scalar)
void mv_output(float * mem,            // global memory pointer
                int input_offset,       // offset of inputs
                int output_offset      // offset of outputs
){
// Global memory interface
#pragma HLS INTERFACE m_axi port=mem depth=2147483648
// Bind all control ports to a single bundle
//#pragma HLS INTERFACE s_axilite port=k bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=input_offset bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=output_offset bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS

int num_weights = 64;
int num_biases = 1;
//int num_input = b*id*ix*iy;
//int num_output = b*od*ox*oy;

// Set bias
float output_element = mem[input_offset/sizeof(float) + num_weights];
// Columns
for (int col = 0; col < 64; col++){
	output_element += mem[input_offset/sizeof(float) + col]*mem[input_offset/sizeof(float) + num_weights + num_biases + col];
}
// Write output
mem[output_offset/sizeof(float)] = output_element;
}

