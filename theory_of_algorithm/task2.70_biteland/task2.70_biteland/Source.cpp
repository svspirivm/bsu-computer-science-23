#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cmath>

int64_t countDamage(const int& n, const int& m, const std::vector<int>& importance) {
	//std::vector<int64_t> tmp(n, 0);
	//std::vector<std::vector<int64_t>> damaged(n, tmp);
	//for (size_t i = 0; i < damaged.size(); i++) {
	//	for (size_t j = i + 1; j < damaged.size(); j++) {
	//		//damaged[i][j] = damaged[i][j - 1];
	//		for (size_t k = i; k < j; k++) {
	//			damaged[i][j] += importance[j] * importance[k];
	//		}
	//		//damaged[j][i] = damaged[i][j];
	//	}
	//}
	//std::cout << "\n";
	//for (auto item : damaged) {
	//	for (auto i : item) std::cout << i << " ";
	//	std::cout << "\n";
	//}
	/*for (size_t i = 0; i < damaged.size(); i++) {
		damaged[i][0] = damaged[0][i];
		for (size_t j = 1; j < m + 1; j++) {
			damaged[j][i] = INT64_MAX;
			for (size_t k = i; k < j; k++) {
				damaged[j][i] = std::min(damaged[j][i], damaged[j - 1][k] + damaged[j][k + 1]);
			}
		}
	}*/
	/*std::cout << "\n";
	for (auto item : damaged) {
		for (auto i : item) std::cout << i << " ";
		std::cout << "\n";
	}
	std::cout << "\n" << damaged[0][damaged.size() - m - 1];
	return damaged[0][damaged.size() - m - 1];*/
	int64_t length = 1;
	for (int i = 1; i < n; i++) {
		length *= i;
	}
	for (int i = 1; i <= m; i++) {
		length /= i;
	}
	for (int i = 1; i < n - m; i++) {
		length /= i;
	}
	std::cout << "Length: " << length;
	std::vector<int64_t> result(length, 0);
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < importance.size(); j++) {
			//
		}
	}
	return 0;
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