#pragma warning(disable : 4996)
#include<iostream>
#include<stdio.h>
#include<vector>

int64_t ROWS = 0, COLUMNS = 0;
int MOVES_X[4] = { 1, 1, -1, -1 };
int MOVES_Y[4] = { 1, -1, -1, 1 };
int64_t FIELD[10][10];
bool VISITED[10][10];
std::vector<std::vector<std::pair<int64_t, int64_t>>> RESULT;

bool inBounds(const int64_t& x, const int64_t& y) {
	return x >= 0 && y >= 0 && x < ROWS && y < COLUMNS;
}

void addBishop(const int64_t& x, const int64_t& y) {
	for (size_t i = 0; i < 4; i++) {
		int64_t current_x = x;
		int64_t current_y = y;
		while (inBounds(current_x + MOVES_X[i], current_y + MOVES_Y[i])) {
			current_x += MOVES_X[i];
			current_y += MOVES_Y[i];
			if (!VISITED[current_x][current_y]) FIELD[current_x][current_y]++;
			else break;
		}
	}
	FIELD[x][y] = 1;
}

void removeBishop(const int64_t& x, const int64_t& y) {
	for (size_t i = 0; i < 4; i++) {
		int64_t current_x = x;
		int64_t current_y = y;
		while (inBounds(current_x + MOVES_X[i], current_y + MOVES_Y[i])) {
			current_x += MOVES_X[i];
			current_y += MOVES_Y[i];
			if (!VISITED[current_x][current_y]) FIELD[current_x][current_y]--;
			else break;
		}
	}
	FIELD[x][y] = 0;
}

void dfs(const int64_t& x, const int64_t& y, std::vector<std::pair<int64_t, int64_t>>& currentBishop) {
	int64_t current_x = x;
	int64_t current_y = y;
	for (size_t k = x; k < ROWS; k++) {
		for (size_t l = (k == current_x ? current_y + 1 : 0); l < COLUMNS; ++l) {
			if (!VISITED[k][l] && !FIELD[k][l]) {
				currentBishop.push_back(std::make_pair(k, l));
				addBishop(k, l);
				dfs(k, l, currentBishop);
				if (currentBishop.size() > RESULT[RESULT.size() - 1].size()) {
					RESULT.clear();
					RESULT.push_back(currentBishop);
				}
				else if (currentBishop.size() == RESULT[RESULT.size() - 1].size()) RESULT.push_back(currentBishop);
				removeBishop(k, l);
				currentBishop.pop_back();
			}
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* input = freopen("input.txt", "r", stdin);
	FILE* output = freopen("output.txt", "w", stdout);
	fscanf(input, "%lld", &ROWS);
	fscanf(input, "%lld", &COLUMNS);
	for (size_t i = 0; i < ROWS; i++)
		for (size_t j = 0; j < COLUMNS; j++)
			fscanf(input, "%i", &VISITED[i][j]);
	fclose(input);
	
	RESULT.push_back(std::vector<std::pair<int64_t, int64_t>>(0));
	for (size_t k = 0; k < ROWS; k++) {
		for (size_t l = 0; l < COLUMNS; l++) {
			if (!VISITED[k][l]) {
				std::vector<std::pair<int64_t, int64_t>> current_bishop(1, std::make_pair(k, l));
				addBishop(k, l);
				dfs(k, l, current_bishop);
				removeBishop(k, l);
			}
		}
	}
	fprintf(output, "%d%c%d%c", RESULT.size(), '\n', RESULT[0].size(), '\n');
	for (size_t i = 0; i < RESULT.size(); i++) {
		for (size_t j = 0; j < RESULT[i].size(); j++) {
			fprintf(output, "%lld%c%lld", RESULT[i][j].first, ' ', RESULT[i][j].second);
			if (j != RESULT[i].size() - 1) fprintf(output, "%c", ' ');
		}
		if (i != RESULT.size() - 1) fprintf(output, "%c", '\n');
	}
	fclose(output);
	return 0;
}