//#include<functional>
//
//template<class T>
//class BinaryTree {
//private:
//	class Node {
//	private:
//		T value = nullptr;
//		Node left = nullptr;
//		Node right = nullptr;
//	public:
//		bool isLeaf() { return left == nullptr && right == nullptr; }
//	};
//
//	Node root;
//
//public:
//	BinaryTree() { }
//
//	BinaryTree(const std::vector<T>& arr) {
//		for (T element : arr) addElement(element);
//	}
//
//	void addElement(const T& element) {
//		if (root == nullptr) {
//			root = new Node();
//			root.value = element;
//			return;
//		}
//		Node node = root;
//		while (true) {
//			if (node.value > element) {
//				if (node.left == nullptr) {
//					node.left = new Node();
//					node.left.value = element;
//					return;
//				}
//				node = node.left;
//			}
//			else if (node.value < element) {
//				if (node.right == nullptr) {
//					node.right = new Node();
//					node.right.value = element;
//					return;
//				}
//				node = node.right;
//			}
//			else break;
//		}
//		//throw new IllegalArgumentException("Binary tree already contains " + element);
//	}
//
//	int infixTraverse(std::function<int(int)>& func) {
//		int result = 0;
//		if (root == nullptr) return;
//		getLeftSubtree().infixTraverse(func);
//		result += func(root.value);
//		getRightSubtree().infixTraverse(func);
//		return result;
//	}
//
//	BinaryTree<T> getLeftSubtree() {
//		if (root == nullptr) return; //throw new IllegalStateException("Binary tree is empty");
//		BinaryTree<T> result = new BinaryTree<T>();
//		result.root = root.left;
//		return result;
//	}
//
//	BinaryTree<T> getRightSubtree() {
//		if (root == nullptr) return; //throw new IllegalStateException("Binary tree is empty");
//		BinaryTree<T> result = new BinaryTree<T>();
//		result.root = root.right;
//		return result;
//	}
//};
