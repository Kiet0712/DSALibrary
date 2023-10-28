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
		for (int i = 0; i < nE; ++i) {
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
		if (other == nullptr) return;
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
		if (idx == nE) return new S1LListWOTail();
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
		for (int i = 0; i < nE; ++i) {
			op(temp->data);
			temp = temp->next;
		}
	}
	void insert(const T& data, int idx) {
		if (idx < 0 || idx > nE) throw out_of_range("Index out of range");
		else if (idx == nE) {
			if (nE == 0) head = tail = new Node(data);
			else tail = tail->next = new Node(data);
			++nE;
		}
		else {
			Node** temp = &head;
			for (int i = 0; i < idx; ++i) temp = &((*temp)->next);
			*temp = new Node(data, *temp);
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
		if (other == nullptr) return;
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
		if (idx == nE) return new S1LListWTail();
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
		for (int i = 0; i < nE; ++i) {
			op(temp->data);
			temp = temp->next;
		}
	}
	void insert(const T& data, int idx) {
		if (idx < 0 || idx > nE) throw out_of_range("Index out of range");
		else if (idx == nE) {
			if (nE == 0) head = new Node(data);
			else {
				Node** temp = &head;
				for (int i = 0; i < idx-1; ++i) temp = &((*temp)->next);
				(*temp)->next = new Node(data, nullptr, *temp);
			}
			++nE;
		}
		else {
			Node** temp = &head;
			for (int i = 0; i < idx; ++i) temp = &((*temp)->next);
			*temp = new Node(data, *temp, (*temp)->prev);
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
		if (other == nullptr) return;
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
		if (idx == nE) return new D2LListWOTail();
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
protected:
	struct Node {
		T data;
		Node* next;
		Node* prev;
		Node(T&& data, Node* next = nullptr, Node* prev = nullptr) : data(std::move(data)), next(next), prev(prev) {}
		Node(const T& data, Node* next = nullptr, Node* prev = nullptr) : data(data), next(next), prev(prev) {}
	};
	Node* head;
	Node* tail;
	int nE;
public:
	D2LListWTail() : head(nullptr),tail(nullptr),nE(0) {}
	D2LListWTail(Node* head, Node* tail, int nE) : head(head),tail(tail),nE(nE){}
	~D2LListWTail() { this->clear(); }
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
		for (int i = 0; i < nE; ++i) {
			op(temp->data);
			temp = temp->next;
		}
	}
	void insert(const T& data, int idx) {
		if (idx < 0 || idx > nE) throw out_of_range("Index out of range");
		else if (idx == nE) {
			if (nE == 0) head = tail = new Node(data);
			else tail = tail->next = new Node(data);
			++nE;
		}
		else {
			Node** temp = &head;
			for (int i = 0; i < idx; ++i) temp = &((*temp)->next);
			*temp = new Node(data, *temp, (*temp)->prev);
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
			while (idx) {
				--idx;
				temp = &((*temp)->next);
			}
			Node* rmNode = *temp;
			*temp = rmNode->next;
			if (*temp) (*temp)->prev = rmNode->prev;
			delete rmNode;
			--nE;
		}
	}
	void concat(List<T>* other) {
		if (other == nullptr) return;
		Node** temp = &head;
		while (*temp) {
			temp = &((*temp)->next);
		}
		other->traverse(
			[&temp](T& data) {
				if (*temp == nullptr) *temp = new Node(data);
				else {
					(*temp)->next = new Node(data, nullptr, *temp);
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
		if (idx == nE) return new D2LListWTail();
		Node** temp = &head;
		int new_nE = nE - idx;
		nE = idx;
		while (idx) {
			temp = &((*temp)->next);
			--idx;
		}
		Node* newNode = *temp;
		*temp = nullptr;
		List<T>* ans = new D2LListWTail(newNode, tail, new_nE);
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
			curr->prev = next;
			prev = curr;
			curr = next;
		}
		head = prev;
	}
};
template<class T>
class S1LListCir : public List<T> {
protected:
	struct Node {
		T data;
		Node* next;
		Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
		Node(T&& data, Node* next = nullptr) : data(std::move(data)), next(next) {}
	};
	Node* head;
	int nE;
public:
	S1LListCir() : head(nullptr),nE(0) {}
	S1LListCir(Node* head, int nE) : head(head),nE(nE) {}
	~S1LListCir() { this->clear(); }
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
		head = nullptr;
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
		for (int i = 0; i < nE; ++i) {
			op(temp->data);
			temp = temp->next;
		}
	}
	void insert(const T& data, int idx) {
		if (idx < 0 || idx > nE) throw out_of_range("Index out of range");
		else {
			Node** temp = &head;
			for(int i = 0; i < idx; ++i) temp = &((*temp)->next);
			if (idx != nE)*temp = new Node(data, *temp);
			else *temp = new Node(data, head);
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
			if (nE == 0) head = nullptr;
		}
	}
	void concat(List<T>* other) {
		if (other == nullptr) return;
		Node** temp = &head;
		for(int i = 0; i < nE; ++i) temp = &((*temp)->next);
		*temp = nullptr;
		other->traverse(
			[&temp](T& data) {
				if (*temp == nullptr) *temp = new Node(data);
				else {
					(*temp)->next = new Node(data);
					temp = &((*temp)->next);
				}
			}
		);
		*temp = head;
		nE += other->size();
	}
	List<T>* split(int idx) {
		if (idx == nE) return new S1LListCir();
		Node** temp = &head;
		int new_nE = nE - idx;
		nE = idx;
		while (idx) {
			temp = &((*temp)->next);
			--idx;
		}
		Node* newNode = *temp;
		*temp = head;
		Node* end = newNode;
		for (int i = 0; i < new_nE-1; ++i) end = end->next;
		if (end) end->next = newNode;
		return new S1LListCir(newNode, new_nE);
	}
	void reverse() {
		Node** oldhead = &head;
		Node* curr = head, * prev = nullptr, * next = nullptr;
		for (int i = 0; i < nE; ++i) {
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		if (*oldhead) (*oldhead)->next = prev;
		head = prev;
	}
};
template<class T>
class D2LListCir : public List<T> {
protected:
	struct Node {
		T data;
		Node* next;
		Node* prev;
		Node(T&& data, Node* next = nullptr, Node* prev = nullptr) : data(std::move(data)), next(next), prev(prev) {}
		Node(const T& data, Node* next = nullptr, Node* prev = nullptr) : data(data), next(next), prev(prev) {}
	};
	Node* head;
	int nE;
public:
	D2LListCir() : head(nullptr),nE(0) { }
	D2LListCir(Node* head, int nE) : head(head), nE(nE) {}
	~D2LListCir() { this->clear(); }
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
		head = nullptr;
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
		int k = nE;
		for (int i = 0; i < k; ++i) {
			op(temp->data);
			temp = temp->next;
		}
	}
	void insert(const T& data, int idx) {
		if (idx < 0 || idx > nE) throw out_of_range("Index out of range");
		else if (nE == 0) {
			head = new Node(data, nullptr, nullptr);
			head->next = head;
			head->prev = head;
		}
		else if (idx == 0) {
			Node* tail = head->prev;
			head = new Node(data, head, tail);
			tail->next = head;
			head->next->prev = head;
		}
		else {
			Node* temp = head;
			if (idx == nE) {}
			else {
				while (idx) {
					temp = temp->next;
					--idx;
				}
			}
			Node* pre = temp->prev;
			pre->next = temp->prev = new Node(data, temp, pre);
		}
		++nE;
	}
	void remove(int idx) {
		if (idx < 0 || idx >= nE) throw out_of_range("Index out of range");
		else if (nE == 1) {
			head->next = head->prev = nullptr;
			delete head;
			head = nullptr;
		}
		else if (idx == 0) {
			Node* tail = head->prev;
			Node* temp = head;
			head = head->next;
			tail->next = head;
			head->prev = tail;
			temp->next = temp->prev = nullptr;
			delete temp;
		}
		else {
			Node* temp = head;
			if (idx == nE - 1) temp = head->prev;
			else {
				while (idx) {
					temp = temp->next;
					--idx;
				}
			}
			Node* prev = temp->prev;
			Node* next = temp->next;
			temp->prev = temp->next = nullptr;
			delete temp;
			prev->next = next;
			next->prev = prev;
		}
		--nE;
	}
	void concat(List<T>* other) {
		if (other == nullptr) return;
		int k = nE;
		other->traverse(
			[this,&k](int& data) {
				this->insert(data, k);
				++k;
			}
		);
		nE = k;
	}
	List<T>* split(int idx) {
		if (idx == nE) return new D2LListCir();
		Node** temp = &head;
		int new_nE = nE - idx;
		nE = idx;
		while (idx) {
			temp = &((*temp)->next);
			--idx;
		}
		Node* newNode = *temp;
		Node* prev = newNode->prev;
		head->prev = prev;
		prev->next = head;
		Node* end = newNode;
		for (int i = 0; i < new_nE - 1; ++i) end = end->next;
		end->next = newNode;
		newNode->prev = end;
		return new D2LListCir(newNode, new_nE);
	}
	void reverse() {
		Node** oldhead = &head;
		Node* curr = head, * prev = nullptr, * next = nullptr;
		for (int i = 0; i < nE; ++i) {
			next = curr->next;
			curr->next = prev;
			curr->prev = next;
			prev = curr;
			curr = next;
		}
		if (*oldhead) (*oldhead)->next = prev;
		head = prev;
	}
};
#define BLOCK_SIZE 32
template<class T>
class ArrList : public List<T> {
protected:
	T* p;
	int nE;
	int cap;
	void resize(int newnE) {
		if (newnE <= nE) return;
		int newCap = ((newnE + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
		T* pN = new T[newCap];
		for (int i = 0; i < nE; ++i) {
			pN[i] = std::move(p[i]);
		}
		delete[] p;
		p = pN;
		cap = newCap;
	}
public:
	ArrList():p(nullptr),nE(0),cap(0) {}
	ArrList(T*p,int nE,int cap) :p(p),nE(nE),cap(cap) {}
	~ArrList() { this->clear(); }
	void clear() {
		if (!empty()) {
			nE = cap = 0;
			delete[] p;
			p = nullptr;
		}
	}
	int size() { return nE; }
	bool empty() { return !nE; }
	T& operator[](int idx) {
		if (idx < 0 || idx >= nE) throw out_of_range("Index out of range");
		return p[idx];
	}
	void insert(const T& data, int idx) {
		if (idx < 0 || idx > nE) throw out_of_range("Index out of range");
		else {
			if (nE == cap) resize(nE + 1);
			for (int j = nE - 1; j >= idx; --j) p[j + 1] = std::move(p[j]);
			p[idx] = data;
			++nE;
		}
	}
	void remove(int idx) {
		if (idx < 0 || idx >= nE) throw out_of_range("Index out of range");
		else {
			for (int i = idx; i < nE; ++i) p[i] = std::move(p[i + 1]);
			--nE;
		}
	}
	void traverse(function<void(T& data)> op) {
		for (int i = 0; i < nE; ++i) op(p[i]);
	}
	List<T>* split(int idx) {
		if (idx == nE) return new ArrList();
		int newnE = nE - idx;
		T* pN = new T[newnE];
		for (int i = 0; i < newnE; ++i) pN[i] = std::move(p[i + idx]);
		this->nE = idx;
		return new ArrList(pN, newnE, newnE);
	}
	void reverse() {
		int i = 0, j = nE - 1;
		while (i < j) {
			T temp(std::move(p[i]));
			p[i] = std::move(p[j]);
			p[j] = std::move(temp);
			++i;
			--j;
		}
	}
	void concat(List<T>*other) {
		this->resize(nE + other->size());
		int i = 0;
		T** pp = &p;
		int knE = nE;
		other->traverse(
			[&i,&knE,pp](int& data) {
				(*pp)[i + knE] = data;
				++i;
			}
		);
		nE = nE + other->size();
	}
};
template<class T>
class stack {
public:
	virtual void push(const T&) = 0;
	virtual void pop() = 0;
	virtual T top() = 0;
	virtual int size() = 0;
	virtual bool empty() = 0;
};
template<class T>
class queue {
public:
	virtual void push(const T&) = 0;
	virtual void pop() = 0;
	virtual T front() = 0;
	virtual int size() = 0;
	virtual bool empty() = 0;
};
template<class T>
class dequeue {
public:
	virtual void push_back(const T&) = 0;
	virtual void push_front(const T&) = 0;
	virtual void pop_back() = 0;
	virtual void pop_front() = 0;
	virtual T front() = 0;
	virtual T back() = 0;
	virtual int size() = 0;
	virtual bool empty() = 0;
};
template<class T>
class ArrStack : protected ArrList<T>, public stack<T> {
public:
	void push(const T& data) {
		this->insert(data, this->nE);
	}
	void pop() {
		this->remove(this->nE - 1);
	}
	T top() {
		this->operator[](this->nE - 1);
	}
	int size() {
		return this->nE;
	}
	bool empty() {
		return !this->nE;
	}
};
template<class T>
class LListStack : protected S1LListWOTail<T>, public stack<T> {
public:
	void push(const T& data) {
		this->insert(data,0);
	}
	void pop() {
		this->remove(0);
	}
	T top() {
		this->operator[](0);
	}
	int size() {
		return this->nE;
	}
	bool empty() {
		return !this->nE;
	}
};
template<class T>
class ArrQueue : protected ArrList<T>, public queue<T> {

};
template<class T>
class LListQueue : protected S1LListWTail<T>, public queue<T> {
public:
	void push(const T& data) {
		this->insert(data, this->nE);
	}
	void pop() {
		this->remove(0);
	}
	T front() {
		this->operator[](0);
	}
	int size() {
		return this->nE;
	}
	bool empty() {
		return !this->nE;
	}
};
template<class T>
class LListDequeue : protected D2LListCir<T>, public dequeue<T> {
public:
	void push_back(const T& data) {
		this->insert(data, this->nE);
	}
	void push_front(const T& data) {
		this->insert(data, 0);
	}
	void pop_back() {
		this->remove(this->nE - 1);
	}
	void pop_front() {
		this->remove(0);
	}
	T front() {
		return this->operator[](0);
	}
	T back() {
		return this->operator[](this->nE - 1);
	}
	int size() {
		return this->nE;
	}
	bool empty() {
		return !this->nE;
	}
};