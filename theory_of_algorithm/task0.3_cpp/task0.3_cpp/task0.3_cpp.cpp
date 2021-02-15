#pragma warning(disable : 4996)
#pragma comment(linker, "/STACK:167772160")

#include<iostream>
#include<fstream>
#include<vector>
#include <stdio.h>

struct Node {
	long long key;
	Node* left = nullptr;
	Node* right = nullptr;
};

class Tree {
public:
	Tree(const char* filename) {
		std::ios_base::sync_with_stdio(false);
		std::cin.tie(nullptr);
		FILE* file = freopen(filename, "r", stdin);

		long long ROOT_VALUE = 0;
		std::vector<long long> VALUES;
		std::vector<long long> WHERE_PARENT;
		std::vector<char> WHAT_CHILD;

		long long amount_of_vertex = 0;
		long long key = 0;
		long long where_parent = 0;
		char what_child;

		fscanf(file, "%lld", &amount_of_vertex);
		fscanf(file, "%lld", &ROOT_VALUE);

		while (amount_of_vertex > 1) {
			fscanf(file, "%lld %lld %c", &key, &where_parent, &what_child);
			VALUES.push_back(key);
			WHERE_PARENT.push_back(where_parent);
			WHAT_CHILD.push_back(what_child);

			amount_of_vertex--;
		}
		fclose(file);

		this->root->key = ROOT_VALUE;
		std::vector<Node*> tree;
		tree.push_back(this->root);
		for (size_t i = 0; i < VALUES.size(); i++) {
			Node* node = new Node();
			node->key = VALUES[i];
			long long parent_index = WHERE_PARENT[i] - 2;
			if (parent_index == -1) {
				if (WHAT_CHILD[i] == 'R') this->root->right = node;
				else this->root->left = node;
				tree.push_back(node);
			}
			else {
				if (WHAT_CHILD[i] == 'R') tree[parent_index + 1]->right = node;
				else tree[parent_index + 1]->left = node;
				tree.push_back(node);
			}
		}
	}

	bool check(Node* vertex, long long min, long long max) {                 // min и max — минимально и максимально допустимые значения в вершинах поддерева.
		if (vertex == nullptr) return true;
		if (vertex->key < min || max < vertex->key) return false;
		return check(vertex->left, min, vertex->key) && check(vertex->right, vertex->key, max);
	}

	bool isBST() {
		return check(this->root, INT64_MIN, INT64_MAX);
	}

private:
	Node* root = new Node();
};





void writeToFile(const char* filename, bool flag) {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* file = freopen(filename, "w", stdout);
	if (flag) fprintf(file, "%s", "YES");
	else fprintf(file, "%s", "NO");
	fclose(file);
}


int main() {
	Tree tree("bst.in");
	writeToFile("bst.out", tree.isBST());
}

