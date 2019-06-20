#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <stdlib.h>

#include "sig_band_energy.h"
#include "helper.h"

using namespace std;

int main() {
	
	string rootDir = "D:/ECE1373/Project/NEW_EDMSE/";

	string gold_file = "gold.txt";
	string raw_file = "raw.txt";
	string coeff_file = "fir_coeff_0.5_4.txt";

	data_t* raw;
	data_t* gold;
	data_t* coeff;
	data_t* dma = new data_t[N + 2 * SIG_LENGTH];

	if (!readData(rootDir, gold_file, gold, SIG_LENGTH)) {
		cout << "File " << rootDir << gold_file << " read" << endl;
	}
	if (!readData(rootDir, raw_file, raw, SIG_LENGTH)) {
		cout << "File " << rootDir << raw_file << " read" << endl;
	}
	if (!readData(rootDir, coeff_file, coeff, N)) {
		cout << "File " << rootDir << coeff_file << " read" << endl;
	}

	copy(coeff, coeff + N, dma);
	copy(raw, raw + SIG_LENGTH, dma + N);

	for (int i = 0; i < SIG_LENGTH; i++) {
		sig_band_energy_gen(dma, 0, 0, 1, 0, i);
	}

	data_t* results = dma;

	data_t e = error(gold, results);
	cout << "The error is " << e << endl;

	return 0;
}
