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
     outputs[row] = add5[0] + add5[1];

  }
}

