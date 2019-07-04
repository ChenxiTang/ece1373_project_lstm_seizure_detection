/*Top Level 22-channel 5-band FIR code with optimisation in HLS*/
/*Written by: Chenxi Tang                                      */
/*Last Updated: 25 June 2019                                   */
/*Developed with Vivdo design suite 2017.2                     */
/*Part of the course project for ECE1373 Digital Design for SoC*/

#include <algorithm>
#include <cmath>
//#include <iostream>
#include "sig_band_energy.h"

using namespace std;

void fir_top(dataType* mem,
	add_type input_add,
	add_type output_add) {
#pragma HLS INTERFACE m_axi depth=2147483648 port=mem
#pragma HLS INTERFACE s_axilite port=input_add bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=output_add bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
	//read weights from memory
	dataType weights1[N];
#pragma HLS RESOURCE variable=weights1 core=RAM_S2P_BRAM

	dataType weights2[N];
#pragma HLS RESOURCE variable=weights2 core=RAM_S2P_BRAM

	dataType weights3[N];
#pragma HLS RESOURCE variable=weights3 core=RAM_S2P_BRAM

	dataType weights4[N];
#pragma HLS RESOURCE variable=weights4 core=RAM_S2P_BRAM

	dataType weights5[N];
#pragma HLS RESOURCE variable=weights5 core=RAM_S2P_BRAM


	for (int j = 0; j < N; j++) {
#pragma HLS PIPELINE

		weights1[j] = mem[input_add / sizeof(dataType) + j + 0 * N];
		weights2[j] = mem[input_add / sizeof(dataType) + j + 1 * N];
		weights3[j] = mem[input_add / sizeof(dataType) + j + 2 * N];
		weights4[j] = mem[input_add / sizeof(dataType) + j + 3 * N];
		weights5[j] = mem[input_add / sizeof(dataType) + j + 4 * N];
	}

	for (int index = 0; index < SIG_LENGTH; index++) {
		// stream in inputs to BRAM
		int input_offset = (n_bands * N) * sizeof(dataType) + input_add;
		dataType channel_in[n_channel];
#pragma HLS RESOURCE variable=channel_in core=RAM_S2P_BRAM
		for (int i = 0; i < n_channel; i++) {
			channel_in[i] = mem[input_offset / sizeof(dataType) + index + SIG_LENGTH * i];
		}

		// FIR for 22 channels
		for (int ch = 0; ch < n_channel; ch++) {


			int output_offset = (n_bands * N + n_channel * SIG_LENGTH + ch * n_bands) * sizeof(dataType) + output_add;
			channel_1_band_5(mem, input_offset, output_offset, ch, index, weights1, weights2, weights3, weights4, weights5, channel_in);


		}


	}
}
