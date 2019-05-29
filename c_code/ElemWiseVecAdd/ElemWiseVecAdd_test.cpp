#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cassert>
#include "ElemWiseVecAdd.h"
#include "ap_int.h"
#include "ap_fixed.h"

#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
	srand(time(0));
	int maxNum = 10;

	dataType in1[len];
	dataType in2[len];
	dataType out[len];

	//input vector generation
	for(int i = 0; i < len; i++){
		in1[i] = (rand() % maxNum) + 1;
		in2[i] = (rand() % maxNum) + 1;
	}


	//Calculate the output
	ElemWiseVecAdd(in1,in2,out);

	//Error comparison
	float total = 0.0f;
	for(int i = 0; i < len; i++){
		float err = fabs(out[i] - (in1[i]+in2[i]));
		total += err*err;
	}

	float avg_error = total/len;
	cout<<"Mean Square Error " << avg_error << endl;
}
