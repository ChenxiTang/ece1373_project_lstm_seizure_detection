#ifndef _M_V_H
#define _M_V_H

typedef float dataType;

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
