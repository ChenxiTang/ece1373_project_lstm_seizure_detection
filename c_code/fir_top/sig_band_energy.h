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
);

void fir_top(dataType* mem,
	add_type input_add,
	add_type output_add);


#endif
