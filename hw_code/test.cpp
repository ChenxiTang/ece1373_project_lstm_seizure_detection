//*********************************************//
//main program to                              //
//1. write to ddr and                          //
//2. read from ddr and                         //                        
//3. calculate accuracy                        //
//*********************************************//

#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <byteswap.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/unistd.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "dma_test.h"

using namespace std;


int main() {

#ifdef FIR_TEST
	string rootDir = "data/Fir_test/";
	
	string dma_file = "fir_dma.txt";
	string gold_file = "gold_all.txt";

	int input_size = n_bands * N + SIG_LENGTH * n_channel;
	int output_size = n_bands * SIG_LENGTH * n_channel;
	
	dataType* dma = new dataType[input_size+output_size];
	dataType* gold = new dataType[output_size];

	cout << "dma array size is " << output_size + input_size << endl;
	cout << "gold size is " << output_size << endl;

	if (!readData(rootDir, dma_file, dma, input_size)) {
		cout << "File " << rootDir << dma_file << " read" << endl;
	}
	if (!readData(rootDir, gold_file, gold, output_size)) {
		cout << "File " << rootDir << gold_file << " read" << endl;
	}

	cout << "File read completed\n";

	
	int input_offset = 0;
	int output_offset = input_size*sizeof(dataType);

	xdma_driver(dma, input_size, output_size, input_offset, output_offset);

	ofstream ofile;
	ofile.open((rootDir+"hw_results.txt").c_str());
	for(int i=0;i<output_size;i++)
	  ofile<<dma[input_size+i]<<endl;
	ofile.close();

	cout << "Max error is " << maxError(gold, dma, input_size) << endl;
	cout << "Total error is " << error(gold, dma, input_size) << endl;
#else

	int d = n_bands*n_channel; //number of features
	int n = SIG_LENGTH; // number of samples

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

	string lstmDir="data/tensorflow_data/";
	int input_size = x+Wf_h+Wf_x+bf+Wi_h+Wi_x+bi+Wc_h+Wc_x+bc+Wo_h+Wo_x+bo+W_output+b_output+C_tmin1+h_tmin1+f_t+i_t+C_tilda+C_t+O_t+h_t+mul_wf_h+mul_wf_x+sum_wfh_wfx_bf+mul_wi_h+mul_wi_x+sum_wih_wix_bi+mul_wc_h+mul_wc_x+sum_wch_wcx_bc+mul_wo_h+mul_wo_x+sum_woh_wox_bo+mul_ft_ctmin1+mul_it_ctilda+tanh_ct+mul_W_ht+sum_Wht_bias;
	dataType* input = new dataType [input_size+N];

	int i=0;
	ifstream inFile;
	
	inFile.open(lstmDir+"x_test_se.txt");
    if (!inFile)
        printf("Unable to open file\n");
    float temp;
    while (inFile >> temp) {
    	// changed by Jamie
        input[i] = temp;
    	//input[i] = 0.0;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();

    inFile.open(lstmDir+"Whf.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();

    inFile.open(lstmDir+"Wxf.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(lstmDir+"bf.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(lstmDir+"Whi.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(lstmDir+"Wxi.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(lstmDir+"bi.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    

    inFile.open(lstmDir+"Whc.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(lstmDir+"Wxc.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    
    inFile.open(lstmDir+"bc.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(lstmDir+"Who.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    inFile.open(lstmDir+"Wxo.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(lstmDir+"bo.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(lstmDir+"Wy.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(lstmDir+"by.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    cout<<"LSTM inputs and weights read complete"<<endl;
    
    dataType* golden_output = new dataType [SIG_LENGTH];
    
    i=0;
    inFile.open(lstmDir + "predictions_series.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        golden_output[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();

	cout << "Gold output read completed" << endl;

	int input_offset = 0;
	int output_offset = input_size * sizeof(dataType);
	int output_size = SIG_LENGTH;

	xdma_driver(input, input_size, output_size, input_offset, output_offset);

	int size = input_size + n;

	for (int i = size - n; i < size - n + 200; i++) {
		if (fabs(golden_output[i - size + n] - input[i]) > 0.001)
			printf("error %d %f %f\n", i - size + n, golden_output[i - size + n], input[i]);
	}

#endif
	return 0;
}
