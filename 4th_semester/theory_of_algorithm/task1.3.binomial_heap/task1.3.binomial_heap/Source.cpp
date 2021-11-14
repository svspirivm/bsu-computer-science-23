#include<iostream>
#include<fstream>
#include<set>
#include<cmath>

std::set<int64_t> buildTree(const int64_t& number_of_vertex) {
	std::set<int64_t> result;
	int64_t sum = 0;
	int64_t i = 1;
	while (i <= number_of_vertex) {
		if (i & number_of_vertex) {
			result.insert(log2(i));
			sum += i;
		}
		i <<= 1;
	}
	if (sum < number_of_vertex) {
		result.clear();
		result.insert(-1);
	}
	return result;
}

int main() {
	int64_t number_of_vertex = 0;
	std::ifstream input("input.txt");
	input >> number_of_vertex;
	input.close();
	std::set<int64_t> result = buildTree(number_of_vertex);
	std::ofstream output("output.txt");
	for (std::set<int64_t>::iterator it = result.begin(); it != result.end(); it++) {
		output << *it << "\n";
	}
	output.close();
	return 0;
}