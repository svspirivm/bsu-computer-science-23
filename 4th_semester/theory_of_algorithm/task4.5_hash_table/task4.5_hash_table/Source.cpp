#pragma warning(disable : 4996)
#include<iostream>
#include<stdio.h>
#include<vector>

class HashTable {
private:
	std::vector<int64_t> table;
	std::int64_t constant;
	std::int64_t size_of_table;

	int64_t Hash(const int64_t& item, const size_t& number_of_try) {
		return ((item % size_of_table) + constant * number_of_try) % size_of_table;
	}
public:
	HashTable(const int64_t& size, const int64_t& constant) {
		this->size_of_table = size;
		this->constant = constant;
		std::vector<int64_t> new_table(this->size_of_table, -1);
		this->table = new_table;
	}
	void AddItem(const int64_t& item) {
		size_t attempt = 0;
		while (true) {
			int64_t hash = Hash(item, attempt);
			if (table[hash] == -1) {
				table[hash] = item;
				break;
			}
			else if (table[hash] == item) break;
			attempt++;
		}
	}

	std::vector<int64_t> GetTable() { return this->table; }
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	FILE* input = freopen("input.txt", "r", stdin);
	FILE* output = freopen("output.txt", "w", stdout);
	int64_t size_of_table = 0, constant = 0, number_of_keys = 0;
	fscanf(input, "%lld%lld%lld", &size_of_table, &constant, &number_of_keys);

	HashTable hash_table(size_of_table, constant);
	for (size_t i = 0; i < number_of_keys; i++) {
		int64_t key = 0;
		fscanf(input, "%lld", &key);
		hash_table.AddItem(key);
	}
	fclose(input);
	
	std::vector<int64_t> result = hash_table.GetTable();
	for(const auto& item : result) fprintf(output, "%lld%c", item, ' ');
	fclose(output);
	return 0;
}

