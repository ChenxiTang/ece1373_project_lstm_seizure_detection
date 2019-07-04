//*********************************************//
//main program to                              //
//1. write to ddr and                          //
//2. read from ddr and                         //                        
//3. calculate accuracy                        //
//*********************************************//

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include "dma_test.h"

using namespace std;

int main() {
	ifstream inFile;

	int d = 110; //number of features
	int n = 61440; // number of samples

	int x = n * d;
	int Wf_h = 64 * 64;
	int Wf_x = 64 * 110;
	int bf = 64;
	int Wi_h = 64 * 64;
	int Wi_x = 64 * 110;
	int bi = 64;
	int Wc_h = 64 * 64;
	int Wc_x = 64 * 110;
	int bc = 64;
	int Wo_h = 64 * 64;
	int Wo_x = 64 * 110;
	int bo = 64;
	int W_output = 64;
	int b_output = 1;
	int C_tmin1 = 64;
	int h_tmin1 = 64;
	int f_t = 64;
	int i_t = 64;
	int C_tilda = 64;
	int C_t = 64;
	int O_t = 64;
	int h_t = 64;
	int mul_wf_h = 64;
	int mul_wf_x = 64;
	int sum_wfh_wfx_bf = 64;
	int mul_wi_h = 64;
	int mul_wi_x = 64;
	int sum_wih_wix_bi = 64;
	int mul_wc_h = 64;
	int mul_wc_x = 64;
	int sum_wch_wcx_bc = 64;
	int mul_wo_h = 64;
	int mul_wo_x = 64;
	int sum_woh_wox_bo = 64;
	int mul_ft_ctmin1 = 64;
	int mul_it_ctilda = 64;
	int tanh_ct = 64;
	int mul_W_ht = 64;
	int sum_Wht_bias = 64;
	int output = n;

	int size = n_bands*N+n_channel*SIG_LENGTH+ x + Wf_h + Wf_x + bf + Wi_h + Wi_x + bi + Wc_h + Wc_x + bc + Wo_h + Wo_x + bo + W_output + b_output + C_tmin1 + h_tmin1 + f_t + i_t + C_tilda + C_t + O_t + h_t + mul_wf_h + mul_wf_x + sum_wfh_wfx_bf + mul_wi_h + mul_wi_x + sum_wih_wix_bi + mul_wc_h + mul_wc_x + sum_wch_wcx_bc + mul_wo_h + mul_wo_x + sum_woh_wox_bo + mul_ft_ctmin1 + mul_it_ctilda + tanh_ct + mul_W_ht + sum_Wht_bias + output;

	//printf("size %d\n", size);
	dataType* input = new dataType[size];

	int i = 0;

	string fileDir = "data/";
	string fileDirGold = "data/tensorflow_data/";

	//printf(fileDir+"x_test_se.txt");

	inFile.open((fileDir + "dma.txt").c_str(), ios::in);
	if (!inFile)
		cout << "Unable to open file" << endl;
	float temp;
	while (inFile >> temp) {
		input[i] = temp;
		i++;
	}
	inFile.close();

	cout << fileDir << "dma.txt read completed, allocated size is " << size - SIG_LENGTH << ", file size is " << i << endl;
	if (i = size - n)
		cout << "Size is correct" << endl;
	else {
		cerr << "Size error" << endl;
		return 1;
	}
	dataType* golden_output = new dataType[n];

	i = 0;
	inFile.open((fileDirGold + "predictions_series.txt").c_str(), ios::in);
	if (!inFile)
		cout << "Unable to open file" << endl;
	while (inFile >> temp) {
		golden_output[i] = temp;
		//printf("temp: %f\n",temp);
		i++;
	}
	inFile.close();

	if (i > n)
		cout << "Size violation\n";
	else
		cout << "File size is " << i << ", allocated size is " << n << endl;

	int input_offset = 0;
	int output_offset = (size - n) * sizeof(dataType);

	xdma_driver(input, size - n, n, input_offset, output_offset);
	int n_error = 0;
	for (int i = size - n; i < size - n + n; i++) {
		if ((golden_output[i-size+n] > (dataType)0.5 && input[i] < (dataType)0.5) || (golden_output[i-size+n] < (dataType)0.5 && input[i] > (dataType)0.5)) {
			cout << "error " << i - size + n << " " << golden_output[i - size + n] << " " << input[i] << endl;
			n_error++;
		}
	}
	cout << "Total number of errors is " << n_error << endl;

	return 0;
}
