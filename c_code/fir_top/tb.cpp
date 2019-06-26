#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <chrono>

#include "sig_band_energy.h"
#include "helper.h"

using namespace std;

#ifdef lin
static string rootDir = "data/";
#else
static string rootDir = "D:/ECE1373/Project/NEW_EDMSE/";
#endif

int main() {
	
	static string dma_file = "fir_dma.txt";
	static string gold_file = "gold_all.txt";
	
	dataType* dma = new dataType[n_bands * N + n_channel * SIG_LENGTH + SIG_LENGTH * n_channel * n_bands];
	dataType* gold = new dataType[SIG_LENGTH * n_channel * n_bands];

	cout << "dma array size is " << n_bands * N + n_channel * SIG_LENGTH + SIG_LENGTH * n_channel * n_bands << endl;
	cout << "gold size is " << SIG_LENGTH * n_channel * n_bands << endl;

	if (!readData(rootDir, dma_file, dma, n_bands * N + n_channel * SIG_LENGTH)) {
		cout << "File " << rootDir << dma_file << " read" << endl;
	}
	if (!readData(rootDir, gold_file, gold, SIG_LENGTH * n_channel * n_bands)) {
		cout << "File " << rootDir << gold_file << " read" << endl;
	}

	auto start = chrono::system_clock::now();\
	fir_top(dma, 0, 0);
	auto end = chrono::system_clock::now();
	auto elapsed = end - start;
	cout << "Software computation takes " << chrono::duration_cast<chrono::seconds> (elapsed).count() << "s" << endl;

	ofstream ofile;
	ofile.open(((rootDir + "results.txt")).c_str());
	for (int i = 0; i < SIG_LENGTH * n_bands * n_channel; i++) {
		ofile << dma[i + SIG_LENGTH * n_channel + n_bands * N] << endl;
	}
	ofile.close();
	cout << "Results written to file " << rootDir << "results.txt" << endl;

	dataType e = error(gold, dma);
	dataType me = maxError(gold, dma);
	cout << "The error is " << e << endl;
	cout << "MAX error is " << me << endl;

	return 0;
}
