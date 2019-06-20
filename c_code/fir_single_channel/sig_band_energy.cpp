#include <cmath>
#include "sig_band_energy.h"

/*Top level function for freature extraction*/

void sig_band_energy_gen(data_t* mem,
						add_type input_offset, 
						add_type output_offset, 
						add_type en, 
						add_type flag, 
						add_type index) {

#pragma HLS INTERFACE m_axi depth=2147483648 port=mem
#pragma HLS INTERFACE s_axilite port=input_offset bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=output_offset bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=en bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=flag bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=index bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS


	static data_t shift_reg[N];
	if (en) {
		
		acc_t acc = 0.0f;

		shift_register_loop:
		for (int i = N - 1; i > 0; i--) {
			shift_reg[i] = shift_reg[i - 1];			
		}
		shift_reg[0] = mem[N + index];

		MAC:
		for (int i = N - 1; i >= 0; i--) {
			acc += shift_reg[i] * mem[i];
		}
		
		mem[N + SIG_LENGTH + index + output_offset/sizeof(data_t)] = abs(acc);

		flag = 1;
	}
}
