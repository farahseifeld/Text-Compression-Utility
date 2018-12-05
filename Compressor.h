#pragma once
#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <queue>
#include "binaryTree.h"
using namespace std;


class Compressor {

private: 

	struct node {
		bool leaf = false;
		string s;
		double p;
		binaryTree <string, double> b;
	};

	struct symbol {
		double p;
		string code;

	};

	struct compare
	{
		bool operator()(const node& l, const node& r)
		{
			return l.p > r.p;
		}
	};
	
		string uncompressed_file, compressed_file;

		double countFile(map <char, int> &m) {

		ifstream inp;
		inp.open(uncompressed_file);
		double cnt = 0;
		char c;
		if (inp.is_open()) {
			inp.get(c);
			while (!inp.eof()) {
				cnt++;
				if (m.find(c) != m.end())
					m[c]++;
				else m.insert(pair<char, int>(c, 1));
				inp.get(c);
			}

		}
		else inp.close();
		inp.close();

		return cnt;
	}

		void buildHeap(map<char, int> m, priority_queue<node, vector<node>, compare> &pq, double cnt, map <char, symbol> & huff) {

		string s; symbol h;
		for (std::map<char, int>::iterator it = m.begin(); it != m.end(); it++) {
			node n;
			n.leaf = true;
			n.p = it->second / cnt;
			n.s = string(1, it->first);
			n.b.insert(n.s, n.p);
			pq.push(n);

			h.p = n.p;
			h.code = "";
			huff.insert(make_pair(it->first, h));
		}

	}

		node buildTree(priority_queue<node, vector<node>, compare> &pq) {

		node n1, n2, n12;
		if (pq.size() == 1) {
			n1 = pq.top();
			pq.pop();
			return n1;
		}
		while (!pq.empty()) {

			n1 = pq.top();
			pq.pop();
			if (!pq.empty()) {
				n2 = pq.top();
				pq.pop();

				n12.leaf = false;
				n12.p = n1.p + n2.p;
				n12.s = n1.s + n2.s;
				n12.b.merge(n12.s, n12.p, n1.b, n2.b);
				pq.push(n12);
			}


		}

		return n12;

	}

		void createTable(node n, map <char, symbol> &codes, map<char, int> m) {

		string s;
		for (std::map<char, int>::iterator it = m.begin(); it != m.end(); it++) {
			n.b.getCode(string(1, it->first), s);
			codes[it->first].code = s;
			s = "";
		}
	}

		string encodeFile(map<char, symbol> codes) {

		ifstream inp;
		inp.open(uncompressed_file);
		string out = "";
		if (inp.is_open()) {

			//ofstream out;
			//out.open("compressed_" +infile);
			//if (out.is_open()) {
			char c;
			inp.get(c);
			while (!inp.eof()) {
				//out << codes[c].code;
				out += codes[c].code;
				inp.get(c);
			}
			//}
			//else {
			//	out.close(); inp.close();
			//}
		}
		else inp.close();
		return out;
	}

		int printTable(map <char, symbol> m) {

		double L = 0;
		double H = 0;
		int min = 50000000;
		for (std::map<char, symbol>::iterator it = m.begin(); it != m.end(); it++) {
			//cout << it->first << " : " << it->second.p << " - " << it->second.code << endl;
			if (it->second.code.size() < min)
				min = it->second.code.size();
			L += it->second.p*it->second.code.size();
			H += it->second.p * (log2(1 / it->second.p));
		}

		cout << "<L>= " << L << endl;
		cout << "H = " << H << endl;
		cout << "Compression Ratio (<L>/8) = " << L / 8 << endl;
		cout << "Efficiency (H/<L>) = " << (H / L) * 100 << "%" << endl;

		return min;
	}

		int8_t convert(string b) {

		int n = b.size();
		int8_t byte = 0;
		for (int i = 0; i < n; i++)
		{
			if (b[i] == '0')
				byte = (0 << 7 - i) | byte;
			else
				byte = (1 << 7 - i) | byte;
		}
		return byte;
	}

		void writeBitstoFile(string out, map <char, symbol> codes, int encoding_size, int small_size) {

		int8_t cache; string byte;
		ofstream op(compressed_file, ofstream::binary);

		op << codes.size() << endl;
		op << encoding_size << endl;
		op << small_size << endl;

		for (map<char, symbol>::iterator it = codes.begin(); it != codes.end(); it++) {

			op << it->first << it->second.code << endl;
		}

		int size = out.size() / 8;
		for (int j = 0; j< size; j++) {
			byte = out.substr(0, 8);
			out = out.substr(8);
			//cout << "byte " << byte << endl;
			cache = convert(byte);
			op.put(cache);
			//cout << j << endl;
		}
		int n = out.size();
		if (out.size() > 0) {
			for (int i = 0; i < 8 - n; i++)
				out += '0';
			byte = out;
			cache = convert(byte);
			//cout << int(cache) << endl;
			op.put(cache);
		}
	}

	
	public:

		Compressor() {
			uncompressed_file = "";
			compressed_file = "";
		}

		Compressor(string uncomp, string comp) {
			uncompressed_file = uncomp;
			compressed_file = comp;
		}

		void compressFile() {

		map <char, int> m;
		map <char, symbol> codes;
		double cnt = countFile(m);
		priority_queue<node, vector<node>, compare> pq;
		buildHeap(m, pq, cnt, codes);
		node tree = buildTree(pq);

		createTable(tree, codes, m);
		int small_size = printTable(codes);
		string out = encodeFile(codes);
		int encoding_size = out.size();
		//cout << "out.size()= " << out.size() << endl;
		ofstream myo;
		myo.open("bin" + uncompressed_file);
		myo << out;
		writeBitstoFile(out, codes, encoding_size, small_size);
	}

};
#endif