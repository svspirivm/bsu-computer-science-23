#include<iostream>
#pragma warning(disable : 4996)
#include <stdio.h>
#include<vector>
#include<utility>
#include<algorithm>
//¬ыведите минимальное число атомарных операций умножени€, необходимое дл€ перемножени€ s матриц.

int64_t minOperations(const std::vector<int>& dimensions) {
	int n = dimensions.size();
	std::vector<int64_t> tmp(n, 0);
	std::vector<std::vector<int64_t>> result(n, tmp);
	for (int l = 2; l < n; l++) {
		for (int i = 1; i < n - l + 1; i++) {
			int j = i + l - 1;
			result[i][j] = INT64_MAX;
			for (int k = i; k < j; k++) {
				int64_t cost = result[i][k] + result[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
				if (cost < result[i][j]) result[i][j] = cost;
			}
			//printf("%i%c", result[i][j], ' ');
		}
		//printf("%c", '\n');
	}

	return result[1][n-1];
}

int main() {
	int num_of_matrices = 0;
	std::vector<int> dimensions;

	const char* input = "input.txt";
	FILE* filein = freopen(input, "r", stdin);

	fscanf(filein, "%i", &num_of_matrices);
	int tmp1 = 0;
	int tmp2 = 0;
	fscanf(filein, "%i%i", &tmp1, &tmp2);
	dimensions.push_back(tmp1);
	dimensions.push_back(tmp2);
	num_of_matrices--;

	while (num_of_matrices > 0) {
		num_of_matrices--;
		int tmp1 = 0;
		int tmp2 = 0;
		fscanf(filein,"%i%i", &tmp1, &tmp2);
		dimensions.push_back(tmp2);
	}
	fclose(filein);

	const char* filename = "output.txt";
	FILE* file = freopen(filename, "w", stdout);
	fprintf(file, "%lld", minOperations(dimensions));
	fclose(file);
	return 0;
}