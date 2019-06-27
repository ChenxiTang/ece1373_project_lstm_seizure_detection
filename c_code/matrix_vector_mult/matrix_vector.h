#ifndef _M_V_H
#define _M_V_H
#include "ap_fixed.h"

//typedef float dataType;
typedef ap_fixed<8,2,AP_RND_CONV,AP_SAT> dataType;

void mv_input(
              dataType input1[],       // offset of input A
			  dataType input2[],       // offset of input B
              dataType outputs[]      // offset of outputs
);
void mv_output(
               dataType input1[],       // offset of inputs
			   dataType input2[],       // offset of input B
               dataType &outputs      // offset of outputs
);
void mv_state(
              dataType input1[],       // offset of inputs
			  dataType input2[],       // offset of input B
              dataType outputs[]      // offset of outputs
);

#endif
