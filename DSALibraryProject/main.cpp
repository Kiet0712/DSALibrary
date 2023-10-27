#include "main.h"
#include "Tree.cpp"
#include "Sort.cpp"
#include "List.cpp"


int main() {
	//do sth with the datastructure
	List<int>* temp = new S1LListWTail<int>;
	for (int i = 0; i < 10; ++i) temp->insert(rand() % 100, i);
	temp->traverse(
		[](int& data) {
			cout << setw(5) << data;
		}
	);
	cout << endl;
	List<int>* temp2 = temp->split(4);
	temp->reverse();
	temp->traverse(
		[](int& data) {
			cout << setw(5) << data;
		}
	);
	cout << endl;
	temp2->traverse(
		[](int& data) {
			cout << setw(5) << data;
		}
	);
	cout << endl;
	temp2->concat(temp);
	delete temp;
	delete temp2;
}