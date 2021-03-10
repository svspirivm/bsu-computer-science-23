#pragma warning(disable : 4996)
#include<iostream>
#include<algorithm>
#include<vector>
#include <stdio.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* file = freopen("huffman.in", "r", stdin);
	int amount = 0;
	fscanf(file, "%i", &amount);
	std::vector<int64_t> frequency;
	while (amount > 0) {
		int64_t tmp = 0;
		fscanf(file, "%lld", &tmp);
		frequency.push_back(tmp);
		amount--;
	}
	fclose(file);

	int64_t result = 0;
	std::vector<int64_t> v(frequency);
	while (v.size() >= 2) {
		std::sort(v.begin(), v.end());
		result += v[0] + v[1];
		v[1] += v[0];
		std::vector<int64_t> v1(v.begin() + 1, v.end());
		v = v1;
	}

	FILE* file_out = freopen("huffman.out", "w", stdout);
	fprintf(file_out, "%lld", result);
	fclose(file_out);
	return 0;
}