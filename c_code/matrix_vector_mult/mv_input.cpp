#include <algorithm>
#include <float.h>
#include "matrix_vector.h"

// matrix-vector multiplication with input vector (110 x 1 vector)
void mv_input(float * mem,            // global memory pointer
                int input_offset,       // offset of inputs
                int output_offset      // offset of outputs
){
// Global memory interface
#pragma HLS INTERFACE m_axi port=mem depth=2147483648
// Bind all control ports to a single bundle
#pragma HLS INTERFACE s_axilite port=input_offset
#pragma HLS INTERFACE s_axilite port=output_offset
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
 
  int num_weights = 64*110;
  int num_biases = 64;
  //int num_input = b*id*ix*iy;
  //int num_output = b*od*ox*oy;

  // rows
  for (int row=0; row<64; row++){
    // Set bias
    float output_element = mem[input_offset/sizeof(float) + num_weights + row];
    // Columns
    for (int col = 0; col < 110; col++){
     output_element += mem[input_offset/sizeof(float) + row*110 + col]*mem[input_offset/sizeof(float) + num_weights + num_biases + col];
     }
     // Write output
    mem[output_offset/sizeof(float) + row] = output_element;
  }
}

