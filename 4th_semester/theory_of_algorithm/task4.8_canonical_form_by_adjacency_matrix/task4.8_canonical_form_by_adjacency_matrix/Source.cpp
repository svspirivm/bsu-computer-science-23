#pragma warning(disable : 4996)
#include<iostream>
#include<stdio.h>
#include<vector>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* input = freopen("input.txt", "r", stdin);
	FILE* output = freopen("output.txt", "w", stdout);
	int64_t number_of_vertices = 0;
	fscanf(input, "%lld", &number_of_vertices);
	std::vector<int64_t> canonical_form(number_of_vertices, 0);
	for (size_t i = 0; i < number_of_vertices; i++) {
		for (size_t j = 0; j < number_of_vertices; j++) {
			int64_t item = 0;
			fscanf(input, "%lld", &item);
			if (item == 1) canonical_form[j] = i + 1;
		}
	}
	fclose(input);

	for (size_t j = 0; j < canonical_form.size(); j++)
		fprintf(output, "%lld%c", canonical_form[j], ' ');
	fclose(output);
	return 0;
}