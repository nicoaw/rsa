#include "math.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	long long e = atoi(argv[1]);
	long long p = atoi(argv[2]);
	long long q = atoi(argv[3]);
	long long d = inverse(e, (p - 1) * (q - 1));

	if((e * d) % ((p - 1) * (q - 1)) != 1)
	{
		cerr << "No positive inverse for e" << endl;
		return -1;
	}

	ifstream cyphertext(argv[4]);
	istream_iterator<string> first{cyphertext}, last;
	ostream_iterator<char> result{cout};

	auto decrypt = [d, p, q](string s)
	{
		try
		{
			long long c = stoi(s);
			return (char) ('A' + powmod(c, d, p * q) - 1);
		}
		catch(...)
		{
			return s[0] == '_' ? ' ' : s[0];
		}
	};

	transform(first, last, result, decrypt);

	return 0;
}
