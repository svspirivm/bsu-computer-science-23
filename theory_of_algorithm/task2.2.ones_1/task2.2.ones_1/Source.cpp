//ƒано число N. Ќеобходимо определить, сколько есть бинарных строк длины N, в которых ровно K единиц.

#include<iostream>
#include<vector>
#include<stdio.h>

//uint64_t countOnes(const int& n, const int& k) {
//	std::vector<uint64_t> tmp(n + 1, 1);
//	std::vector<std::vector<uint64_t>> matrix(n + 1, tmp);
//	for (size_t i = 1; i <= n; i++) {
//		for (size_t j = 1; j <= i - 1; j++) {
//			matrix[i][j] = matrix[i - 1][j - 1] + matrix[i - 1][j];
//		}
//	}
//	uint64_t result = matrix[n][k];
//	result = result % (1000000000 + 7);
//	return result;
//}



uint64_t countOnes(const int& n, const int&k) {
	//Cnk = n!/((n-k)!k!) = n*(n - 1)* ... * (n-k+1)/k!
	int mod = 1000000007;
	uint64_t numerator = 1;
	uint64_t denominator = 1;
	for (size_t i = 0; i < k; i++) {
		denominator = (denominator * (i + 1)) % mod;
		numerator = (numerator * (n - i)) % mod;
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
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n = 0;
	int k = 0;

	scanf_s("%i%i", &n, &k);

	printf("%lld", countOnes(n, k));
	return 0;
}