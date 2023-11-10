#include "main.h"
#include "Tree.h"
#include "Sort.h"
#include "List.h"


int main() {
	AVL<int> tree;
	int v[] = { 7,49,73,58,30,72,44,78,23,9 };
	for (int i = 0; i < 10; ++i) {
		tree.insert(v[i]);
	}
	tree.traverse(
		[](int& a) {//
			cout << setw(5) << a;
		}, AVL<int>::DFS_NLR
	);
	cout << endl;
	tree.remove(30);
	tree.traverse(
		[](int& a) {//
			cout << setw(5) << a;
		}, AVL<int>::DFS_NLR
	);
	cout << endl;
	return 0;///////////
}