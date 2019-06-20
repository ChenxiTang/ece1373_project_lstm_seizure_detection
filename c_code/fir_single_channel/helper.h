#ifndef helper_h
#define helper_h

#include <string>
#include "sig_band_energy.h"

using namespace std;

//int extract_energy(const string fname, int size);

//int readRawFile(const string fname, float*& fptr, const int read_alloc, const int max_alloc);

data_t error(data_t* gold, data_t* results);

int readData(string rootDir, string fname, data_t*& ptr, const int size);

#endif
