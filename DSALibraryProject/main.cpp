#include "main.h"
#include "Tree.cpp"
#include "Sort.cpp"
#include "List.cpp"


int main() {
	//do sth with the datastructure
	ArrQueue<int> temp;
	int n;
	cout << "HAY NHAP GIA TRI CUA n: " << endl;
	cin >> n;
	temp.reserve(n);
	for (int i = 0; i < n; ++i) {
		int k = rand() % 100;
		cout << "Input " << i << " = " << k << endl;
		temp.push(k);
	}
	cout << "POP" << endl;
	for (int i = 0; i < n; ++i) {
		cout << temp.front() << endl;
		temp.pop();
	}
	return 0;///
}