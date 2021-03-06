#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<queue>

int64_t countDamage(const int& n, const int& m, const std::vector<int>& importance) {
	std::vector<int64_t> tmp(n, 0);
	std::vector<std::vector<int64_t>> damaged(n, tmp);
	std::vector<int64_t> prefix_sums;
	std::vector<int64_t> prefix_sums_of_squares;

	prefix_sums.push_back(importance[0]);
	prefix_sums_of_squares.push_back(importance[0] * importance[0]);
	for (size_t i = 1; i < importance.size(); i++) {
		prefix_sums.push_back(prefix_sums[i - 1] + importance[i]);
		prefix_sums_of_squares.push_back(prefix_sums_of_squares[i - 1] + importance[i] * importance[i]);
	}

	std::vector<int64_t> postfix_sums(n, 0);
	std::vector<int64_t> postfix_sums_of_squares(n, 0);
	postfix_sums[n - 1] = importance[n - 1];
	postfix_sums_of_squares[n - 1] = importance[n - 1] * importance[n - 1];
	for (int i = importance.size() - 2; i >= 0; i--) {
		postfix_sums[i] = postfix_sums[i + 1] + importance[i];
		postfix_sums_of_squares[i] = postfix_sums_of_squares[i + 1] + importance[i] * importance[i];
	}

	std::cout << '\n';
	for (auto i : prefix_sums) std::cout << i << " ";
	std::cout << "\n";
	std::cout << '\n';
	for (auto i : prefix_sums_of_squares) std::cout << i << " ";
	std::cout << "\n";
	std::cout << '\n';
	for (auto i : postfix_sums) std::cout << i << " ";
	std::cout << "\n";
	std::cout << '\n';
	for (auto i : postfix_sums_of_squares) std::cout << i << " ";
	std::cout << "\n";




	for (size_t i = 0; i < damaged.size(); i++) {
		for (size_t j = i + 1; j < damaged.size(); j++) {
			damaged[i][j] = 0.5 *  ( (-1) * prefix_sums[j - 1] * prefix_sums[j - 1] + prefix_sums_of_squares[j - 1] +
				(-1) * postfix_sums[j - 1] * postfix_sums[j - 1] + prefix_sums_of_squares[j - 1]);

		}
	}
	std::cout << "\n";
	for (auto item : damaged) {
		for (auto i : item) std::cout << i << " ";
		std::cout << "\n";
	}
	/*for (size_t i = 0; i < damaged.size(); i++) {
		damaged[i][0] = damaged[0][i];
	}

	for (size_t i = 0; i < damaged.size(); i++) {
		for (size_t j = 1; j < m + 1; j++) {
			damaged[j][i] = INT64_MAX;
			for (size_t k = 0; k < i; k++) {
				damaged[j][i] = std::min(damaged[j][i], damaged[j - 1][k] + damaged[i][k + 1]);
			}
		}
	}
	std::cout << "\n";
	for (auto item : damaged) {
		for (auto i : item) std::cout << i << " ";
		std::cout << "\n";
	}*/
	std::cout << "\n" << damaged[0][damaged.size() - m - 1];
	return damaged[0][damaged.size() - m - 1];
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