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

	for (int ch = 0; ch < n_channel; ch++) {
		int input_offset = (n_bands * N) * sizeof(dataType) + input_add;
		int output_offset = (n_bands * N + n_channel * SIG_LENGTH + ch * n_bands) * sizeof(dataType)+output_add;
		channel_1_band_5(mem, input_offset, output_offset, ch);
		//cout << "Channel " << ch + 1 << " completed." << endl;
	}
}
