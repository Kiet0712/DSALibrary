#include "main.h"
//#include "Tree.h"
#include "Sort.h"
#include "List.h"


int main() {
	//do sth with the datastructure
	S1LListWOTail<int> temp;
	for (int i = 0; i < 100; ++i) temp.insert(i, i);
	for (auto& k : temp) {
		k = k * 2 + 1;
	}
	for (auto& k : temp) {
		cout << setw(5) << k;
	}
	return 0;///////////
}