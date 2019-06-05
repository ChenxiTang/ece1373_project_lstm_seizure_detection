#ifndef _M_V_H
#define _M_V_H

typedef float dataType;

void mv_input(dataType * mem,            // global memory pointer
              int input_offset,       // offset of inputs
              int output_offset      // offset of outputs
);
void mv_output(dataType * mem,            // global memory pointer
               int input_offset,       // offset of inputs
               int output_offset      // offset of outputs
);
void mv_state(dataType * mem,            // global memory pointer
              int input_offset,       // offset of inputs
              int output_offset      // offset of outputs
);

#endif