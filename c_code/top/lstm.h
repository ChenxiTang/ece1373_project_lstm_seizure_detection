#ifndef _LSTM_H
#define _LSTM_H
#include "ap_fixed.h"

//typedef float dataType;
typedef ap_fixed<15,5,AP_RND_CONV,AP_SAT> dataType;

void lstm(dataType * mem,            // global memory pointer
              int input_offset,       // offset of input
              int output_offset      // offset of outputs
);

#endif
