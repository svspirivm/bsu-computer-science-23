#pragma warning(disable : 4996)
#include<iostream>
#include<stdio.h>
#include<vector>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* input = freopen("input.in", "r", stdin);
	FILE* output = freopen("output.out", "w", stdout);
	int64_t number_of_crossroads = 0, number_of_roads = 0;
	int64_t start = 0, end = 0;
	fscanf(input, "%lld%lld", &number_of_crossroads, &number_of_roads);
	fscanf(input, "%lld%lld", &start, &end);
	//numbers are gonna be from zero
	start--;
	end--;
	if (start == end) {
		fclose(input);
		fprintf(output, "%i%c%lld", 0, '\n', start + 1);
		fclose(output);
		return 0;
	}

	//adjaceny_list[i] contains all vertices where you can get from i vertex and weights
	std::vector<std::pair<int64_t, int64_t>> tmp;
	std::vector<std::vector<std::pair<int64_t, int64_t>>> adjacency_list(number_of_crossroads, tmp);
	for (size_t i = 0; i < number_of_roads; i++) {
		int64_t crossroad1 = 0, crossroad2 = 0, time = 0;
		fscanf(input, "%lld%lld%lld", &crossroad1, &crossroad2, &time);
		crossroad1--;
		crossroad2--;
		adjacency_list[crossroad1].push_back(std::make_pair(crossroad2, time));
		adjacency_list[crossroad2].push_back(std::make_pair(crossroad1, time));
	}
	fclose(input);
	std::vector<int64_t> distances(number_of_crossroads, INT64_MAX);
	distances[start] = 0;
	std::vector<bool> visited(number_of_crossroads, false);
	std::vector<int64_t> parent(number_of_crossroads);

	//dijkstra
	for (size_t i = 0; i < number_of_crossroads; i++) {
		int64_t vertex = -1;
		for (size_t j = 0; j < number_of_crossroads; j++)
			if (!visited[j] && (vertex == -1 || distances[j] < distances[vertex]))
				vertex = j;
		if (distances[vertex] == INT64_MAX) break;
		visited[vertex] = true;

		for (size_t j = 0; j < adjacency_list[vertex].size(); j++) {
			int64_t where_to = adjacency_list[vertex][j].first;
			int64_t length = adjacency_list[vertex][j].second;
			if (distances[vertex] + length + adjacency_list[where_to].size() < distances[where_to]) {
				distances[where_to] = distances[vertex] + length + adjacency_list[where_to].size();
				parent[where_to] = vertex;
			}
		}
	}
	std::vector<int64_t> path;
	for (size_t i = end; i != start; i = parent[i]) path.push_back(i);
	path.push_back(start);

	fprintf(output, "%lld%c", distances[end] - adjacency_list[end].size(), '\n');
	for (std::vector<int64_t>::reverse_iterator rit = path.rbegin(); rit != path.rend(); rit++) 
		fprintf(output, "%lld%c", *rit + 1, ' ');
	fclose(output);
	return 0;
}