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


  // rows

  for (int row=0; row<64; row++)

//#pragma HLS UNROLL
 {
    // Set bias
    //dataType output_element = 0;
    // Columns
    for (int col = 0; col < 64; col++){
        #pragma HLS UNROLL
        mult[col] = input1[row*64 + col]*input2[col];
    }

     for (int i = 0; i < 32; i++)
        #pragma HLS UNROLL
         add1[i] = mult[2*i] + mult[2*i+1];
     for (int i = 0; i < 16; i++)
        #pragma HLS UNROLL
         add2[i] = add1[2*i] + add1[2*i+1];
     for (int i = 0; i < 8; i++)
        #pragma HLS UNROLL
         add3[i] = add2[2*i] + add2[2*i+1];
     for (int i = 0; i < 4; i++)
        #pragma HLS UNROLL
         add4[i] = add3[2*i] + add3[2*i+1];
     for (int i = 0; i < 2; i++)
        #pragma HLS UNROLL
         add5[i] = add4[2*i] + add4[2*i+1];
     outputs[row] = add5[0] + add5[1];
     // Write output
     //outputs[row] = output_element;


     /*

     output_element += input1[row*64 + col]*input2[col];
     }
     // Write output
    outputs[row] = output_element;
      */
  }
}

