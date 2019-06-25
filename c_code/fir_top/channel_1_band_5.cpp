#include <algorithm>
#include <cmath>
//#include <iostream>
#include "sig_band_energy.h"

using namespace std;

void channel_1_band_5(
	dataType* mem,
	add_type input_offset,
	add_type output_offset,
	add_type channel
) {
	static dataType shift_reg[n_channel][N];

	for (int index = 0; index < SIG_LENGTH; index++) {

		dataType acc[n_bands] = { 0.0f };

	shift_register_loop:

			for (int i = N - 1; i > 0; i--) {
				shift_reg[channel][i] = shift_reg[channel][i - 1];
			}
			shift_reg[channel][0] = mem[input_offset / sizeof(dataType) + index + SIG_LENGTH * channel];

		mac_loop:

			for (int j = N - 1; j >= 0; j--) {			
					acc[0] += shift_reg[channel][j] * mem[input_offset / sizeof(dataType) - N * n_bands + j + 0 * N];
					acc[1] += shift_reg[channel][j] * mem[input_offset / sizeof(dataType) - N * n_bands + j + 1 * N];
					acc[2] += shift_reg[channel][j] * mem[input_offset / sizeof(dataType) - N * n_bands + j + 2 * N];
					acc[3] += shift_reg[channel][j] * mem[input_offset / sizeof(dataType) - N * n_bands + j + 3 * N];
					acc[4] += shift_reg[channel][j] * mem[input_offset / sizeof(dataType) - N * n_bands + j + 4 * N];
			}

			
		write_to_mem:
			for (int band = 0; band < n_bands; band++) {
				mem[output_offset / sizeof(dataType) + band + index * n_bands * n_channel] = abs(acc[band]);
				//cout << abs(acc[band]) << ",";
			}
			//cout << endl;
		
	}


}
