#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <map>
#include <cmath>
#include <queue>
#include "BinaryTree.h"
#include "Compressor.h"
#include "Decompressor.h"
using namespace std;

void do_everything() {
	string file_1, file_2;
	int choice;
	cout << "If you want to compress a file, enter 0." << endl << "If you want to decompress a file, enter 1." << endl;
	cin >> choice;

	if (!choice) {
		cout << "Input text file:";
		cin >> file_1;
		cout << "Output compressed file:";
		cin >> file_2;
		Compressor c(file_1, file_2);
		c.compressFile();
	}
	else {
		cout << "Input compressed file:";
		cin >> file_1;
		cout << "Output decompressed text file:";
		cin >> file_2;
		Decompressor d(file_1, file_2);
		d.decompress();
	}
}

int main() {

	do_everything();
	system("pause");
	return 0;
		
}