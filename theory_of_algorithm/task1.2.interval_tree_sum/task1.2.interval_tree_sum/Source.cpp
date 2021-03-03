#pragma comment(linker, "/STACK:167772160")
#include<iostream>
#include<vector>
#include<cmath>
#include<string>

void doBuild(const std::vector<int64_t>& elements, std::vector<int64_t>& tree, 
			 const int64_t &vertex, const int64_t& left, const int64_t& right) {
	if (right - left == 1) tree[vertex] = elements[left];
	else {
		int64_t m = floor((double)((left + right) / 2));
		doBuild(elements, tree, 2 * vertex + 1, left, m);
		doBuild(elements, tree, 2 * vertex + 2, m, right);
		tree[vertex] = tree[2 * vertex + 1] + tree[2 * vertex + 2];
	}
}

std::vector<int64_t> buildTree(const std::vector<int64_t>& elements) {
	std::vector<int64_t> result(elements.size() * 4, 0);
	doBuild(elements, result, 0, 0, elements.size());
	return result;
}

void doAdd(std::vector<int64_t>& tree, const int64_t& vertex, const int64_t& left,
	const int64_t& right, const int64_t& i, const int64_t& x) {
	if (right - left == 1) {
		tree[vertex] += x;
		return;
	}
	int64_t m = floor((double)((left + right) / 2));
	if (i < m) doAdd(tree, 2 * vertex + 1, left, m, i, x);
	else doAdd(tree, 2 * vertex + 2, m, right, i, x);
	tree[vertex] = tree[2 * vertex + 1] + tree[2 * vertex + 2];
}

void add(std::vector<int64_t>& tree, const int64_t& n, const int64_t& i, const int64_t& x) {
	doAdd(tree, 0, 0, n, i, x);
}

int64_t doFindSum(std::vector<int64_t>& tree, const int64_t& vertex, const int64_t& tree_left, 
				  const int64_t& tree_right, const int64_t& interval_left, const int64_t& interval_right) {
	if (interval_left == tree_left && interval_right == tree_right) return tree[vertex];
	int64_t m = floor((double)((tree_left + tree_right) / 2));
	if (interval_right <= m) return doFindSum(tree, 2 * vertex + 1, tree_left, m, interval_left, interval_right);
	if (m <= interval_left) return doFindSum(tree, 2 * vertex + 2, m, tree_right, interval_left, interval_right);
	return (
		doFindSum(tree, 2 * vertex + 1, tree_left, m, interval_left, m) +
		doFindSum(tree, 2 * vertex + 2, m, tree_right, m, interval_right)
		);
}

int main() {
	int64_t number_of_elements = 0;
	std::cin >> number_of_elements;
	std::vector<int64_t> elements;
	int64_t counter = number_of_elements;
	while (counter > 0) {
		counter--;
		int64_t tmp = 0;
		std::cin >> tmp;
		elements.push_back(tmp);
	}

	std::vector<int64_t> interval_tree = buildTree(elements);

	int64_t number_of_queries = 0;
	std::cin >> number_of_queries;
	while (number_of_queries > 0) {
		number_of_queries--;
		std::string query;
		std::cin >> query;
		if (query == "Add") {
			int64_t i = 0, x = 0;
			std::cin >> i >> x;
			add(interval_tree, number_of_elements, i, x);
		}
		else if (query == "FindSum") {
			int64_t left = 0, right = 0;
			std::cin >> left >> right;
			std::cout << doFindSum(interval_tree, 0, 0, number_of_elements, left, right) << "\n";
		}
	}

	return 0;
}