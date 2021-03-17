#include<iostream>
#include<fstream>
#include<vector>

class DisjointSetUnion {
private:
	std::vector<int64_t> parent_;
	std::vector<int64_t> size_;
	int64_t number_of_components_;
public:
	DisjointSetUnion() { this->number_of_components_ = 0; }

	DisjointSetUnion(const int64_t& number_of_elements) {
		this->number_of_components_ = number_of_elements;
		for (size_t i = 0; i < number_of_components_; i++) {
			parent_.push_back(i);
			size_.push_back(1);
		}
	}

	int64_t GetComponents() { return this->number_of_components_; }

	int64_t FindSet(const int64_t& x) {
		if (x == this->parent_[x]) return x;
		//path compression
		this->parent_[x] = this->FindSet(this->parent_[x]);
		return this->parent_[x];
	}

	void Union(int64_t& x, int64_t& y) {
		x--; //because we count from zero
		y--;
		x = this->FindSet(x);
		y = this->FindSet(y);
		if (x != y) {
			//union by size
			if (this->size_[x] < this->size_[y]) std::swap(x, y); //swap x and y
			//now size[x] >= size[y]
			this->parent_[y] = x;
			this->size_[x] += this->size_[y];
			number_of_components_--;
		}
	}
};

int main() {
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");
	int64_t number_of_cities = 0, number_of_queries = 0;
	input >> number_of_cities >> number_of_queries;
	DisjointSetUnion dsu(number_of_cities);
	while (number_of_queries > 0) {
		number_of_queries--;
		int64_t first = 0, second = 0;
		input >> first >> second;
		dsu.Union(first, second);
		output << dsu.GetComponents() << "\n";
	}
	input.close();
	output.close();
	return 0;
}