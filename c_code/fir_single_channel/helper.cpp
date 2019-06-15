#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include "helper.h"
#include "sig_band_energy.h"


using namespace std;

data_t error(data_t* gold, data_t* results) {
	data_t err = 0.0;

	for (int i = 0; i < SIG_LENGTH; i++) {
		err += abs(gold[i]-results[i+N+SIG_LENGTH]);
	}

	return err;
}

int readData(string rootDir, string fname, data_t*& ptr, const int size) {
	data_t x;
	int i = 0;
	int flag = 0;
	ptr = new data_t[size];

	ifstream infile;
	infile.open(rootDir + fname, ios::in);

	if (!infile) {
		flag = 1;
		delete[] ptr;
		return flag;
	}

	while (infile >> x) {
		ptr[i] = x;
		i++;
	}

	return flag;
}

/*
int extract_energy(const string fname, int size) {
	float* memory;
	if (readRawFile(fname, memory, size, size)) {
		return 1;
	}
	else {
		for (int i = 0; i < 10; i++) {
			cout << memory[i] << endl;
		}
	}

	return 0;
}*/