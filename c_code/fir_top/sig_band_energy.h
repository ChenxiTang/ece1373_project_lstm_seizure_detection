#ifndef sig_band_energy_h
#define sig_band_energy_h

#include <vector>

using namespace std;

#define N 256              //fir no. of taps
#define SIG_LENGTH 61440   //test input data points
#define n_channel 22        //no. of channels
#define n_bands 5          //no. of freq bands


typedef float dataType;
typedef int add_type;

void fir_5_bands(dataType* mem, add_type input_offset, add_type output_offset);

void channel_1_band_5(
	dataType* mem,
	add_type input_offset,
	add_type output_offset,
	add_type channel
);

void fir_top(dataType* mem,
	add_type input_offset,
	add_type output_offset);

void sig_band_energy_gen(dataType* mem, add_type input_offset,
	add_type output_offset);


#endif
