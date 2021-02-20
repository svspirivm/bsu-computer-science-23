#pragma warning(disable : 4996)
#pragma comment(linker, "/STACK:167772160")

#include<iostream>
#include<vector>
#include<functional>
#include<fstream>
#include<algorithm>
#include<utility>

struct Node {
	int64_t value = 0;
	int64_t height = 0;
	int64_t num_of_leaves = 0;
	int64_t msl = 0;
	int64_t b = 0;
	int64_t a = 0;
	int64_t c = 1;
	bool is_root = false;
	bool is_MSL = false;
	Node* left = nullptr;
	Node* right = nullptr;
	bool isLeaf() {
		return this->left == nullptr && this->right == nullptr;
	}
};

int64_t MAX_PATH = 0;
int64_t MAX_HEIGHT = 0;

class BinarySearchTree {

private:
	Node* root;

public:
	BinarySearchTree() {
		this->root = nullptr;
	}

	BinarySearchTree(const std::vector<int64_t>& vertices) {
		this->root = nullptr;
		for (const auto& element : vertices) {
			addElement(element);
		}
	}

	void addElement(const int64_t& element) {
		if (this->root == nullptr) {
			this->root = new Node();
			this->root->value = element;
			return;
		}

		Node* node = new Node();
		node = this->root;
		while (true) {
			if (node->value > element) {
				if (node->left == nullptr) {
					node->left = new Node();
					node->left->value = element;
					return;
				}
				node = node->left;
			}
			else if (node->value < element) {
				if (node->right == nullptr) {
					node->right = new Node();
					node->right->value = element;
					return;
				}
				node = node->right;
			}
			else break;
		}
	}

	bool contains(const int64_t& element) {
		Node* node = this->root;
		while (true) {
			if (node == nullptr) return false;
			if (node->value > element) {
				node = node->left;
			}
			else if (node->value < element) {
				node = node->right;
			}
			else return true;
		}
	}

	Node* minimum(Node* x) {
		if (x->left == nullptr) return x;
		return minimum(x->left);
	}

	Node* deleteElementRight(const int64_t& element) {
		if (this->root == nullptr) return nullptr;

		if (element < this->root->value) {
			this->root->left = getLeftSubtree()->deleteElementRight(element);
		}
		else if (element > this->root->value) {
			this->root->right = getRightSubtree()->deleteElementRight(element);
		}
		else if (this->root->left != nullptr && this->root->right != nullptr) {
			this->root->value = minimum(this->root->right)->value;
			this->root->right = getRightSubtree()->deleteElementRight(this->root->value);
		}
		else {
			if (this->root->left != nullptr) this->root = root->left;
			else if (this->root->right != nullptr) this->root = this->root->right;
			else this->root = nullptr;
		}
		return this->root;
	}

	/*void infixTraverse(std::function<void(const int64_t&)> func) {
		if (this->root == nullptr) return;
		getLeftSubtree()->infixTraverse(func);
		func(this->root->value);
		getRightSubtree()->infixTraverse(func);
	}*/

	void prefixTraverse(std::function<void(Node*)> func) {		//прямой левый
		if (this->root == nullptr) return;
		func(this->root);
		getLeftSubtree()->prefixTraverse(func);
		getRightSubtree()->prefixTraverse(func);
	}

	//void postfixTraverse(std::function<void(Node*)> func) {	//обратный левый обход
	//	if (this->root == nullptr) return;
	//	getLeftSubtree()->postfixTraverse(func);
	//	getRightSubtree()->postfixTraverse(func);
	//	func(this->root);
	//}

	BinarySearchTree* getLeftSubtree() {
		BinarySearchTree* result = new BinarySearchTree();
		if (!(this->root == nullptr)) result->root = this->root->left;
		return result;
	}

	BinarySearchTree* getRightSubtree() {
		BinarySearchTree* result = new BinarySearchTree();
		if (!(this->root == nullptr)) result->root = this->root->right;
		return result;
	}

	void getHeightAndLeaves() {
		if (!(this->root == nullptr)) {
			getLeftSubtree()->getHeightAndLeaves();
			getRightSubtree()->getHeightAndLeaves();
			if (this->root->isLeaf()) {
				this->root->height = 0;
				this->root->msl = 0;
				this->root->num_of_leaves = 1;
			}
			else if (this->root->left != nullptr && this->root->right != nullptr) {
				this->root->height = std::max(this->root->left->height, this->root->right->height) + 1;
				this->root->msl = 2 + this->root->right->height + this->root->left->height;
				if (this->root->left->height == this->root->right->height)
					this->root->num_of_leaves = this->root->left->num_of_leaves + this->root->right->num_of_leaves;
				else if (this->root->left->height > this->root->right->height)
					this->root->num_of_leaves = this->root->left->num_of_leaves;
				else this->root->num_of_leaves = this->root->right->num_of_leaves;
			}
			else if (this->root->left != nullptr) {
				this->root->height = this->root->left->height + 1;
				this->root->num_of_leaves = this->root->left->num_of_leaves;
				this->root->msl = 1 + this->root->left->height;
			}
			else if (this->root->right != nullptr) {
				this->root->height = this->root->right->height + 1;
				this->root->num_of_leaves = this->root->right->num_of_leaves;
				this->root->msl = 1 + this->root->right->height;
			}
		}
	}


	int64_t findMaximumSemipathLength() {
		if (!(this->root == nullptr)) {
			getLeftSubtree()->findMaximumSemipathLength();
			getRightSubtree()->findMaximumSemipathLength();
			if (this->root->msl > MAX_PATH) {
				MAX_PATH = this->root->msl;
			}
		}
		return MAX_PATH;
	}

	void markRoot() {
		if (!(this->root == nullptr)) {
			getLeftSubtree()->markRoot();
			getRightSubtree()->markRoot();
			if (this->root->height > MAX_HEIGHT) {
				MAX_HEIGHT = this->root->height;
			}
		}
		if(this->root != nullptr) this->root->is_root = true;
	}

	void markMSL(const int64_t& max) {
		if (!(this->root == nullptr)) {
			getLeftSubtree()->markMSL(max);
			getRightSubtree()->markMSL(max);
			if (this->root->msl == max) {
				this->root->is_MSL = true;
			}
		}
	}

	void markB() {
		if (!(this->root == nullptr)) {
			getLeftSubtree()->markB();
			getRightSubtree()->markB();
			if (this->root->is_MSL == true && this->root->left != nullptr && this->root->right != nullptr) {
				this->root->b = this->root->right->num_of_leaves * this->root->left->num_of_leaves;
			}
			else if (this->root->is_MSL == true && this->root->left != nullptr) {
				this->root->b = this->root->left->num_of_leaves;
			}
			else if (this->root->is_MSL == true && this->root->right != nullptr) {
				this->root->b = this->root->right->num_of_leaves;
			}
		}
	}

	

	void markA() {
		if (this->root == nullptr) return;
		if (this->root->left != nullptr && this->root->right != nullptr) {
			if (this->root->right->height == this->root->left->height) {
				this->root->right->a = this->root->b + this->root->right->num_of_leaves * (this->root->a / this->root->num_of_leaves);
				this->root->left->a = this->root->b + this->root->left->num_of_leaves * (this->root->a / this->root->num_of_leaves);
			}
			else if (this->root->right->height > this->root->left->height) {
				this->root->right->a = this->root->a + this->root->b;
				this->root->left->a = this->root->b;
			}
			else if (this->root->left->height > this->root->right->height) {
				this->root->left->a = this->root->a + this->root->b;
				this->root->right->a = this->root->b;
			}
		}
		else if (this->root->left != nullptr) this->root->left->a = this->root->a + this->root->b;
		else if (this->root->right != nullptr) this->root->right->a = this->root->a + this->root->b;
		getLeftSubtree()->markA();
		getRightSubtree()->markA();
	}

	void getResult() {
		if (this->root == nullptr) return;
		this->root->c = this->root->a + this->root->b;
		getLeftSubtree()->getResult();
		getRightSubtree()->getResult();
	}
};


std::vector<int64_t> readFromFile(const std::string& filename) {
	std::ifstream input(filename);
	int64_t number;
	std::vector<int64_t> result;
	if (input.is_open()) {
		while (input >> number) {
			result.push_back(number);
		}
	}
	input.close();
	return result;
}


int main() {
	std::vector<int64_t> vertices = readFromFile("input.txt");
	BinarySearchTree tree(vertices);
	tree.deleteElementRight(vertices[0]);

	if (vertices.size() > 2) {
		tree.getHeightAndLeaves();
		int64_t m = tree.findMaximumSemipathLength();
		tree.markMSL(m);
		tree.markRoot();
		tree.markB();
		tree.markA();
		tree.getResult();
	}
	std::ofstream output("output.txt");
	std::function<void(Node*)> writeToFile = [&output](Node* x) { output << x->value << " " << x->c << "\n"; };
	tree.prefixTraverse(writeToFile);
	output.close();
	
	return 0;
}