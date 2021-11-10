#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

uint1024_t encryption(const uint1024_t& input, const std::pair<uint1024_t, int>& public_key)
{
	if (input == 1)
		return -1;
	else if (input == 0)
		return -2;
	uint1024_t n = public_key.first;
	int e = public_key.second;
	uint1024_t c = powm(input, e, n);
	return c;
}

uint1024_t decryption(const uint1024_t& cyphertext, const std::pair<uint1024_t, uint1024_t>& private_key)
{
	if (cyphertext == -1)
		return 1;
	else if (cyphertext == -2)
		return 0;
	uint1024_t n = private_key.first, d = private_key.second;
	uint1024_t output = powm(cyphertext, d, n);
	return output;
}

std::pair<std::pair<uint1024_t, int>, std::pair<uint1024_t, uint1024_t>> keyGenerator()
{
	const uint1024_t p = 4701195215349136403;
	const uint1024_t q = 4890704364257540107;
	uint1024_t n = p * q, phi = (p - 1) * (q - 1);
	int e = 65537;
	//if(gcd(e, p - 1) == 1 && gcd(e, q - 1) == 1)
	int x = 1;
	while ((x * phi + 1) % e != 0)
	{
		++x;
	}
	const uint1024_t d = (x * phi + 1) / e;
	return { { n, e }, { n, d } };
}

int main()
{
	uint64_t input;
	std::cout << "INPUT:\t";
	std::cin >> input;
	std::pair<std::pair<uint1024_t, int>, std::pair<uint1024_t, uint1024_t>> keys = keyGenerator();
	std::pair<uint1024_t, int> public_key = keys.first;
	std::pair<uint1024_t, uint1024_t> private_key = keys.second;
	const uint1024_t c = encryption(input, public_key);
	std::cout << "\nCYPHERTEXT:\t" << c << std::endl;
	const uint1024_t output = decryption(c, private_key);
	std::cout << "\nOUTPUT:\t" << output << "\n\n\n";
	std::cout << "The output is " << (input == output ? "CORRECT" : "INCORRECT") << std::endl;
}