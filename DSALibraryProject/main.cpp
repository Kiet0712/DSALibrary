#include "main.h"
//#include "Tree.h"
#include "Sort.h"
#include "List.h"


int main() {
	ArrList<int> temp;
	for (int i = 0; i < 20; ++i) temp.insert(i, i);
	//for (auto k : temp) cout << setw(5) << k;
	for (auto start = temp.begin(), end = temp.end(); start != end; ++start) {
		cout << setw(5) << *start;
	}
	return 0;///////////
}