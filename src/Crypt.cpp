#include "Crypt.hpp"
#include <random>
#include <stdexcept>

namespace mp = boost::multiprecision;

mp::cpp_int inverse(const mp::cpp_int& a, const mp::cpp_int& p);
mp::cpp_int powmod(mp::cpp_int a, mp::cpp_int b, const mp::cpp_int& n);

mp::cpp_int decrypt(const RSAKey& privateKey, const mp::cpp_int& cypher)
{
	return powmod(cypher, privateKey.exponent, privateKey.n);
}

mp::cpp_int encrypt(const RSAKey& publicKey, const mp::cpp_int& plain)
{
	return powmod(plain, publicKey.exponent, publicKey.n);
}

mp::cpp_int inverse(const mp::cpp_int& a, const mp::cpp_int& p)
{
	mp::cpp_int t = 0, newt = 1;
	mp::cpp_int r = p, newr = a;

	while(newr != 0)
	{
		mp::cpp_int q = r / newr;
		
		mp::cpp_int oldt = newt;
		mp::cpp_int oldr = newr;		
		
		newt = t - q * newt;
		newr = r - q * newr;
		
		t = oldt;
		r = oldr;
	}

	if(t < 0)
		t += p;

	return t;
}

RSAKey makePrivateKey(const mp::cpp_int& p, const mp::cpp_int& q, const mp::cpp_int& e)
{
	return RSAKey{p * q, inverse(e, (p - 1) * (q - 1))};
}

RSAKey makePublicKey(const mp::cpp_int& n, const mp::cpp_int& e)
{
	return RSAKey{n, e};
}

mp::cpp_int powmod(mp::cpp_int a, mp::cpp_int b, const mp::cpp_int& n)
{
	mp::cpp_int result = b & 1 ? a : 1;

	b >>= 1;

	for(; b != 0; b >>= 1)
	{
		a = mp::pow(a, 2) % n;

		if(b & 1)
			result *= a;
	}

	return result % n;
}
