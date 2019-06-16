#ifndef _LSTM_H
#define _LSTM_H

typedef float dataType;

void lstm(dataType * mem,            // global memory pointer
              int input1_offset,       // offset of input
              int output_offset      // offset of outputs
);

#endif
