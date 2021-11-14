#pragma warning(disable : 4996)
#include<iostream>
#include<stdio.h>
#include<vector>
#include<queue>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* input = freopen("input.txt", "r", stdin);
	FILE* output = freopen("output.txt", "w", stdout);
	int64_t number_of_vertices = 0;
	fscanf(input, "%lld", &number_of_vertices);
	std::vector<int64_t> identifiers(number_of_vertices, 0);
	std::vector<bool> visited(number_of_vertices, false);
	std::vector<std::vector<bool>> adjacency_matrix(number_of_vertices, visited);

	for (size_t i = 0; i < number_of_vertices; i++) {
		for (size_t j = 0; j < number_of_vertices; j++) {
			int item = 0;
			fscanf(input, "%i", &item);
			adjacency_matrix[i][j] = (bool)item;
		}
	}
	fclose(input);
	int64_t next_index = 0;
	for (size_t k = 0; k < adjacency_matrix.size(); k++) {
		if (identifiers[k] == 0) {
			std::queue<int64_t> q;
			visited[k] = true;
			identifiers[k] = next_index;
			q.push(k);
			next_index++;
			while (!q.empty()) {
				int64_t vertex = q.front();
				q.pop();
				for (size_t u = 0; u < adjacency_matrix[vertex].size(); u++)
					if (adjacency_matrix[vertex][u] && !visited[u]) {
						visited[u] = true;
						identifiers[u] = next_index;
						next_index++;
						q.push(u);
					}
			}
		}
	}
	for (size_t j = 0; j < identifiers.size(); j++)
		fprintf(output, "%lld%c", identifiers[j] + 1, ' ');
	fclose(output);
	return 0;
}