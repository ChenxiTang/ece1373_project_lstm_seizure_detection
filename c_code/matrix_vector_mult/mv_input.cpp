#include <algorithm>
#include <float.h>
#include "matrix_vector.h"

// matrix-vector multiplication with input vector (110 x 1 vector)
void mv_input(
                dataType input1[],       // offset of input A
			    dataType input2[],       // offset of input B
                dataType outputs[]      // offset of outputs
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


  dataType mult[110];
   #pragma HLS ARRAY_PARTITION variable=mult complete dim=1
  dataType add1[55];
    #pragma HLS ARRAY_PARTITION variable=add1 complete dim=1
  dataType add2[28];
    #pragma HLS ARRAY_PARTITION variable=add2 complete dim=1
  dataType add3[14];
    #pragma HLS ARRAY_PARTITION variable=add3 complete dim=1
  dataType add4[7];
    #pragma HLS ARRAY_PARTITION variable=add4 complete dim=1
  dataType add5[4];
    #pragma HLS ARRAY_PARTITION variable=add5 complete dim=1
  dataType add6[2];
    #pragma HLS ARRAY_PARTITION variable=add6 complete dim=1

  // rows
  for (int row=0; row<64; row++){
//#pragma HLS UNROLL
    // Set bias
    //dataType output_element = 0;
    // Columns
    for (int col = 0; col < 110; col++){
        #pragma HLS UNROLL
        mult[col] = input1[row*110 + col]*input2[col];
        //output_element += input1[row*110 + col]*input2[col];
     }


    for (int i = 0; i < 55; i++){
        #pragma HLS UNROLL
    	const dataType temp = mult[2*i] + mult[2*i+1];
//#pragma HLS RESOURCE variable=temp core=FAddSub_nodsp
        add1[i] = temp;
    }
    for (int i = 0; i < 27; i++){
        #pragma HLS UNROLL
    	const dataType temp = add1[2*i] + add1[2*i+1];
//#pragma HLS RESOURCE variable=temp core=FAddSub_nodsp
        add2[i] = temp;
    }
    add2[27] = add1[54];
    for (int i = 0; i < 14; i++){
        #pragma HLS UNROLL
    	const dataType temp = add2[2*i] + add2[2*i+1];
//#pragma HLS RESOURCE variable=temp core=FAddSub_nodsp
        add3[i] = temp;
    }
    for (int i = 0; i < 7; i++){
        #pragma HLS UNROLL
    	const dataType temp = add3[2*i] + add3[2*i+1];
//#pragma HLS RESOURCE variable=temp core=FAddSub_nodsp
        add4[i] = temp;
    }
    for (int i = 0; i < 3; i++){
        #pragma HLS UNROLL
    	const dataType temp = add4[2*i] + add4[2*i+1];
//#pragma HLS RESOURCE variable=temp core=FAddSub_nodsp
        add5[i] = temp;
    }
    add5[3] = add4[6];
    for (int i = 0; i < 2; i++){
        #pragma HLS UNROLL
    	const dataType temp = add5[2*i] + add5[2*i+1];
//#pragma HLS RESOURCE variable=temp core=FAddSub_nodsp
        add6[i] = temp;
    }
    outputs[row] = add6[0] + add6[1];
     // Write output
    //outputs[row] = output_element;
     /*
      for (int i = 0; i < 110; i++){
          output_element += mult[i];
      }
      outputs[row] = output_element;
    */
  }
}

