#include "main.h"
#include "Tree.h"
#include "Sort.h"
#include "List.h"


int main() {
	//do sth with the datastructure
	int p[] = {0,9,29,14,2,4,7,8,9,10};
	BST<int> temp;
	for (int i = 0; i < 10; ++i) temp.insert(p[i]);
	temp.traverse(
		[](int& data) {
			cout << setw(5) << data;
		}, BST<int>::BFS_TV
	);
	return 0;///
}