#ifndef sig_band_energy_h
#define sig_band_energy_h

#include <cstdint>

#define N 256
#define SIG_LENGTH 61440
#define n_channel 22

typedef double coef_t;
typedef double data_t;
typedef double acc_t;
typedef uint32_t add_type;

void sig_band_energy_gen(data_t* mem, add_type input_offset,
	add_type output_offset, add_type en, add_type flag, add_type index);


#endif
