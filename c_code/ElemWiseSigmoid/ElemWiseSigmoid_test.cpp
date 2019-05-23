#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cassert>
#include "ElemWiseSigmoid.h"
#include "ap_int.h"
#include "ap_fixed.h"

#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
	srand(6);
	int maxNum = 10;

	dataType in[len];
	dataType out[len];

	//input vector generation
	for(int i = 0; i < len; i++)
		in[i] = (rand() % maxNum) + 1;

	//Calculate the output
	ElemWiseSigmoid(in,out);

	//Error comparison
	float total = 0.0f;
	for(int i = 0; i < len; i++){
		float err = fabs(out[i] - (exp(in[i])/(exp(in[i]) + 1)));
		total += err*err;
	}

	float avg_error = total/len;
	cout<<"Mean Square Error " << avg_error << endl;
}
