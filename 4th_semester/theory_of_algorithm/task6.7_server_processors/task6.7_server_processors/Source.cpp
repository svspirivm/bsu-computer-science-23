#pragma warning(disable : 4996)
#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>

class Program {
public:
	int64_t loading = 0;
	int64_t running = 0;
	int64_t index = 0;
	Program (const int64_t& load, const int64_t& run, const int64_t& index) {
		this->loading = load;
		this->running = run;
		this->index = index;
	}
	bool operator < (const Program& program) {
		if (this->running == program.running) return this->loading < program.loading;
		return this->running < program.running;
	}
};

int64_t load(const std::vector<Program>& progs, const int64_t& from, const int64_t& to) {
	int64_t result = 0;
	for (size_t i = from; i < to - 1; i++) result += progs[i].loading;
	return result;
}

int64_t run(const std::vector<Program>& progs, const int64_t& from, const int64_t& to) {
	int64_t result = 0;
	for (size_t i = from; i < to - 1; i++) result += progs[i].running;
	return result;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* input = freopen("input.txt", "r", stdin);
	FILE* output = freopen("output.txt", "w", stdout);
	int64_t processors = 0, programs = 0;
	fscanf(input, "%lld", &processors);
	fscanf(input, "%lld", &programs);
	std::vector<Program> tasks;
	for (size_t i = 0; i < programs; i++) {
		int64_t load = 0, run = 0;
		fscanf(input, "%lld%lld", &load, &run);
		Program new_program(load, run, i + 1);
		tasks.push_back(new_program);
	}
	fclose(input);
	std::sort(tasks.rbegin(), tasks.rend());

	std::vector<int64_t> time(programs, 0);
	std::vector<int64_t> proc(programs, 0);
	if (programs > processors)
		for (size_t j = 0; j < programs; j++) {
			time[j] = tasks[j].loading + run(tasks, 0, j + 1) + load(tasks, 0, j + 1) / processors;
			proc[j] = j % 3 + 1;
		}
	else 
		for (size_t j = 0; j < programs; j++) {
			time[j] = tasks[j].loading + run(tasks, 0, j + 1);
			proc[j] = j % 3 + 1;
		}
	fprintf(output, "%lld%c", time.back(), '\n');
	for (size_t j = 0; j < tasks.size(); j++) {
		fprintf(output, "%lld%c%lld%c", tasks[j].index, ' ', proc[j], '\n');
	}
	return 0;
}