#pragma once
#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <bitset>
using namespace std;


class Decompressor {

private:
	string compressed_file, decompressed_file;

	string readCompressed(map <string, char> &codes, int &small_size) {
		ifstream inp(compressed_file, ios::binary);
		char c;
		string s = "";

		getline(inp, s, '\n');
		int table_size = atoi(s.c_str());
		getline(inp, s, '\n');
		int encoding_size = atoi(s.c_str());
		getline(inp, s, '\n');
		small_size = atoi(s.c_str());

		int i = 0;


		while (i < table_size) {
			inp.get(c);
			getline(inp, s, '\n');
			codes.insert(make_pair(s, c));
			i++;
		}
		s = "";
		inp.get(c);
		while (!inp.eof()) {

			
			s += bitset<8>(int8_t(c)).to_string();
			inp.get(c);
		}
		s = s.substr(0, encoding_size);
		return s;
	}

public:

	Decompressor() {
		decompressed_file = "";
		compressed_file = "";
	}

	Decompressor(string comp, string decomp) {
		compressed_file = comp;
		decompressed_file = decomp;
	}

	void decompress() {

		ofstream out;
		int small = 0;
		map <string, char>codes;
		string s = readCompressed(codes, small);

		out.open(decompressed_file);

		if (out.is_open()) {

			int end = small;
			string check;
			int i = 0;
			while (i + end <= s.size()) {
				check = s.substr(i, end);
				if (codes.find(check) != codes.end()) {
					out.put(codes[check]);

					i += end;
					end = small;

				}
				else {
					end++;

				}

			}

		}
		else out.close();

	}

};
#endif