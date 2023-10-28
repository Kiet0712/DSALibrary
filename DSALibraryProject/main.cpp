#include "main.h"
#include "Tree.cpp"
#include "Sort.cpp"
#include "List.cpp"


int main() {
	//do sth with the datastructure
	List<int>* temp = new D2LListCir<int>;
	for (int i = 0; i < 10; ++i) {
		temp->insert(rand()%10, i);
	}
	temp->traverse(
		[](int& a) {
			cout << a << " ";
		}
	);
	cout << endl;
	int k;
	cout << "HAY NHAP K" << endl;
	cin >> k;
	List<int>* temp1 = temp->split(k);
	temp->traverse(
		[](int& a) {
			cout << a << " ";
		}
	);
	cout << endl;
	temp1->traverse(
		[](int& a) {
			cout << a << " ";
		}
	);
	cout << endl;
	temp1->reverse();
	temp1->concat(temp);
	temp1->traverse(
		[](int& a) {
			cout << a << " ";
		}
	);
	delete temp1;
	delete temp;/////////////////////////////
	return 0;
}