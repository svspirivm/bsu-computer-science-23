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
	std::vector<bool> tmp(number_of_vertices, false);
	std::vector<std::vector<bool>> adjacency_matrix(number_of_vertices, tmp);
	while (number_of_edges > 0) {
		int64_t vertex1 = 0, vertex2 = 0;
		fscanf(input, "%lld%lld", &vertex1, &vertex2);
		vertex1--;
		vertex2--;
		adjacency_matrix[vertex1][vertex2] = true;
		adjacency_matrix[vertex2][vertex1] = true;
		number_of_edges--;
	}
	fclose(input);
	for (size_t i = 0; i < adjacency_matrix.size(); i++) {
		for (size_t j = 0; j < adjacency_matrix[i].size(); j++) 
			fprintf(output, "%i%c", (int)adjacency_matrix[i][j], ' ');
		fprintf(output, "%c", '\n');
	}
	fclose(output);
	return 0;
}