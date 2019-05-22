#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "helper.h"

using namespace std;

int read_data(string dir, float*& data, const int size,const int max_size) {
	ifstream file;
	file.open(dir, ios::binary);
	int retval = 0;

	if (file.fail()) {
		cout << "File does not exist \n";
		return 1;
	}

	if (file.good()) {
		data = new float[max_size];
		if (!file.read(reinterpret_cast<char*>(&data[0]), sizeof(float) * size)) {
			cout<<"error \n";
			retval = 1;
		}
	}
	file.close();

	if (retval) delete[] data;
	return retval;
}