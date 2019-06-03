#ifndef _M_V_H
#define _M_V_H


void mv_input(float * mem,            // global memory pointer
              int input_offset,       // offset of inputs
              int output_offset      // offset of outputs
);
void mv_output(float * mem,            // global memory pointer
               int input_offset,       // offset of inputs
               int output_offset      // offset of outputs
);
void mv_state(float * mem,            // global memory pointer
              int input_offset,       // offset of inputs
              int output_offset      // offset of outputs
);

#endif