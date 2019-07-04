//*********************************************//
//main program to                              //
//1. write to ddr and                          //
//2. read from ddr and                         //                        
//3. calculate accuracy                        //
//*********************************************//

#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <byteswap.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/unistd.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "dma_test.h"

using namespace std;


int main() {

	string rootDir = "data/";
	
	string dma_file = "dma.txt";
	string gold_file = "single_gold.txt";

	int input_size = n_bands * N + SIG_LENGTH * n_channel;
	int output_size = n_bands * SIG_LENGTH * n_channel;
	
	dataType* dma = new dataType[input_size+output_size];
	dataType* gold = new dataType[output_size];

	cout << "dma array size is " << output_size + input_size << endl;
	cout << "gold size is " << output_size << endl;

	if (!readData(rootDir, dma_file, dma, input_size)) {
		cout << "File " << rootDir << dma_file << " read" << endl;
	}
	if (!readData(rootDir, gold_file, gold, output_size)) {
		cout << "File " << rootDir << gold_file << " read" << endl;
	}

	cout << "File read completed\n";

	
	int input_offset = 0;
	int output_offset = input_size*sizeof(dataType);

	xdma_driver(dma, input_size, output_size, input_offset, output_offset);

	ofstream ofile;
	ofile.open((rootDir+"hw_results.txt").c_str());
	for(int i=0;i<output_size;i++)
	  ofile<<dma[input_size+i]<<endl;
	ofile.close();

	cout << "Max error is " << maxError(gold, dma, input_size) << endl;
	cout << "Total error is " << error(gold, dma, input_size) << endl;

	return 0;
}
