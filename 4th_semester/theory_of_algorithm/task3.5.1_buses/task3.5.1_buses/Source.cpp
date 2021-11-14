#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<iterator>
#include<algorithm>
#include<queue>

struct Stop {
	int64_t route_number;
	int64_t index_in_route;
	int64_t index_of_stop;
	int64_t time;
	std::vector<std::pair<int64_t, int64_t>> route_upto;
};

int main() {
	//read_data
	std::set<int64_t> all_stops;
	std::ifstream input("in.txt");
	int64_t number_routes = 0, number_stops = 0;
	input >> number_stops >> number_routes;
	std::vector<std::pair<int64_t, int64_t>>* routes = new std::vector <std::pair<int64_t, int64_t>>[number_routes];

	int64_t first = 0, second = 0;
	input >> first >> second;
	std::pair<int64_t, int64_t> destination(first, second);
	std::vector<int64_t> number(number_stops, 0);
	std::ofstream output("out.txt");
	//check if our way is already done
	if (first == second) {
		output << 0;
		input.close();
		output.close();
		return 0;
	}
	for (size_t i = 0; i < number_routes; i++) {
		int64_t stops = 0;
		input >> stops;
		for (size_t j = 0; j < stops; j++) {
			int64_t t = 0;
			input >> t;
			std::pair<int64_t, int64_t> p(t, -1); //-1 as indicator "not visited"
			routes[i].push_back(p);
			all_stops.insert(t);
			number[t - 1]++;
		}
	}
	input.close();
	//check if destination exists
	std::set<int64_t>::iterator iter1 = std::find_if(all_stops.begin(), all_stops.end(),
		[&destination](const int64_t& p) -> bool {
			return p == destination.second;
		});
	std::set<int64_t>::iterator iter2 = std::find_if(all_stops.begin(), all_stops.end(),
		[&destination](const int64_t& p) -> bool {
			return p == destination.first;
		});
	if (iter1 == all_stops.end() || iter2 == all_stops.end()) {
		output << "NoWay";
		output.close();
		return 0;
	}
	//create queue with all stops
	std::queue<Stop> stops_queue;
	//load routes in queue
	int64_t flag = number[destination.second - 1];
	for (size_t i = 0; i < number_routes; i++) {
		for (size_t j = 0; j < routes[i].size(); j++) {
			if (routes[i][j].first == destination.second && flag != 0) {
			routes[i][j].second = 0;
			Stop stop;
			stop.index_in_route = j;
			stop.route_number = i;
			stop.index_of_stop = destination.second;
			stop.time = 0;			
			stops_queue.push(stop);
			flag--;
			}
			
		}
	}
	//processing
	int64_t way_length = -1;
	std::vector<Stop> path;
	while (!stops_queue.empty()) {
		Stop current_stop = stops_queue.front();
		stops_queue.pop();
		//check if we got to destination
		if (current_stop.index_of_stop == destination.first && (way_length == -1 || way_length > current_stop.time)) {
			path.push_back(current_stop);
			way_length = current_stop.time;
		}
		// otherwise go to next stop
		else {
			//if this route isn't finished we go to the next stop in this route (in case next stop hasn't already visited
			//or we don't need to get there for transfer)
			if (current_stop.index_in_route != routes[current_stop.route_number].size() - 1 &&
					(routes[current_stop.route_number][current_stop.index_in_route + 1].second == -1 ||
					 routes[current_stop.route_number][current_stop.index_in_route + 1].second >= current_stop.time + 1)) {
				Stop next_stop;
				next_stop.route_number = current_stop.route_number;
				next_stop.index_in_route = current_stop.index_in_route + 1;
				next_stop.index_of_stop = routes[current_stop.route_number][next_stop.index_in_route].first;
				next_stop.time = current_stop.time + 1;
				//add to next stop all the route of previous stop
				for (size_t k = 0; k < current_stop.route_upto.size(); k++) next_stop.route_upto.push_back(current_stop.route_upto[k]);
				//add to next stop current stop
				next_stop.route_upto.push_back(std::make_pair(current_stop.route_number, current_stop.index_in_route));
				//add next stop to queue
				stops_queue.push(next_stop);
				//update time in matrix of all routes
				routes[current_stop.route_number][next_stop.index_in_route].second = next_stop.time;
			}
			//in case we go this route in reversed direction
			if (current_stop.index_in_route != 0 &&
				(routes[current_stop.route_number][current_stop.index_in_route - 1].second == -1 ||
					routes[current_stop.route_number][current_stop.index_in_route - 1].second >= current_stop.time + 1)) {
				Stop next_stop;
				next_stop.route_number = current_stop.route_number;
				next_stop.index_in_route = current_stop.index_in_route - 1;
				next_stop.index_of_stop = routes[current_stop.route_number][next_stop.index_in_route].first;
				next_stop.time = current_stop.time + 1;
				//here we do the same steps as in previous condition
				for (size_t k = 0; k < current_stop.route_upto.size(); k++) next_stop.route_upto.push_back(current_stop.route_upto[k]);
				next_stop.route_upto.push_back(std::make_pair(current_stop.route_number, current_stop.index_in_route));
				stops_queue.push(next_stop);
				routes[current_stop.route_number][next_stop.index_in_route].second = next_stop.time;
			}
			//the last case: we change route
			for (size_t i = 0; i < number_routes; i++) {
				for (size_t j = 0; j < routes[i].size(); j++) {
					if (routes[i][j].first == current_stop.index_of_stop &&
						(routes[i][j].second == -1 || routes[i][j].second >= current_stop.time + 3)) {
						Stop next_stop;
						next_stop.route_number = i;
						next_stop.index_in_route = j;
						next_stop.index_of_stop = current_stop.index_of_stop;
						next_stop.time = current_stop.time + 3;
						for (size_t k = 0; k < current_stop.route_upto.size(); k++) next_stop.route_upto.push_back(current_stop.route_upto[k]);
						next_stop.route_upto.push_back(std::make_pair(current_stop.route_number, current_stop.index_in_route));
						stops_queue.push(next_stop);
						routes[i][j].second = next_stop.time;
					}
				}
			}				
		}
	}

	if (path.empty()) {
		output << "NoWay";
		output.close();
		return 0;
	}

	Stop end;
	for (size_t i = 0; i < path.size(); i++) 
		if (path[i].time == way_length) 
			end = path[i];

	end.route_upto.push_back(std::make_pair(end.route_number, end.index_in_route));
	output << end.time << "\n";

	for (int i = 0; i < end.route_upto.size() - 1; i++) {
		if (end.route_upto[i].first == end.route_upto[i + 1].first &&
			(abs(end.route_upto[i].second - end.route_upto[i + 1].second) == 1)) {
			output << "StopNo " << routes[end.route_upto[i].first][end.route_upto[i].second].first << " ";
			output << "BusNo " << end.route_upto[i].first + 1 << "\n";
		}
	}

	size_t i = end.route_upto.size() - 1;
	output << "StopNo " << routes[end.route_upto[i].first][end.route_upto[i].second].first << " ";
	output << "BusNo " << end.route_upto[i - 1].first + 1;
	output.close();
	delete[] routes;
	return 0;
}