#pragma once
#include "main.h"
#include "List.h"


//BST
template<class T>
class BST {
protected:
	struct Node {
		T data;
		Node* left;
		Node* right;
		Node() : left(nullptr), right(nullptr) {}
		Node(const T& data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) { }
		Node(T&& data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) { }
	};
	Node* root;
	void clear(Node* root) {
		if (root == nullptr) return;
		else {
			clear(root->left);
			clear(root->right);
			delete root;
		}
	}
	void insert(const T& data, Node*& root) {
		if (root == nullptr) root = new Node(data);
		else {
			if (data < root->data) insert(data, root->left);
			else insert(data, root->right);
		}
	}
	T* find(const T& data, Node* root) {
		if (root) return root->data == data ? &root->data : (root->data > data ? find(data, root->left) : find(data, root->right));
		else return nullptr;
	}
	void remove(Node*& root, const T& data) {
		if (root) {
			if (root->data == data) {
				if (root->left && root->right) {
					Node* p = root->right;
					while (p->left) {
						p = p->left;
					}
					root->data = p->data;
					remove(root->right, root->data);
				}
				else if (root->left) {
					Node* temp = root;
					root = root->left;
					delete temp;
				}
				else if (root->right) {
					Node* temp = root;
					root = root->right;
					delete temp;
				}
				else {
					delete root;
					root = nullptr;
				}
			}
			else return root->data > data ? remove(root->left, data) : remove(root->right, data);
		}
	}
public:
	BST() : root(nullptr) { }
	~BST() { this->clear(); }
	void clear() {
		this->clear(this->root);
	}
	enum traverseType { DFS_NLR, DFS_NRL, DFS_LNR, DFS_RNL, DFS_LRN, DFS_RLN, BFS_TV };
	void traverse(function<void(T& data)> op, const traverseType& type) {
		switch (type)
		{
		case DFS_NLR:
			NLR(op, root);
			break;
		case DFS_NRL:
			NRL(op, root);
			break;
		case DFS_LNR:
			LNR(op, root);
			break;
		case DFS_RNL:
			RNL(op, root);
			break;
		case DFS_LRN:
			LRN(op, root);
			break;
		case DFS_RLN:
			RLN(op, root);
			break;
		case BFS_TV:
			BFS(op, root);
			break;
		default:
			break;
		}
	}
	void insert(const T& data) {
		//insert(data, this->root);
		Node** p = &root;
		while (*p) {
			if ((*p)->data > data) p = &((*p)->left);
			else p = &((*p)->right);
		}
		*p = new Node(data);
	}
	void remove(const T& data) {
		remove(this->root, data);
	}
	T* find(const T& data) {
		//return find(data,root);
		Node* p = this->root;
		while (p) {
			if (p->data == data) return &p->data;
			else p = p->data > data ? p->left : p->right;
		}
		return nullptr;
	}
protected:
	static void NLR(function<void(T& data)> op, Node* root) {
		if (root) {
			op(root->data);
			NLR(op, root->left);
			NLR(op, root->right);
		}
	}
	static void NRL(function<void(T& data)> op, Node* root) {
		if (root) {
			op(root->data);
			NLR(op, root->right);
			NLR(op, root->left);
		}
	}
	static void LNR(function<void(T& data)> op, Node* root) {
		if (root) {
			LNR(op,root->left);
			op(root->data);
			LNR(op,root->right);
		}
	}
	static void RNL(function<void(T& data)> op, Node* root) {
		if (root) {
			RNL(op,root->right);
			op(root->data);
			RNL(op,root->left);
		}
	}
	static void LRN(function<void(T& data)> op, Node* root) {
		if (root) {
			LRN(op,root->left);
			LRN(op,root->right);
			op(root->data);
		}
	}
	static void RLN(function<void(T& data)> op, Node* root) {
		if (root) {
			RLN(op,root->right);
			RLN(op,root->left);
			op(root->data);
		}
	}
	static void BFS(function<void(T& data)> op, Node* root) {
		LListQueue<Node*> queue;
		if (root) queue.push(root);
		while (!queue.empty()) {
			Node* front = queue.front();
			queue.pop();
			op(front->data);
			if (front->left) queue.push(front->left);
			if (front->right) queue.push(front->right);
		}
	}
};





//AVL Tree
template<class T>
class AVL {
protected:
	enum BalanceFactor{EH,LH,RH};
	struct Node {
		T data;
		Node* left;
		Node* right;
		BalanceFactor bf;
		Node() : left(nullptr), right(nullptr),bf(EH) {}
		Node(const T& data, Node* left = nullptr, Node* right = nullptr,BalanceFactor bf = EH) : data(data), left(left), right(right),bf(bf) { }
		Node(T&& data, Node* left = nullptr, Node* right = nullptr,BalanceFactor bf = EH) : data(data), left(left), right(right),bf(bf) { }
	};
	Node* root;
	void clear(Node* root) {
		if (root == nullptr) return;
		else {
			clear(root->left);
			clear(root->right);
			delete root;
		}
	}
	void rotR(Node*& root) {
		Node* temp = root->left;
		root->left = temp->right;
		temp->right = root;
		root = temp;
	}
	void rotL(Node*& root) {
		Node* temp = root->right;
		root->right = temp->left;
		temp->left = root;
		root = temp;
	}
	bool balanceLeft(Node*& root) {
		if (root->bf == EH) {
			root->bf = LH;
			return true;
		}
		else if (root->bf == RH) {
			root->bf = EH;
			return false;
		}
		if (root->left->bf == LH) {
			rotR(root);
			root->bf = root->right->bf = EH;
			return false;
		}
		if (root->left->bf == EH) {
			rotR(root);
			root->bf = RH;
			root->right->bf = LH;
			return true;
		}
		rotL(root->left);
		rotR(root);
		if (root->bf == EH) {
			root->left->bf = root->right->bf = EH;
		}
		else if (root->bf == LH) {
			root->right->bf = RH;
			root->bf = root->left->bf = EH;
		}
		else {
			root->left->bf = LH;
			root->right->bf = root->bf = EH;
		}
		return false;

	}
	bool balanceRight(Node*& root) {
		if (root->bf == EH) {
			root->bf = RH;
			return true;
		}
		else if (root->bf == LH) {
			root->bf = EH;
			return false;
		}
		if (root->right->bf == RH) {
			rotL(root);
			root->bf = root->left->bf = EH;
			return false;
		}
		if (root->right->bf == EH) {
			rotL(root);
			root->bf = LH;
			root->left->bf = RH;
			return true;
		}
		rotR(root->right);
		rotL(root);
		if (root->bf == EH) {
			root->right->bf = root->left->bf = EH;
		}
		else if (root->bf == RH) {
			root->left->bf = LH;
			root->bf = root->right->bf = EH;
		}
		else {
			root->right->bf = RH;
			root->left->bf = root->bf = EH;
		}
		return false;
	}
	bool insert(const T& data, Node*& root) {
		if (root == nullptr) {
			root = new Node(data);
			return true;
		}
		else {
			if (root->data == data) return false;
			if (root->data > data) {
				if (insert(data,root->left)) {
					return balanceLeft(root);
				}
				return false;
			}
			else {
				if (insert(data,root->right)) {
					return balanceRight(root);
				}
				return false;
			}
		}
	}
	T* find(const T& data, Node* root) {
		if (root) return root->data == data ? &root->data : (root->data > data ? find(data, root->left) : find(data, root->right));
		else return nullptr;
	}
	bool remove(Node*& root, const T& data) {
		if (root) {
			if (root->data == data) {
				if (!root->left && !root->right) {
					delete root;
					root = nullptr;
					return true;
				}
				else if (root->left && !root->right) {
					Node* temp = root;
					root = root->left;
					delete temp;
					return true;
				}
				else if (!root->left && root->right) {
					Node* temp = root;
					root = root->right;
					delete temp;
					return true;
				}
				else {
					Node* p = root->right;
					while (p->left) {
						p = p->left;
					}
					root->data = p->data;
					if (remove(root->right, root->data)) return !balanceLeft(root);
					return false;
				}
			}
			else if (root->data > data) {
				if (remove( root->left, data)) {
					return !balanceRight(root);
				}
				return false;
			}
			else {
				if (remove( root->right, data)) {
					return !balanceLeft(root);
				}
				return false;
			}
		}
		return false;
	}
public:
	AVL() : root(nullptr) { }
	~AVL() { this->clear(); }
	void clear() {
		this->clear(this->root);
	}
	enum traverseType { DFS_NLR, DFS_NRL, DFS_LNR, DFS_RNL, DFS_LRN, DFS_RLN, BFS_TV };
	void traverse(function<void(T& data)> op, const traverseType& type) {
		switch (type)
		{
		case DFS_NLR:
			NLR(op, root);
			break;
		case DFS_NRL:
			NRL(op, root);
			break;
		case DFS_LNR:
			LNR(op, root);
			break;
		case DFS_RNL:
			RNL(op, root);
			break;
		case DFS_LRN:
			LRN(op, root);
			break;
		case DFS_RLN:
			RLN(op, root);
			break;
		case BFS_TV:
			BFS(op, root);
			break;
		default:
			break;
		}
	}
	void insert(const T& data) {
		bool temp = insert(data, this->root);
	}
	void remove(const T& data) {
		remove(this->root, data);
	}
	T* find(const T& data) {
		return find(data,root);
	}
protected:
	static void NLR(function<void(T& data)> op, Node* root) {
		if (root) {
			op(root->data);
			NLR(op, root->left);
			NLR(op, root->right);
		}
	}
	static void NRL(function<void(T& data)> op, Node* root) {
		if (root) {
			op(root->data);
			NLR(op, root->right);
			NLR(op, root->left);
		}
	}
	static void LNR(function<void(T& data)> op, Node* root) {
		if (root) {
			LNR(op, root->left);
			op(root->data);
			LNR(op, root->right);
		}
	}
	static void RNL(function<void(T& data)> op, Node* root) {
		if (root) {
			RNL(op, root->right);
			op(root->data);
			RNL(op, root->left);
		}
	}
	static void LRN(function<void(T& data)> op, Node* root) {
		if (root) {
			LRN(op, root->left);
			LRN(op, root->right);
			op(root->data);
		}
	}
	static void RLN(function<void(T& data)> op, Node* root) {
		if (root) {
			RLN(op, root->right);
			RLN(op, root->left);
			op(root->data);
		}
	}
	static void BFS(function<void(T& data)> op, Node* root) {
		LListQueue<Node*> queue;
		if (root) queue.push(root);
		while (!queue.empty()) {
			Node* front = queue.front();
			queue.pop();
			op(front->data);
			if (front->left) queue.push(front->left);
			if (front->right) queue.push(front->right);
		}
	}
};





//BTree
