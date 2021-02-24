#pragma warning(disable : 4996)
#include <stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>

int64_t countMosquitos(const std::vector<int>& mosquitos) {
	if (mosquitos.size() == 2) return -1;
	std::vector<int64_t> result(mosquitos.size(), 0);
	result[0] = mosquitos[0];
	result[1] = INT64_MIN;
	result[2] = mosquitos[0] + mosquitos[2];
	for (size_t i = 3; i < mosquitos.size(); i++) { 
		result[i] = std::max(result[i - 2], result[i - 3]) + mosquitos[i];
	}

	return result[result.size() - 1];
}

int main() {
	int num_water_lilys = 0;
	std::vector<int> where_mosquitos;

	const char* input = "input.txt";
	FILE* filein = freopen(input, "r", stdin);

	fscanf(filein, "%i", &num_water_lilys);
	while (num_water_lilys > 0) {
		num_water_lilys--;
		int tmp = 0;
		fscanf(filein, "%i", &tmp);
		where_mosquitos.push_back(tmp);
	}
	fclose(filein);

	const char* filename = "output.txt";
	FILE* file = freopen(filename, "w", stdout);
	fprintf(file, "%lld", countMosquitos(where_mosquitos));
	fclose(file);

	return 0;
}