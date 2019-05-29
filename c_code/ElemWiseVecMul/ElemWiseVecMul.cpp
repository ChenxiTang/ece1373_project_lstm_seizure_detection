#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cassert>
#include "ElemWiseVecMul.h"
#include "ap_int.h"
#include "ap_fixed.h"

void ElemWiseVecMul(const dataType in1[len], const dataType in2[len], dataType out[len]){
	for(int i = 0; i < len; i++){
		out[i] = in1[i] * in2[i];
	}
}
