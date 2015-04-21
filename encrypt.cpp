#include "math.hpp"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char* argv[])
{
	long long e = atoi(argv[1]);
	long long pq = atoi(argv[2]);
	
	ifstream plaintext{argv[3]};
	istream_iterator<char> first{plaintext}, last;
	ostream_iterator<string> result{cout, " "};
	noskipws(plaintext);

	auto encrypt = [e, pq](char m) -> string
	{
		if(m == ' ')
			return "_";
		else if(isalpha(m))
			return to_string(powmod(tolower(m) - 'a' + 1, e, pq));
		else
			return string(1, m);
	};

	transform(first, last, result, encrypt);

	return 0;
}
