#include <algorithm>
#include <float.h>
#include "matrix_vector.h"

// matrix-vector multiplication with state vector (64 x 1 vector)
void mv_state(
                dataType input1[],       //   input A
				dataType input2[],       //   input B
                dataType outputs[]      //   outputs
){

// Global memory interface
	/*
#pragma HLS INTERFACE m_axi port=mem depth=2147483648
// Bind all control ports to a single bundle
#pragma HLS INTERFACE s_axilite port=input1_offset
#pragma HLS INTERFACE s_axilite port=input2_offset
#pragma HLS INTERFACE s_axilite port=output_offset
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
 */


  // rows

  for (int row=0; row<64; row++)

//#pragma HLS UNROLL
 {
    // Set bias
    dataType output_element = 0;
    // Columns
    for (int col = 0; col < 64; col++){
//#pragma HLS UNROLL
     output_element += input1[row*64 + col]*input2[col];
     }
     // Write output
    outputs[row] = output_element;
  }
}

