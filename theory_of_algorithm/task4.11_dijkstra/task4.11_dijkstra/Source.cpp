#pragma warning(disable : 4996)
#include<iostream>
#include<stdio.h>
#include<vector>
#include<set>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* input = freopen("input.txt", "r", stdin);
	FILE* output = freopen("output.txt", "w", stdout);
	int64_t number_of_vertices = 0, number_of_edges = 0;
	fscanf(input, "%lld%lld", &number_of_vertices, &number_of_edges);
	std::vector<std::vector<std::pair<int64_t, int64_t>>> adjacency_matrix(number_of_vertices);
	for (size_t i = 0; i < number_of_edges; i++) {
		int64_t first = 0, second = 0, length = 0;
		fscanf(input, "%lld%lld%lld", &first, &second, &length);
		first--;
		second--;
		adjacency_matrix[first].push_back(std::make_pair(second, length));
		adjacency_matrix[second].push_back(std::make_pair(first, length));
	}
	fclose(input);
	std::vector<int64_t> distances(number_of_vertices, INT64_MAX);
	std::set<std::pair<int64_t, int64_t>> s;
	s.insert(std::make_pair(0, 0));
	while (!s.empty()) {
		int64_t vertex = s.begin()->second;
		int64_t current_distance = s.begin()->first;
		s.erase(s.begin());
		distances[vertex] = current_distance;
		for (size_t i = 0; i < adjacency_matrix[vertex].size(); i++) {
			if (distances[vertex] + adjacency_matrix[vertex][i].second < distances[adjacency_matrix[vertex][i].first]) {
				s.erase(std::make_pair(distances[adjacency_matrix[vertex][i].first], adjacency_matrix[vertex][i].first));
				distances[adjacency_matrix[vertex][i].first] = distances[vertex] + adjacency_matrix[vertex][i].second;
				s.insert(std::make_pair(distances[adjacency_matrix[vertex][i].first], adjacency_matrix[vertex][i].first));
			}
		}
	}
	fprintf(output, "%lld", distances[distances.size() - 1]);
	fclose(output);
	return 0;
}