#ifndef CRYPT_HPP
#define CRYPT_HPP

#include <boost/multiprecision/cpp_int.hpp>

struct RSAKey
{
	boost::multiprecision::cpp_int n, exponent;
};

boost::multiprecision::cpp_int decrypt(const RSAKey& privateKey, const boost::multiprecision::cpp_int& cypher);
boost::multiprecision::cpp_int encrypt(const RSAKey& publicKey, const boost::multiprecision::cpp_int& plain);
RSAKey makePrivateKey(const boost::multiprecision::cpp_int& p, const boost::multiprecision::cpp_int& q, const boost::multiprecision::cpp_int& e);
RSAKey makePublicKey(const boost::multiprecision::cpp_int& n, const boost::multiprecision::cpp_int& e);

#endif /* CRYPT_HPP */
