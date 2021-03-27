#pragma warning(disable : 4996)
#include<iostream>
#include<stdio.h>
#include<vector>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* input = freopen("input.txt", "r", stdin);
	FILE* output = freopen("output.txt", "w", stdout);
	int64_t number_of_vertices = 0, number_of_edges = 0;
	fscanf(input, "%lld%lld", &number_of_vertices, &number_of_edges);
	std::vector<int64_t> tmp(1, 0);
	std::vector<std::vector<int64_t>> adjacency_list(number_of_vertices, tmp);
	while (number_of_edges > 0) {
		int64_t first = 0, second = 0;
		fscanf(input, "%lld%lld", &first, &second);
		adjacency_list[first - 1][0]++;
		adjacency_list[first - 1].push_back(second);
		adjacency_list[second - 1][0]++;
		adjacency_list[second - 1].push_back(first);
		number_of_edges--;
	}
	fclose(input);

	for (size_t i = 0; i < adjacency_list.size(); i++) {
		for (size_t j = 0; j < adjacency_list[i].size(); j++)
			fprintf(output, "%lld%c", adjacency_list[i][j], ' ');
		fprintf(output, "%c", '\n');
	}
	fclose(output);
	return 0;
}