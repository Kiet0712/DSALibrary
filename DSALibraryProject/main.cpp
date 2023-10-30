#include "main.h"
//#include "Tree.h"
#include "Sort.h"
#include "List.h"


int main() {
	//do sth with the datastructure
	S1LListCir<int> temp;
	for (int i = 0; i < 20; ++i) temp.insert(i, i);
	/*for (auto start = temp.begin(), end = temp.end(); start != end; --end) {
		cout << setw(5) << *end;
	}*/
	for (auto k : temp) cout << setw(5) << k;
	return 0;///////////
}