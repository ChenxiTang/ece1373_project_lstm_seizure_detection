#ifndef helper_h
#define helper_h

#include <string>
#include "sig_band_energy.h"

using namespace std;


dataType error(dataType* gold, dataType* results);

int readData(string rootDir, string fname, dataType*& ptr, const int size);

dataType maxError(dataType* gold, dataType* results);
/*
void write_int(volatile void* map_base, int offset, int value);
int read_int(volatile void* map_base, int offset);
void timespec_sub(struct timespec* t1, const struct timespec* t2);
*/
#endif
