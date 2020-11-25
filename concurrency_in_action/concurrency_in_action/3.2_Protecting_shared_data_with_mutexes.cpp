#include <list>
#include <algorithm>
#include <mutex>
#include <iostream>
#include <vector>

#define NUM_THREADS 2

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value) {
	std::lock_guard<std::mutex>guard(some_mutex);
	some_list.push_back(new_value);

}

bool list_contains(int value_to_find) {
	std::lock_guard<std::mutex>guard(some_mutex);
	return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

void Push2List();
void FindFromList();

int main() {

	std::thread pushThread = std::thread(Push2List);
	pushThread.join();
	std::thread findThread  = std::thread(FindFromList);

	findThread.join();

	return 0;
}

void Push2List() {
	int i = 0;
	for (; i < 1000; i++) {
		add_to_list(i);
	}
}

void FindFromList() {

	if (list_contains(100)) {
		std::cout << "contains!";
	}
	else {
		std::cout << "not contains!!";
	}
}