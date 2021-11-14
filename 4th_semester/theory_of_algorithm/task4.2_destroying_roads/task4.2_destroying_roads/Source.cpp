#pragma warning(disable : 4996)
#include<iostream>
#include<stdio.h>
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
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* input = freopen("input.txt", "r", stdin);
	FILE* output = freopen("output.txt", "w", stdout);
	int64_t number_of_cities = 0, number_of_queries = 0, number_of_earthquakes = 0;
	fscanf(input, "%lld%lld%lld", &number_of_cities, &number_of_queries, &number_of_earthquakes);
	std::vector<std::pair<int64_t, int64_t>> roads_to_build;
	DisjointSetUnion dsu(number_of_cities);
	std::vector<bool> ruined(number_of_queries, false);
	std::vector<int64_t> ruined_index;

	for (size_t k = 0; k < number_of_queries; k++) {
		int64_t first = 0, second = 0;
		fscanf(input, "%lld%lld", &first, &second);
		roads_to_build.push_back(std::make_pair(first, second));
	}

	for (size_t k = 0; k < number_of_earthquakes; k++) {
		int64_t road_to_ruin = 0;
		fscanf(input, "%lld", &road_to_ruin);
		ruined[road_to_ruin - 1] = true;
		ruined_index.push_back(road_to_ruin);
	}
	fclose(input);

	//unions for untouched roads
	for (size_t k = 0; k < roads_to_build.size(); k++) {
		if (!ruined[k]) dsu.Union(roads_to_build[k].first, roads_to_build[k].second);
	}

	//now we need to go backwards to check if our graph become connected in case we "rebuild" ruined road 
	std::vector<int> result(number_of_earthquakes, -1);
	size_t k = number_of_earthquakes - 1;
	while (dsu.GetComponents() > 1) {
		result[k] = 0;
		dsu.Union(roads_to_build[ruined_index[k] - 1].first, roads_to_build[ruined_index[k] - 1].second);
		k--;
	}

	for (size_t k = 0; k < result.size(); k++) fprintf(output, "%i", std::abs(result[k]));

	fclose(output);
	return 0;
}