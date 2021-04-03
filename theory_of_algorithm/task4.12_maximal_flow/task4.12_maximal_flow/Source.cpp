#include<iostream>
#include<vector>
#include<queue>

int main() {
	int64_t number_of_vertices = 0, number_of_edges = 0;
	std::cin >> number_of_vertices >> number_of_edges;
	std::vector<std::vector<int64_t>> capacities(number_of_vertices, std::vector<int64_t>(number_of_vertices, 0));
	for (size_t i = 0; i < number_of_edges; i++) {
		int64_t first = 0, second = 0, capacity = 0;
		std::cin >> first >> second >> capacity;
		first--;
		second--;
		capacities[first][second] += capacity;
	}
	int64_t maximal_flow = 0;
	while (true) {
		std::vector<int64_t> parent(number_of_vertices, -1);
		std::vector<bool> visited(number_of_vertices, false);
		std::queue<int64_t> q;
		visited[0] = true;
		q.push(0);
		while (!q.empty()) {
			int64_t vertex = q.front();
			q.pop();
			for (size_t i = 0; i < number_of_vertices; i++) {
				if (!visited[i] && capacities[vertex][i] > 0) {
					parent[i] = vertex;
					visited[i] = true;
					q.push(i);
				}
			}
		}
		if (!visited[number_of_vertices - 1]) break;
		int64_t aug_flow = INT64_MAX;
		int64_t destination = number_of_vertices - 1;
		while (destination != 0) {
			aug_flow = std::min(aug_flow, capacities[parent[destination]][destination]);
			destination = parent[destination];
		}
		destination = number_of_vertices - 1;
		while (destination != 0) {
			capacities[parent[destination]][destination] -= aug_flow;
			capacities[destination][parent[destination]] += aug_flow;
			destination = parent[destination];
		}
		maximal_flow += aug_flow;
	}
	std::cout << maximal_flow;
	return 0;
}