
#include <stdio.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include "lstm.h"
using namespace std;

typedef float dataType;

int main(){

    ifstream inFile;
    
    int d = 110; //number of features
    int n = 61440; // number of samples

    int x = n*d;
    int Wf_h = 64*64;
    int Wf_x = 64*110;
    int bf = 64;
    int Wi_h = 64*64;
    int Wi_x = 64*110;
    int bi = 64;
    int Wc_h = 64*64;
    int Wc_x = 64*110;
    int bc = 64;
    int Wo_h = 64*64;
    int Wo_x = 64*110;
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

    int size = x+Wf_h+Wf_x+bf+Wi_h+Wi_x+bi+Wc_h+Wc_x+bc+Wo_h+Wo_x+bo+W_output+b_output+C_tmin1+h_tmin1+f_t+i_t+C_tilda+C_t+O_t+h_t+mul_wf_h+mul_wf_x+sum_wfh_wfx_bf+mul_wi_h+mul_wi_x+sum_wih_wix_bi+mul_wc_h+mul_wc_x+sum_wch_wcx_bc+mul_wo_h+mul_wo_x+sum_woh_wox_bo+mul_ft_ctmin1+mul_it_ctilda+tanh_ct+mul_W_ht+sum_Wht_bias+output;

    printf("size %d\n", size);
    dataType* input = (dataType*) malloc(size*sizeof(dataType));
    
    int i = 0;
    
    string fileDir = "../../data/tensorflow_data";
    
    inFile.open(fileDir+"x_test_se.txt");
    if (!inFile)
        printf("Unable to open file\n");
    float temp;
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();


    inFile.open(fileDir+"Whf.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();

    inFile.open(fileDir+"Wxf.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(fileDir+"bf.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(fileDir+"Whi.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(fileDir+"Wxi.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(fileDir+"bi.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    

    inFile.open(fileDir+"Whc.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(fileDir+"Wxc.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    
    inFile.open(fileDir+"bc.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(fileDir+"Who.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(fileDir+"Wxo.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(fileDir+"bo.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(fileDir+"Wy.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    inFile.open(fileDir+"by.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        input[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    printf("i: %d\n", i);
    
    float* golden_output = (float*) malloc(sizeof(float)*n);
    
    i=0;
    inFile.open(fileDir+"predictions_series.txt");
    if (!inFile)
        printf("Unable to open file\n");
    while (inFile >> temp) {
        golden_output[i] = temp;
        //printf("temp: %f\n",temp);
        i++;
    }
    inFile.close();
    
    ///*
    lstm(input, 0, size-n);
    
    for (int i = size-n; i < size; i++){
        if (golden_output[i-size+n] != input[i])
            printf("error %d\n", i);
    }
    //*/
    return 0;
}








