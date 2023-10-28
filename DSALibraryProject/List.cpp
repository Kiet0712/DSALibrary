#include "main.h"

template<class T>
class List {
public:
	virtual int size() = 0;
	virtual bool empty() = 0;
	virtual void insert(const T&, int) = 0;
	virtual void remove(int) = 0;
	virtual T& operator[](int) = 0;
	virtual void traverse(function<void(T&)>) = 0;
	virtual void clear() = 0;
	virtual void concat(List<T>*) = 0;
	virtual void reverse() = 0;
	virtual List<T>* split(int) = 0;
};
template<class T>
class S1LListWOTail : public List<T> {
protected:
	struct Node {
		T data;
		Node* next;
		Node(const T&data, Node* next = nullptr) : data(data),next(next) {}
		Node(T&&data, Node*next = nullptr) : data(std::move(data)), next(next) {}
	};
	Node* head;
	int nE;
public:
	S1LListWOTail(Node* head, int nE) : head(head),nE(nE) {}
	S1LListWOTail(): head(nullptr),nE(0) {}
	~S1LListWOTail() { this->clear(); }
	int size() {
		return nE;
	}
	bool empty() {
		return !nE;
	}
	void clear() {
		while (nE) {
			Node* temp = head;
			head = head->next;
			delete temp;
			--nE;
		}
	}
	T& operator[](int idx) {
		if (idx < 0 || idx >= nE) throw out_of_range("Index out of range");
		else {
			Node* temp = head;
			while (idx) {
				temp = temp->next;
				--idx;
			}
			return temp->data;
		}
	}
	void traverse(function<void(T& data)> op) {
		Node* temp = head;
		while (temp) {
			op(temp->data);
			temp = temp->next;
		}
	}
	void insert(const T& data, int idx) {
		if(idx < 0 || idx > nE) throw out_of_range("Index out of range");
		else {
			Node** temp = &head;
			while (idx) {
				--idx;
				temp = &((*temp)->next);
			}
			*temp = new Node(data, *temp);
			++nE;
		}
	}
	void remove(int idx) {
		if (idx < 0 || idx >= nE) throw out_of_range("Index out of range");
		else {
			Node** temp = &head;
			while (idx) {
				--idx;
				temp = &((*temp)->next);
			}
			Node* rmNode = *temp;
			*temp = rmNode->next;
			delete rmNode;
			--nE;
		}
	}
	void concat(List<T>* other) {
		Node** temp = &head;
		while (*temp) {
			temp = &((*temp)->next);
		}
		other->traverse(
			[&temp](T& data) {
				if (*temp==nullptr) *temp = new Node(data);
				else {
					(*temp)->next = new Node(data);
					temp = &((*temp)->next);
				}
			}
		);
		nE += other->size();
	}
	List<T>* split(int idx) {
		Node** temp = &head;
		int new_nE = nE - idx;
		nE = idx;
		while (idx) {
			temp = &((*temp)->next);
			--idx;
		}
		Node* newNode = *temp;
		*temp = nullptr;
		return new S1LListWOTail(newNode, new_nE);
	}
	void reverse() {
		Node* curr = head, *prev = nullptr, *next = nullptr;
		while (curr) {
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		head = prev;
	}
};
template<class T>
class S1LListWTail : public List<T> {
protected:
	struct Node {
		T data;
		Node* next;
		Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
		Node(T&& data, Node* next = nullptr) : data(std::move(data)), next(next) {}
	};
	Node* head;
	Node* tail;
	int nE;
public:
	S1LListWTail(Node* head, Node* tail, int nE):head(head),tail(tail),nE(nE) {}
	S1LListWTail() : head(nullptr),tail(nullptr),nE(0) {}
	~S1LListWTail() { this->clear(); }
	int size() { return nE; }
	bool empty() { return !nE; }
	void clear() {
		tail = nullptr;
		while (nE) {
			Node* temp = head;
			head = head->next;
			delete temp;
			--nE;
		}
	}
	T& operator[](int idx) {
		if (idx < 0 || idx >= nE) throw out_of_range("Index out of range");
		else {
			Node* temp = head;
			while (idx) {
				temp = temp->next;
				--idx;
			}
			return temp->data;
		}
	}
	void traverse(function<void(T& data)> op) {
		Node* temp = head;
		while (temp) {
			op(temp->data);
			temp = temp->next;
		}
	}
	void insert(const T& data, int idx) {
		if (idx < 0 || idx > nE) throw out_of_range("Index out of range");
		else {
			Node** temp = &head;
			for (int i = 0; i < idx; ++i) temp = &((*temp)->next);
			if(idx==nE) tail = *temp = new Node(data, *temp);
			else *temp = new Node(data, *temp);
			++nE;
		}
	}
	void remove(int idx) {
		if (idx < 0 || idx >= nE) throw out_of_range("Index out of range");
		else if (idx == nE - 1) {
			if (nE == 1) {
				nE = 0;
				delete head;
				head = tail = nullptr;
			}
			else {
				Node* temp = head;
				while (temp->next != tail) {
					temp = temp->next;
				}
				temp->next = nullptr;
				delete tail;
				--nE;
				tail = temp;
			}
		}
		else {
			Node** temp = &head;
			for (int i = 0; i < idx; ++i) temp = &((*temp)->next);
			Node* rmNode = *temp;
			*temp = rmNode->next;
			delete rmNode;
			--nE;
		}
	}
	void concat(List<T>* other) {
		if (other->size() == 0) return;
		Node** temp = &(tail->next);
		other->traverse(
			[&temp](T& data) {
				if (*temp == nullptr) *temp = new Node(data);
				else {
					(*temp)->next = new Node(data);
					temp = &((*temp)->next);
				}
			}
		);
		Node* check = head;
		while (check->next != nullptr) check = check->next;
		tail = check;
		nE += other->size();
	}
	List<T>* split(int idx) {
		Node** temp = &head;
		int new_nE = nE - idx;
		nE = idx;
		while (idx) {
			temp = &((*temp)->next);
			--idx;
		}
		Node* newNode = *temp;
		*temp = nullptr;
		List<T>* ans = new S1LListWTail(newNode, tail, new_nE);
		newNode = head;
		if (newNode == nullptr) tail = nullptr;
		else {
			while (newNode->next != nullptr) newNode = newNode->next;
			tail = newNode;
		}
		return ans;
	}
	void reverse() {
		tail = head;
		Node* curr = head, * prev = nullptr, * next = nullptr;
		while (curr) {
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		head = prev;
	}
};
template<class T>
class D2LListWOTail: public List<T> {
protected:
	struct Node {
		T data;
		Node* next;
		Node* prev;
		Node(T && data, Node* next = nullptr, Node* prev = nullptr) : data(std::move(data)),next(next),prev(prev) {}
		Node(const T& data, Node* next = nullptr, Node* prev = nullptr) : data(data), next(next), prev(prev) {}
	};
	Node* head;
	int nE;
public:
	D2LListWOTail(Node* head,int nE): head(head),nE(nE) {}
	D2LListWOTail() : head(nullptr),nE(0) {}
	~D2LListWOTail() { this->clear(); }
	int size() { return nE; }
	bool empty() { return !nE;}
	void clear() {
		while (nE) {
			Node* temp = head;
			head = head->next;
			delete temp;
			--nE;
		}
	}
	T& operator[](int idx) {
		if (idx < 0 || idx >= nE) throw out_of_range("Index out of range");
		else {
			Node* temp = head;
			while (idx) {
				temp = temp->next;
				--idx;
			}
			return temp->data;
		}
	}
	void traverse(function<void(T& data)> op) {
		Node* temp = head;
		while (temp) {
			op(temp->data);
			temp = temp->next;
		}
	}
	void insert(const T& data, int idx) {
		if (idx < 0 || idx > nE) throw out_of_range("Index out of range");
		else {
			Node** temp = &head;
			for (int i = 0; i < idx; ++i) temp = &((*temp)->next);
			if (*temp == nullptr) *temp = new Node(data);
			else *temp = new Node(data, *temp,(*temp)->prev);
			++nE;
		}
	}
	void remove(int idx) {
		if (idx < 0 || idx >= nE) throw out_of_range("Index out of range");
		else {
			Node** temp = &head;
			while (idx) {
				--idx;
				temp = &((*temp)->next);
			}
			Node* rmNode = *temp;
			*temp = rmNode->next;
			if(*temp) (*temp)->prev = rmNode->prev;
			delete rmNode;
			--nE;
		}
	}
	void concat(List<T>* other) {
		Node** temp = &head;
		while (*temp) {
			temp = &((*temp)->next);
		}
		other->traverse(
			[&temp](T& data) {
				if (*temp == nullptr) *temp = new Node(data);
				else {
					(*temp)->next = new Node(data,nullptr,*temp);
					temp = &((*temp)->next);
				}
			}
		);
		nE += other->size();
	}
	List<T>* split(int idx) {
		Node** temp = &head;
		int new_nE = nE - idx;
		nE = idx;
		while (idx) {
			temp = &((*temp)->next);
			--idx;
		}
		Node* newNode = *temp;
		*temp = nullptr;
		return new D2LListWOTail(newNode, new_nE);
	}
	void reverse() {
		Node* curr = head, * prev = nullptr, * next = nullptr;
		while (curr) {
			next = curr->next;
			curr->next = prev;
			curr->prev = next;
			prev = curr;
			curr = next;
		}
		head = prev;
	}
};
template<class T>
class D2LListWTail : public List<T> {

};
template<class T>
class S1LListCir : public List<T> {

};
template<class T>
class D2LListCir : public List<T> {

};
template<class T>
class ArrList : public List<T> {

};
