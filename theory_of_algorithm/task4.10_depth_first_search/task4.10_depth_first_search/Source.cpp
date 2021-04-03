#pragma warning(disable : 4996)
#include<iostream>
#include<stdio.h>
#include<vector>
#include<queue>

void dfs(std::vector<std::vector<bool>>& graph, const std::int64_t& vertex, std::vector<bool>& visited, 
		 std::vector<int64_t>& identifiers, int64_t& index) {
	visited[vertex] = true;
	identifiers[vertex] = index++;
	for (size_t i = 0; i < graph.size(); i++)
		if (graph[vertex][i])
			if (!visited[i])
				dfs(graph, i, visited, identifiers, index);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* input = freopen("input.txt", "r", stdin);
	FILE* output = freopen("output.txt", "w", stdout);
	int64_t number_of_vertices = 0;
	fscanf(input, "%lld", &number_of_vertices);
	std::vector<int64_t> identifiers(number_of_vertices, 0);
	std::vector<bool> visited(number_of_vertices, false);
	std::vector<std::vector<bool>> adjacency_matrix(number_of_vertices, std::vector<bool>(number_of_vertices));

	for (size_t i = 0; i < number_of_vertices; i++) {
		for (size_t j = 0; j < number_of_vertices; j++) {
			int item = 0;
			fscanf(input, "%i", &item);
			adjacency_matrix[i][j] = (bool)item;
		}
	}
	fclose(input);
	
	std::queue<int64_t> q;
	int64_t index = 0;
	for (size_t i = 0; i < number_of_vertices; i++)
		if (!visited[i]) dfs(adjacency_matrix, i, visited, identifiers, index);


	for (size_t j = 0; j < identifiers.size(); j++)
		fprintf(output, "%lld%c", identifiers[j] + 1, ' ');
	fclose(output);
	return 0;
}