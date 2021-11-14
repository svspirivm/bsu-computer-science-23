#pragma warning(disable : 4996)
#pragma comment(linker, "/STACK:167772160")

#include<iostream>
#include<fstream>
#include<vector>
#include<stdio.h>
#include<math.h>

std::vector<int> readFromFile(const char* filename) {
	std::vector<int> result;
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* file = freopen(filename, "r", stdin);
	
	long long amount_of_vertex = 0;
	long long key = 0;
	
	fscanf(file, "%lld", &amount_of_vertex);
	
	while (amount_of_vertex > 0) {
		fscanf(file, "%lld", &key);
		result.push_back(key);
		amount_of_vertex--;
	}
	fclose(file);
	return result;
}

void writeToFile(const char* filename, bool flag) {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* file = freopen(filename, "w", stdout);
	if (flag) fprintf(file, "%s", "Yes");
	else fprintf(file, "%s", "No");
	fclose(file);
}

bool isHeap(const std::vector<int>& heap) {
	for (size_t i = 0; i < (heap.size() - 1) / 2; i++) {
		if (heap[i] > heap[2 * i + 1] || heap[i] > heap[2 * i + 2]) return false;
	}
	if (heap.size() % 2 == 0) {
		if (heap[heap.size() - 1] < heap[floor(heap.size() - 1) / 2]) return false;
	}
	return true;
}


int main() {
	writeToFile("output.txt", isHeap(readFromFile("input.txt")));
}

