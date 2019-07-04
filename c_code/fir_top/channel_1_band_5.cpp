#include <algorithm>
#include <cmath>
//#include <iostream>
#include "sig_band_energy.h"

using namespace std;

void channel_1_band_5(
	dataType* mem,
	add_type input_offset,
	add_type output_offset,
	add_type channel,
	add_type index,
	dataType* weights1,
	dataType* weights2,
	dataType* weights3,
	dataType* weights4,
	dataType* weights5,
	dataType* inputs
) {
	static dataType shift_reg[n_channel][N];
	dataType acc[n_bands] = { 0.0f };
#pragma HLS RESOURCE variable=shift_reg core=RAM_S2P_BRAM

shift_register_loop:
	int ii;
	for (ii = N - 1; ii > 1; ii=ii-2) {
#pragma HLS PIPELINE
		shift_reg[channel][ii] = shift_reg[channel][ii - 1];
		shift_reg[channel][ii-1] = shift_reg[channel][ii - 2];
	}
	if (ii == 1) {
		shift_reg[channel][1] = shift_reg[channel][0];
	}
	shift_reg[channel][0] = inputs[channel];

mac_loop:

	for (int j = N - 1; j >= 0; j--) {

#pragma HLS PIPELINE

		acc[0] += shift_reg[channel][j] * weights1[j];
		acc[1] += shift_reg[channel][j] * weights2[j];
		acc[2] += shift_reg[channel][j] * weights3[j];
		acc[3] += shift_reg[channel][j] * weights4[j];
		acc[4] += shift_reg[channel][j] * weights5[j];
	}

write_to_mem:
	for (int band = 0; band < n_bands; band++) {
#pragma HLS PIPELINE
		mem[output_offset / sizeof(dataType) + band + index * n_bands * n_channel] = abs(acc[band]);
	}
}
