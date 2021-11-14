#pragma warning(disable : 4996)
#include<iostream>
#include<stdio.h>
#include<map>
#include<algorithm>
#include<vector>

int main() {
	int64_t n = 0, n_squared = 0;
	std::map<int64_t, int64_t> frequency;
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* file = freopen("input.txt", "r", stdin);
	fscanf(file, "%lld", &n);
	n_squared = n * n;
	while (n_squared > 0) {
		n_squared--;
		int64_t tmp = 0;
		fscanf(file, "%lld", &tmp);
		frequency[tmp]++;
	}

	std::vector<int64_t> numbers(n, 0);
	numbers[0] = (*frequency.begin()).first / 2;
	(*frequency.begin()).second--;

	for (size_t i = 1; i < n; i++) {
		std::map<int64_t, int64_t>::iterator iter = std::find_if(frequency.begin(), frequency.end(),
			[](const std::pair<int64_t, int64_t>& p) -> bool {
				return p.second > 0;
			});
		numbers[i] = iter->first - numbers[0];
		for (size_t j = 0; j < i; j++) frequency[numbers[i] + numbers[j]] -= 2;
		frequency[numbers[i] + numbers[i]]--;
	}

	FILE* file_out = freopen("output.txt", "w", stdout);
	for (const int64_t& x : numbers) {
		fprintf(file_out, "%lld%c", x, '\n');
	}
	fclose(file_out);
	return 0;
}