#include<iostream>
#pragma warning(disable : 4996)
#include <stdio.h>
#include<vector>
#include<queue>

//bool outOfBounds(const int& n, const int& m, const std::pair<int, int>& coordinates, const std::vector<std::vector<int>>& field) {
	//if ((coordinates.first < 0) || (coordinates.second < 0) || 
	//	(coordinates.first >= n) || (coordinates.second >= m) || 
	//	(field[coordinates.first][coordinates.second] == -1)) return true;
	//return false;
//}

int main() {
	int n = 0, m = 0;
	std::vector<std::vector<int>> field;
	const char* filename = "in.txt";
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* file = freopen(filename, "r", stdin);
	fscanf(file, "%d", &n);
	fscanf(file, "%d", &m);
	for (size_t i = 0; i < n; i++) {
		std::vector<int> tmp;
		for (size_t j = 0; j < m; j++) {
			int element = 0;
			fscanf(file, "%d", &element);
			tmp.push_back(element);
		}
		field.push_back(tmp);
	}
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	fscanf(file, "%d", &x1);
	fscanf(file, "%d", &y1);
	fscanf(file, "%d", &x2);
	fscanf(file, "%d", &y2);
	fclose(file);
	std::pair<int, int> begin(x1 - 1, y1 - 1);
	std::pair<int, int> end(x2 - 1, y2 - 1);
	const std::vector<std::pair<int, int>> moves = { {2, 1}, {2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1} };
	std::queue<std::pair<int, int>> positions;
	if (field[begin.first][begin.second] == 0) {
		positions.push(std::make_pair(begin.first, begin.second));
	}

	while (!positions.empty()) {
		std::pair<int, int> current_position = positions.front();
		positions.pop();
		if (current_position == end) break;
		if (field[current_position.first][current_position.second] == -1) continue;
		for (size_t j = 0; j < moves.size(); j++) {
			std::pair<int, int> new_position(current_position.first + moves[j].first, current_position.second + moves[j].second);
			if (!((new_position.first < 0) || (new_position.second < 0) ||
				(new_position.first >= n) || (new_position.second >= m) ||
				(field[new_position.first][new_position.second] == -1))) {

				field[new_position.first][new_position.second] = 1 + field[current_position.first][current_position.second];
				positions.push(new_position);
			}
		}
		field[current_position.first][current_position.second] = -1;
	}
	const char* output = "out.txt";
	FILE* file_output = freopen(output, "w", stdout);
	if (field[end.first][end.second] == -1)fprintf(file_output, "%s", "No");
	fprintf(file_output, "%d", field[end.first][end.second]);
	fclose(file_output);
	return 0;
}