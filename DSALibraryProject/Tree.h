#pragma once
#include "main.h"
#include "List.h"

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
		insert(data, this->root);
	}
	void remove(const T& data) {

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