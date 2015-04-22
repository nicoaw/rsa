#include "math.hpp"
#include <cmath>
#include <cstdint>

long long powmod(long long a, long long b, long long n)
{
	long long result = b & 1 ? a : 1;

	b >>= 1;

	for(; b != 0; b >>= 1)
	{
		a = (long long) pow(a, 2) % n;

		if(b & 1)
			result *= a;
	}

	return result % n;
}

long long inverse(long long a, long long n)
{
	long long t = 0, newt = 1;
	long long r = n, newr = a;

	while(newr != 0)
	{
		long long q = r / newr;
		
		long long oldt = newt;
		long long oldr = newr;		
		
		newt = t - q * newt;
		newr = r - q * newr;
		
		t = oldt;
		r = oldr;
	}

	if(t < 0)
		t += n;

	return t;
}
