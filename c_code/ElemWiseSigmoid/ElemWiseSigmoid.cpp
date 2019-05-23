#include <iostream>
#include <fstream>
#include <hls_math.h>
#include <vector>
#include <cassert>
#include "ElemWiseSigmoid.h"
#include "ap_int.h"
#include "ap_fixed.h"

void ElemWiseSigmoid(const dataType in[len], dataType out[len]){
	for(int i = 0; i < len; i++){
		//out[i] = in[i]/(1+abs(in[i]));

		//Hsigm
		if(in[i] > 4)
			out[i] = 1;
		else if(in[i] <= -4)
			out[i] = 0;
		else
			out[i] = 0.25*in[i] + 0.5;
	}
}
