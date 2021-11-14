#include<iostream>
#include<fstream>
#include<vector>

int howToGetThere(const int& n, const int& m) {
	int mod = 1000000007;
	uint64_t numerator = 1;
	uint64_t denominator = 1;
	for (size_t i = 0; i < n + m - 2; i++) {
		numerator = (numerator * (n + m - 2 - i)) % mod;
	}
	int k = n - m;
	for (size_t i = 0; i < n - 1; i++) {
		denominator = (denominator * (i + 1)) % mod;
	}
	for (size_t i = 0; i < m - 1; i++) {
		denominator = (denominator * (i + 1)) % mod;
	}


	//по теореме ферма a = a^p/mod(p)
	uint64_t remainder = 1;
	uint64_t power = mod - 2;
	while (power > 0) {
		if (power % 2 == 1) {
			remainder = (remainder * denominator) % mod;
		}
		denominator = (denominator * denominator) % mod;
		power >>= 1;
	}
	return (numerator * remainder) % mod;
}

int main() {
	std::ifstream input("input.txt");
	int n = 0;
	int m = 0;
	input >> n >> m;
	std::ofstream output("output.txt");
	output << howToGetThere(n, m);

	return 0;
}

//c из n + m - 2 по n - 1