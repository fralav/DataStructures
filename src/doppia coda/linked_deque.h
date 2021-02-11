#ifndef CODA_POINTER_DEQUE_H_
#define CODA_POINTER_DEQUE_H_

#include <iostream>

template<class>
class LinkedDeque;

template<class T>
class NodePointerDeque {
public:
	friend class LinkedDeque<T>;

	NodePointerDeque() {
		next = nullptr;
		prev = nullptr;
		value = T();
	}

private:
	T value;
	NodePointerDeque<T>* next;
	NodePointerDeque<T>* prev;
};

template<class T>
class LinkedDeque {
public:
	typedef T itemtype;

	LinkedDeque();
	LinkedDeque(const LinkedDeque<T> &);
	~LinkedDeque();

	bool isEmpty() const;
	int size() const;
	void pushFront(itemtype);
	void pushBack(itemtype);
	void popFront();
	void popBack();
	itemtype top() const;
	itemtype bottom() const;

	void print() const;

private:
	NodePointerDeque<T>* head;
	NodePointerDeque<T>* tail;
	int s;
};

template<class T>
LinkedDeque<T>::LinkedDeque() {
	head = nullptr;
	tail = nullptr;
	s = 0;
}

template<class T>
LinkedDeque<T>::LinkedDeque(const LinkedDeque<T> &d) {
	head = nullptr;
	tail = nullptr;
	s = 0;
	NodePointerDeque<T>* temp = d.head;
	while (temp != nullptr) {
		pushBack(temp->value);
		temp = temp->next;
	}
}

template<class T>
LinkedDeque<T>::~LinkedDeque() {
	while (!isEmpty()) {
		popFront();
	}
}

template<class T>
bool LinkedDeque<T>::isEmpty() const {
	return head == nullptr;
}

template<class T>
int LinkedDeque<T>::size() const {
	return s;
}

template<class T>
void LinkedDeque<T>::pushFront(itemtype e) {
	NodePointerDeque<T> *temp = new NodePointerDeque<T>;
	temp->value = e;
	if (isEmpty()) {
		head = temp;
		tail = temp;
	} else {
		head->prev = temp;
		temp->next = head;
		head = temp;
	}
	s++;
}

template<class T>
void LinkedDeque<T>::pushBack(itemtype e) {
	NodePointerDeque<T> *temp = new NodePointerDeque<T>;
	temp->value = e;
	if (isEmpty()) {
		head = temp;
		tail = temp;
	} else {
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
	}
	s++;
}

template<class T>
void LinkedDeque<T>::popFront() {
	if (size() == 1) {
		s--;
		delete head;
		head = nullptr;
		tail = nullptr;
	} else if (!isEmpty()) {
		NodePointerDeque<T> *temp = head;
		head->next->prev = nullptr;
		head = head->next;
		delete temp;
		s--;
	}
}

template<class T>
void LinkedDeque<T>::popBack() {
	if (size() == 1) {
		s--;
		delete tail;
		head = nullptr;
		tail = nullptr;
	} else if (!isEmpty()) {
		NodePointerDeque<T> *temp = head;
		tail->prev->next = nullptr;
		tail = tail->prev;
		delete temp;
		s--;
	}
}

template<class T>
typename LinkedDeque<T>::itemtype LinkedDeque<T>::top() const {
	return head->value;
}

template<class T>
typename LinkedDeque<T>::itemtype LinkedDeque<T>::bottom() const {
	return tail->value;
}

template<class T>
void LinkedDeque<T>::print() const {
	std::cout << "[";
	if (!isEmpty()) {
		NodePointerDeque<T>* temp = head;
		while (temp->next != nullptr) {
			std::cout << temp->value << ", ";
			temp = temp->next;
		}
		std::cout << temp->value;
	}
	std::cout << "]" << std::endl;
}


#endif /* CODA_POINTER_DEQUE_H_ */
