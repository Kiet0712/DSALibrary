#include "main.h"
#include "Tree.cpp"
#include "Sort.cpp"
#include "List.cpp"


int main() {
	//do sth with the datastructure
	List<int>* temp = new D2LListWOTail<int>;
	for (int i = 0; i < 10; ++i) temp->insert(rand() % 100, i);
	temp->traverse(
		[](int& a) {
			cout << setw(4) << a;
		}
	);
	cout << endl;
	temp->reverse();
	temp->traverse(
		[](int& a) {
			cout << setw(4) << a;
		}
	);
	cout << endl;//
	delete temp;
}