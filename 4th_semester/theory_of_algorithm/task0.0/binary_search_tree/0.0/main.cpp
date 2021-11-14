#include<iostream>
#include<set>
#include<fstream>
#include<utility>

std::set<int64_t> readFromFile(const std::string& filename) {
	std::ifstream input(filename);
	int64_t number;
	std::set<int64_t> result;
	if (input.is_open()) {
		while (input >> number) {
			result.insert(number);
		}
	}
	input.close();
	return result;
}

int64_t calculateSum(const std::set<int64_t>& s) {
	int64_t result = 0;
	for (std::set<int64_t>::iterator it = s.begin(); it != s.end(); ++it) result += *it;
	return result;
}

void writeToFile(const std::string& filename, const int64_t& value) {
	std::ofstream output(filename);
	output << value;
	output.close();
}

int main() {
	std::set<int64_t> numbers = readFromFile("input.txt");
	writeToFile("output.txt", calculateSum(numbers));
	//std::cout << calculateSum(numbers);
	return 0;
}