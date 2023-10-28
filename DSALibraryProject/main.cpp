#include "main.h"
#include "Tree.cpp"
#include "Sort.cpp"
#include "List.cpp"


int main() {
	//do sth with the datastructure
	LListDequeue<int> temp;
	int n;
	cout << "HAY NHAP GIA TRI CUA n: " << endl;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		temp.push_back(rand() % 100);
	}
	while (!temp.empty()) {
		cout << temp.front() << endl;
		temp.pop_front();
	}
	return 0;
}