#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>
#include <stdint.h>
#include <assert.h>
#include "helper.h"
#include "sig_band_energy.h"

/* ltoh: little to host */
/* htol: little to host */
#if __BYTE_ORDER == __LITTLE_ENDIAN
#  define ltohl(x)       (x)
#  define ltohs(x)       (x)
#  define htoll(x)       (x)
#  define htols(x)       (x)
#elif __BYTE_ORDER == __BIG_ENDIAN
#  define ltohl(x)     __bswap_32(x)
#  define ltohs(x)     __bswap_16(x)
#  define htoll(x)     __bswap_32(x)
#  define htols(x)     __bswap_16(x)
#endif


using namespace std;

dataType error(dataType* gold, dataType* results) {
	dataType err = 0.0f;
	dataType temp;

	for (int i = 0; i < n_bands*SIG_LENGTH; i++) {
		temp = abs(gold[i] - results[i + n_bands * N + n_channel * SIG_LENGTH]);
		err += temp;
		//cout << gold[i] << "   " << results[i + n_bands * N + n_channel * SIG_LENGTH] << endl;
	}

	return err;
}

dataType maxError(dataType* gold, dataType* results) {
	static dataType max_e = 0.0f;
	dataType e;

	for (int i = 0; i < n_bands * SIG_LENGTH; i++) {
		e = abs(gold[i] - results[i + n_bands * N + n_channel * SIG_LENGTH]);
		if (e > max_e)
			max_e = e;
	}
	return max_e;
}

int readData(string rootDir, string fname, dataType*& ptr, const int size) {
	dataType x;
	int i = 0;
	int flag = 0;
	ptr = new dataType[size];

	ifstream infile;
	infile.open(rootDir + fname, ios::in);

	if (!infile) {
		flag = 1;
		delete[] ptr;
		cout << "File not opened\n";
		return flag;
	}

	while (infile >> x) {
		ptr[i] = x;
		i++;
	}

	if (i > size)
		cout << "Size violation\n";
	else
		cout << "File size is " << i << ", allocated size is " << size << endl;


	return flag;
}

/*
void write_int(volatile void* map_base, int offset, int value)
{
	volatile void* virt_addr = (volatile void*)((char*)map_base + offset);
	*((uint32_t*)virt_addr) = htoll(value);
}
int read_int(volatile void* map_base, int offset)
{
	volatile void* virt_addr = (volatile void*)((char*)map_base + offset);
	return ltohl(*((uint32_t*)virt_addr));
}

void timespec_sub(struct timespec* t1, const struct timespec* t2)
{
	assert(t1->tv_nsec >= 0);
	assert(t1->tv_nsec < 1000000000);
	assert(t2->tv_nsec >= 0);
	assert(t2->tv_nsec < 1000000000);
	t1->tv_sec -= t2->tv_sec;
	t1->tv_nsec -= t2->tv_nsec;
	if (t1->tv_nsec >= 1000000000)
	{
		t1->tv_sec++;
		t1->tv_nsec -= 1000000000;
	}
	else if (t1->tv_nsec < 0)
	{
		t1->tv_sec--;
		t1->tv_nsec += 1000000000;
	}
}
*/