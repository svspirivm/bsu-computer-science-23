#pragma warning(disable : 4996)
#include <stdio.h>
#include <vector>
#include <algorithm>

const int64_t MAXN = 200000; 

struct Edge {
	int64_t from, to, capacity, flow;
};

int64_t number_of_vertices, distances[MAXN], ptr[MAXN], q[MAXN];
std::vector<Edge> edges;
std::vector<int64_t> graph[MAXN];

void add_edge(const int64_t& a, const int64_t& b, const int64_t& cap) {
	Edge e1 = { a, b, cap, 0 };
	Edge e2 = { b, a, 0, 0 };
	graph[a].push_back((int64_t)edges.size());
	edges.push_back(e1);
	graph[b].push_back((int64_t)edges.size());
	edges.push_back(e2);
}

bool bfs() {
	int64_t qh = 0, qt = 0;
	q[qt++] = 0;
	memset(distances, -1, number_of_vertices * sizeof distances[0]);
	distances[0] = 0;
	while (qh < qt && distances[number_of_vertices - 1] == -1) {
		int64_t v = q[qh++];
		for (size_t i = 0; i < graph[v].size(); ++i) {
			int64_t id = graph[v][i],
				to = edges[id].to;
			if (distances[to] == -1 && edges[id].flow < edges[id].capacity) {
				q[qt++] = to;
				distances[to] = distances[v] + 1;
			}
		}
	}
	return distances[number_of_vertices - 1] != -1;
}

int64_t dfs(const int64_t& v, const int64_t& flow) {
	if (!flow)  return 0;
	if (v == number_of_vertices - 1)  return flow;
	for (; ptr[v] < (int64_t)graph[v].size(); ++ptr[v]) {
		int64_t id = graph[v][ptr[v]], to = edges[id].to;
		if (distances[to] != distances[v] + 1) continue;
		int64_t pushed = dfs(to, std::min(flow, edges[id].capacity - edges[id].flow));
		if (pushed) {
			edges[id].flow += pushed;
			edges[id ^ 1].flow -= pushed;
			return pushed;
		}
	}
	return 0;
}

int64_t dinic() {
	int64_t flow = 0;
	for (;;) {
		if (!bfs()) break;
		memset(ptr, 0, number_of_vertices * sizeof ptr[0]);
		while (int64_t pushed = dfs(0, INT64_MAX))
			flow += pushed;
	}
	return flow;
}

int main() {
	int64_t number_of_edges = 0;
	scanf("%lld%lld", &number_of_vertices, &number_of_edges);
	for (size_t i = 0; i < number_of_edges; i++) {
		int64_t first = 0, second = 0, capacity = 0;
		scanf("%lld%lld%lld", &first, &second, &capacity);
		first--;
		second--;
		add_edge(first, second, capacity);
	}
	int64_t maximal_flow = dinic();
	printf("%lld", maximal_flow);
	return 0;
}
