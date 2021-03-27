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
	number_of_vertices--;
	while (number_of_vertices > 0) {
		int64_t father = 0, child = 0;
		fscanf(input, "%lld%lld", &father, &child);
		child--;
		canonical_form[child] = father;
		number_of_vertices--;
	}
	fclose(input);
	for (size_t j = 0; j < canonical_form.size(); j++)
		fprintf(output, "%lld%c", canonical_form[j], ' ');
	fclose(output);
	return 0;
}