#include <algorithm>
#include <float.h>
#include "matrix_vector.h"

// matrix-vector multiplication with input vector (110 x 1 vector)
void mv_input(dataType * mem,            // global memory pointer
                int input1_offset,       // offset of input A
				int input2_offset,       // offset of input B
                int output_offset      // offset of outputs
){
// Global memory interface
#pragma HLS INTERFACE m_axi port=mem depth=2147483648
// Bind all control ports to a single bundle
#pragma HLS INTERFACE s_axilite port=input1_offset
#pragma HLS INTERFACE s_axilite port=input2_offset
#pragma HLS INTERFACE s_axilite port=output_offset
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
 

  //int num_input = b*id*ix*iy;
  //int num_output = b*od*ox*oy;

  // rows
  for (int row=0; row<64; row++){
    // Set bias
    float output_element = 0;
    // Columns
    for (int col = 0; col < 110; col++){
     output_element += mem[input1_offset/sizeof(dataType) + row*110 + col]*mem[input2_offset/sizeof(dataType) + col];
     }
     // Write output
    mem[output_offset/sizeof(dataType) + row] = output_element;
  }
}

