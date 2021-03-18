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
	int64_t number_of_cities = 0, number_of_roads = 0;
	fscanf(input, "%lld", &number_of_cities);
	fscanf(input, "%lld", &number_of_roads);
	std::vector<int64_t> tmp;
	std::vector<std::vector<int64_t>> graph(number_of_cities, tmp);
	std::vector<bool> visited(number_of_cities, false);
	for (size_t k = 0; k < number_of_roads; k++) {
		int64_t first = 0, second = 0;
		fscanf(input, "%lld%lld", &first, &second);
		first--;
		second--;
		graph[first].push_back(second);
		graph[second].push_back(first);
	}
	int64_t result = 0;
	for (size_t k = 0; k < number_of_cities; k++) {
		if (!visited[k]) {
			visited[k] = true;
			result++;
			std::queue<int64_t> queue_for_bfs;
			queue_for_bfs.push(k);
			while (!queue_for_bfs.empty()) {
				int64_t element = queue_for_bfs.front();
				for (size_t i = 0; i < graph[element].size(); i++) {
					if (!visited[graph[element][i]]) {
						queue_for_bfs.push(graph[element][i]);
						visited[graph[element][i]] = true;
					}
				}
				queue_for_bfs.pop();
			}

		}
	}
	result--;
	fprintf(output, "%lld", result);
	fclose(output);
	return 0;
}