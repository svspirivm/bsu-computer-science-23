#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

std::vector<int> tmp(101, -1);
std::vector<std::vector<int>> STATES(101, tmp);

bool notVisited(const std::pair<int, int>& position) {
	if (STATES[position.first][position.second] == -1) return true;
	return false;
}

bool inBounds(const std::pair<int, int>& position) {
	if (position.first < STATES.size() && position.first >= 0 && 
		position.second < STATES.size() && position.second >= 0) return true;
	return false;
}

int main() {
	int liters_to_pour = 0, liters_in_first = 0, liters_in_second = 0, tmp = 0, result = 0;
	std::vector<int> scale;
	std::ifstream input("in.txt");
	std::ofstream output("out.txt");
	input >> liters_to_pour;
	input >> liters_in_first >> liters_in_second;
	while (input >> tmp) {
		if (tmp == 0) break;
		scale.push_back(tmp);
	}
	if (scale.empty()) scale.push_back(0);

	if (100 - liters_in_first - liters_in_second == liters_to_pour) output << 0;
	else {
		STATES[liters_in_first][liters_in_second] = 0;
		std::queue<std::pair<int, int>> actions;
		actions.push(std::make_pair(liters_in_first, liters_in_second));

		while (!actions.empty()) {
			std::pair<int, int> current = actions.front();
			actions.pop();
			if (current.first + current.second == 100 - liters_to_pour) {
				result = STATES[current.first][current.second];
				break;
			}
			for (size_t i = 0; i < scale.size(); i++) {
				//everything from 1st to 2nd
				std::pair<int, int> new_position(0, current.first + current.second);
				if (inBounds(new_position) && notVisited(new_position)) {
					actions.push(new_position);
					STATES[new_position.first][new_position.second] = 1 + STATES[current.first][current.second];
				}

				//everything from 2nd to 1st
				new_position = std::make_pair(current.first + current.second, 0);
				if (inBounds(new_position) && notVisited(new_position)) {
					actions.push(new_position);
					STATES[new_position.first][new_position.second] = 1 + STATES[current.first][current.second];
				}

				//everything from 1st to 3rd
				new_position = std::make_pair(0, current.second);
				if (inBounds(new_position) && notVisited(new_position)) {
					actions.push(new_position);
					STATES[new_position.first][new_position.second] = 1 + STATES[current.first][current.second];
				}

				//everything from 2nd to 3rd
				new_position = std::make_pair(current.first, 0);
				if (inBounds(new_position) && notVisited(new_position)) {
					actions.push(new_position);
					STATES[new_position.first][new_position.second] = 1 + STATES[current.first][current.second];
				}
				//part from 1st to 2nd
				new_position = std::make_pair(scale[i], current.first + current.second - scale[i]);
				if (inBounds(new_position) && notVisited(new_position)) {
					actions.push(new_position);
					STATES[new_position.first][new_position.second] = 1 + STATES[current.first][current.second];
				}
				//part from 2nd to 1st
				new_position = std::make_pair(current.first + current.second - scale[i], scale[i]);
				if (inBounds(new_position) && notVisited(new_position)) {
					actions.push(new_position);
					STATES[new_position.first][new_position.second] = 1 + STATES[current.first][current.second];
				}
				//part from 1st to 3rd
				if (current.first > scale[i]) {
					new_position = std::make_pair(scale[i], current.second);
					if (inBounds(new_position) && notVisited(new_position)) {
						actions.push(new_position);
						STATES[new_position.first][new_position.second] = 1 + STATES[current.first][current.second];
					}
				}
				//part from 2nd to 3rd
				if (current.second > scale[i]) {
					new_position = std::make_pair(current.first, scale[i]);
					if (inBounds(new_position) && notVisited(new_position)) {
						actions.push(new_position);
						STATES[new_position.first][new_position.second] = 1 + STATES[current.first][current.second];
					}
				}
				//part from 3rd to 1st
				if (current.first < scale[i] && current.second + scale[i] <= 100) {
					new_position = std::make_pair(scale[i], current.second);
					if (inBounds(new_position) && notVisited(new_position)) {
						actions.push(new_position);
						STATES[new_position.first][new_position.second] = 1 + STATES[current.first][current.second];
					}
				}
				//part from 3rd to 2nd
				if (current.second < scale[i] && current.first + scale[i] <= 100) {
					new_position = std::make_pair(current.first, scale[i]);
					if (inBounds(new_position) && notVisited(new_position)) {
						actions.push(new_position);
						STATES[new_position.first][new_position.second] = 1 + STATES[current.first][current.second];
					}
				}
				//all from 3rd to 1st
				new_position = std::make_pair(100 - current.second, current.second);
				if (inBounds(new_position) && notVisited(new_position)) {
					actions.push(new_position);
					STATES[new_position.first][new_position.second] = 1 + STATES[current.first][current.second];
				}
				//all from 3rd to 2nd
				new_position = std::make_pair(current.first, 100 - current.first);
				if (inBounds(new_position) && notVisited(new_position)) {
					actions.push(new_position);
					STATES[new_position.first][new_position.second] = 1 + STATES[current.first][current.second];
				}
			}
		}
		if (result > 0) output << result;
		else output << "No solution";
	}
	return 0;
}