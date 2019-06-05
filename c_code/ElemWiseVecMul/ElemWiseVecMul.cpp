#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cassert>
#include "ElemWiseVecMul.h"
#include "ap_int.h"
#include "ap_fixed.h"

void ElemWiseVecMul(dataType * mem,            // global memory pointer
		int input1_offset,       // offset of inputs A
		int input2_offset,       // offset of inputs B
        int output_offset,      // offset of outputs
		int len){
	for(int i = 0; i < len; i++){
		mem[output_offset/sizeof(dataType)+i] = mem[input1_offset/sizeof(dataType)+i] * mem[input2_offset/sizeof(dataType)+i];
	}
}
