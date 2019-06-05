#include <iostream>
#include <fstream>
#include <hls_math.h>
#include <vector>
#include <cassert>
#include "ElemWiseSigmoid.h"
#include "ap_int.h"
#include "ap_fixed.h"

void ElemWiseSigmoid(dataType * mem,            // global memory pointer
		int input_offset,       // offset of inputs
        int output_offset,      // offset of outputs
		int len					// length of data
		){
			for(int i = 0; i < len; i++){
				//out[i] = in[i]/(1+abs(in[i]));

				//Hsigm
				if(mem[i+input_offset/sizeof(dataType)] > 4)
					mem[i+output_offset/sizeof(dataType)] = 1;
				else if(mem[i+input_offset/sizeof(dataType)] <= -4)
					mem[i+output_offset/sizeof(dataType)] = 0;
				else
					mem[i+output_offset/sizeof(dataType)] = 0.25*mem[i+input_offset/sizeof(dataType)] + 0.5;
	}
}
