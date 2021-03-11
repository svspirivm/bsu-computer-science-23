#pragma warning(disable : 4996)
#include<iostream>
#include<queue>
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

	std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> q(frequency.begin(), frequency.end());

	while (q.size() >= 2) {
		int64_t first = q.top();
		q.pop();
		int64_t second = q.top();
		q.pop();
		q.push(first + second);
		result += first + second;
	}

	FILE* file_out = freopen("huffman.out", "w", stdout);
	fprintf(file_out, "%lld", result);
	fclose(file_out);
	return 0;
}