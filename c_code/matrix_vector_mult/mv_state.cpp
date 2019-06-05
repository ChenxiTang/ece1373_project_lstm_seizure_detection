#include <algorithm>
#include <float.h>
#include "matrix_vector.h"

// matrix-vector multiplication with state vector (64 x 1 vector)
void mv_state(dataType * mem,            // global memory pointer
                int input1_offset,       // offset of input A
				int input2_offset,       // offset of input B
                int output_offset      // offset of outputs
){

// Global memory interface
#pragma HLS INTERFACE m_axi port=mem depth=2147483648
// Bind all control ports to a single bundle
//#pragma HLS INTERFACE s_axilite port=k bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=input_offset bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=output_offset bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
 


  // rows
  for (int row=0; row<64; row++){
    // Set bias
    float output_element = 0;
    // Columns
    for (int col = 0; col < 64; col++){
     output_element += mem[input1_offset/sizeof(dataType) + row*64 + col]*mem[input2_offset/sizeof(dataType) + col];
     }
     // Write output
    mem[output_offset/sizeof(dataType) + row] = output_element;
  }
}

