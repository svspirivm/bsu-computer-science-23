#include<iostream>
#include<fstream>
#include<vector>

class Point {
public:
	int  x = 0;
	int y = 0;

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	bool overflow(const int& n, const int& m, const std::vector<std::vector<int>>& field) {
		if ((x <= 0) || (y <= 0) || (x > n) || (y > m) || (field[x][y] == -1)) return false;
			field[x][y] = false;
		return true;
	}
}

int main() {
	int n, m;
	std::vector<std::vector<int>> cant_get;
	std::fstream input("in.txt");
	for (size_t i = 0; i < n; i++) {
		std::vector<int> tmp;
		for (size_t j = 0; j < m; j++) {
			int element = 0;
			input >> element;
			tmp.push_back(element);
		}
		cant_get.push_back(tmp);
	}
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	input >> x1 >> y1 >> x2 >> y2;
	Point begin(x1, y1);
	Point end(x2, y2);

	return 0;
}