#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cassert>
#include "ElemWiseTanh.h"
#include "ap_int.h"
#include "ap_fixed.h"

void ElemWiseTanh(dataType * mem,            // global memory pointer
		int input_offset,       // offset of inputs
        int output_offset,      // offset of outputs
		int len					// length of data
		){
	for(int i = 0; i < len; i++){
		//out[i] = tanh(in[i]);
		//Htanh
		if(mem[input_offset/sizeof(dataType)+i] < -1)
			mem[output_offset/sizeof(dataType)+i] = -1;
		else if(mem[input_offset/sizeof(dataType)+i] > 1)
			mem[output_offset/sizeof(dataType)+i] = 1;
		else mem[output_offset/sizeof(dataType)+i] = mem[input_offset/sizeof(dataType)+i];


		//Ptanh
		/*
		if(in[i] > 2.5)
			out[i] = 1;
		else if(in[i] > 0.5)
			out[i] = 0.25*in[i] + (3/8);
		else if(in[i] < -2.5)
			out[i] = -1;
		else if(in[i] <= -0.5)
			out[i] = 0.25*in[i] - (3/8);
		else
			out[i] = in[i];
			*/
	}
}
