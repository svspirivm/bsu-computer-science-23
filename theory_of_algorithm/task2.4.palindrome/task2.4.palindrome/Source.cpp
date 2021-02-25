//#pragma warning(disable : 4996)
//#define MAXCHAR 7001
#include<iostream>
#include<stdio.h>
#include<vector>
#include<fstream>
#include<cmath>
#include<string>
#include<algorithm>

std::string Palindrome(const std::string& str) {
	std::string max_palindrome;
	std::vector<int> tmp(str.size(), 0);
	std::vector<std::vector<int>> matrix(str.size(), tmp);
	if (str.size() == 1) return str;
	if (str.size() == 2) {
		if (str[0] != str[1]) return std::string(1, str[0]);
		else return str;
	}

	for (size_t i = 0; i < matrix.size() - 1; i++) {
		matrix[i][i] = 1;
		if (str[i] == str[i + 1]) matrix[i][i + 1] = 2;
		else matrix[i][i + 1] = 1;
	}
	matrix[matrix.size() - 1][matrix.size() - 1] = 1;

	for (int i = 1; i < matrix.size(); i++) {                                  //columns
		for (int j = i - 1; j >= 0; j--) {										  //rows
			if (str[i] == str[j]) matrix[j][i] = 2 + matrix[j + 1][i - 1];
			else  matrix[j][i] = std::max(matrix[j + 1][i], matrix[j][i - 1]);
		}
	}

	for (auto item : matrix) {
		for (auto i : item) std::cout << i << " ";
		std::cout << "\n";
	}

	int i = 0;
	int j = matrix.size() - 1;

	if (str.size() == matrix[0][matrix.size() - 1]) return str;
	else if(matrix[0][matrix.size() - 1] == 1) return std::string(1, str[0]);

	while (j >= i) {
		if (matrix[i][j] > matrix[i + 1][j - 1] && max_palindrome.size() * 2 < matrix[0][matrix.size() - 1] &&
			matrix[i + 1][j - 1] == std::max(matrix[i][j - 1], matrix[i + 1][j])) {
			max_palindrome += str[j];
			i++;
			j--;
		}
		else if (matrix[i][j - 1] == std::max(matrix[i][j - 1], matrix[i + 1][j])) {
			j--;
		}
		else {
			i++;
		}
	}
	std::cout << max_palindrome;
	auto it = max_palindrome.rbegin();
	if (matrix[0][matrix.size() - 1] % 2 == 0) {
		std::string tmp_string (it, max_palindrome.rend());
		max_palindrome = max_palindrome + tmp_string;
	}
	else {
		std::string tmp_string(it + 1, max_palindrome.rend());
		max_palindrome = max_palindrome + tmp_string;
	}
	std::cout << '\n' << max_palindrome;
	return max_palindrome;
}

int main() {
	std::string str;
	std::ifstream input("input.txt");
	input >> str;
	std::ofstream output ("output.txt");
	str = Palindrome(str);
	output << str.size() << "\n" << str;
	return 0;
}