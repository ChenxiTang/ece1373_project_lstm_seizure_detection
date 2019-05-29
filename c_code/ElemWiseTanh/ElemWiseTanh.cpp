#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cassert>
#include "ElemWiseTanh.h"
#include "ap_int.h"
#include "ap_fixed.h"

void ElemWiseTanh(const dataType in[len], dataType out[len]){
	for(int i = 0; i < len; i++){
		//out[i] = tanh(in[i]);
		//Htanh
		if(in[i] < -1)
			out[i] = -1;
		else if(in[i] > 1)
			out[i] = 1;
		else out[i] = in[i];


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
