//Для каждого числа - запроса xx в отдельной строке выведите через пробел числа bb, ll и rr, 
//где bb равно 11, если xx присутствует в массиве, и 00 в противном случае, ll — индекс первого элемента, 
//большего либо равного xx, rr — индекс первого элемента, большего xx.

#include<iostream>
#include<vector>
#include <stdio.h>
#include<math.h>

bool contains(const int& element, const std::vector<int>& data) {
	size_t left = 0;
	size_t right = data.size();
	while (left < right) {
		size_t k = floor((left + right) / 2);
		if (element == data[k]) return true;
		else if (element < data[k]) right = k;
		else left = k + 1;
	}
	return false;
}

int lowerBound(const int& element, const std::vector<int>& data) {
	int left = 0;
	int right = data.size();
	while (left < right) {
		int k = floor((left + right) / 2);
		if (element <= data[k]) right = k;
		else left = k + 1;
	}
	return left;
}

int upperBound(const int& element, const std::vector<int>& data) {
	int left = 0;
	int right = data.size();
	while (left < right) {
		int k = floor((left + right) / 2);
		if (element < data[k]) right = k;
		else left = k + 1;
	}
	return left;
}

void processQueries(const std::vector<int>& data, const std::vector<int> queries) {
	for (const int& query : queries) {
		printf("%i%c%i%c%i%c", (int)contains(query, data), ' ', lowerBound(query, data), ' ', upperBound(query, data), '\n');
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int len_of_array = 0;
	std::vector<int> data;
	int num_of_queries = 0;
	std::vector<int> queries;

	scanf_s("%i", &len_of_array);
	while (len_of_array > 0) {
		len_of_array--;
		int tmp = 0;
		scanf_s("%i", &tmp);
		data.push_back(tmp);
	}

	scanf_s("%i", &num_of_queries);
	while (num_of_queries > 0) {
		num_of_queries--;
		int tmp = 0;
		scanf_s("%i", &tmp);
		queries.push_back(tmp);
	}

	processQueries(data, queries);
	//for (int i = 0; i < data.size(); i++) printf("%c%i", ' ', data[i]);
	//printf("%c", '\n');
	//for (int i = 0; i < queries.size(); i++) printf("%c%i", ' ', queries[i]);
	return 0;
}