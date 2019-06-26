#ifndef _DMA_H
#define _DMA_H

#include <string>
#include <vector>
#include <map>

#define PCIE_BASE 0x00010000
#define h2c_reg 0x00
#define c2h_reg 0x04
#define MAP_SIZE (1024UL*1024UL)

#define n_bands 5
#define n_channel 22
#define N 256
#define SIG_LENGTH 61440

using namespace std;

typedef float dataType;

int readData(string rootDir, string fname, dataType*& ptr, const int size);

dataType error(dataType* gold, dataType* results, int start_place);

int readData(string rootDir, string fname, dataType*& ptr, const int size);

dataType maxError(dataType* gold, dataType* results, int start_place);

void timespec_sub(struct timespec *t1, const struct timespec *t2);

int read_int(volatile void* map_base, int offset);

void write_int(volatile void* map_base, int offset, int value);

void xdma_driver(dataType* mem,
	const int dma_size, //dont multiply with sizeof
	const int out_size, //dont multiply with sizeof
	int input_offset,
	int output_offset
	);

#endif
