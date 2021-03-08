#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cmath>

int64_t countDamage(const int& n, const int& m, const std::vector<int>& importance) {
	std::vector<int64_t> tmp(n, 0);
	std::vector<std::vector<int64_t>> damaged(n, tmp);
	std::vector<int64_t> tmp1(m + 1, 0);
	std::vector<std::vector<int64_t>> result(n, tmp1);

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			damaged[i][j] = damaged[i][j - 1];
			for (int k = i; k < j; k++) {
				damaged[i][j] += importance[k] * importance[j];
			}
		}
	}
	std::cout << "\n";
	for (auto item : damaged) {
		for (auto i : item) std::cout << i << " ";
		std::cout << "\n";
	}
	
	for (int i = 0; i < n; i++)
		result[i][0] = damaged[0][i];

	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= m; j++) {
			result[i][j] = INT64_MAX / 2;
			for (int k = 0; k < i; k++) {
				result[i][j] = std::min(result[i][j], result[k][j - 1] + damaged[k + 1][i]);
			}
		}
	}

	std::cout << "\n";
	for (auto item : result) {
		for (auto i : item) std::cout << i << " ";
		std::cout << "\n";
	}

	std::cout << "\n" << result[n - 1][m];
	return result[n - 1][m];
}

int main() {
	std::ifstream input("input.txt");
	int number_of_stations = 0, number_to_ruin = 0;
	input >> number_of_stations >> number_to_ruin;
	std::vector<int> importances;
	int counter = number_of_stations;
	while (counter > 0) {
		counter--;
		int tmp = 0;
		input >> tmp;
		importances.push_back(tmp);
	}
	int64_t result = countDamage(number_of_stations, number_to_ruin, importances);
	std::ofstream output("output.txt");
	output << result;
	return 0;
}