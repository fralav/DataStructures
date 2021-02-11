#ifndef CODA_LINKED_QUEUE_H_
#define CODA_LINKED_QUEUE_H_

#include <iostream>

template<class T>
class LinkedQueue;

template<class T>
class NodePointerQueue {
	friend class LinkedQueue<T>;

	NodePointerQueue() {
		next = nullptr;
	}

	NodePointerQueue(const NodePointerQueue<T> &n) {
		value = n.value;
		next = nullptr;
	}

private:
	NodePointerQueue* next;
	T value;
};

template<class T>
class LinkedQueue {
public:
	typedef T itemtype;

	LinkedQueue();
	LinkedQueue(const LinkedQueue<T> &);
	~LinkedQueue();

	bool isEmpty() const;
	int size() const;
	void push(itemtype);
	void pop();
	itemtype top() const;

	void print() const;

private:
	NodePointerQueue<T>* head;
	NodePointerQueue<T>* tail;
	int s;
};

template<class T>
LinkedQueue<T>::LinkedQueue() {
	head = nullptr;
	tail = nullptr;
	s = 0;
}

template<class T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T> &q) {
	head = nullptr;
	tail = nullptr;
	s = 0;
	NodePointerQueue<T>* temp = q.head;
	while (temp != nullptr) {
		push(temp->value);
		temp = temp->next;
	}
}

template<class T>
LinkedQueue<T>::~LinkedQueue() {
	while (!isEmpty()) {
		pop();
	}
}

template<class T>
bool LinkedQueue<T>::isEmpty() const {
	return head == nullptr;
}

template<class T>
int LinkedQueue<T>::size() const {
	return s;
}

template<class T>
void LinkedQueue<T>::push(itemtype e) {
	NodePointerQueue<T>* temp = new NodePointerQueue<T>;
	if (isEmpty()) {
		head = temp;
		tail = temp;
	} else {
		tail->next = temp;
	}
	temp->next = nullptr;
	temp->value = e;
	tail = temp;
	s++;
}

template<class T>
void LinkedQueue<T>::pop() {
	NodePointerQueue<T>* temp = head;
	head = head->next;
	delete temp;
	s--;
}

template<class T>
typename LinkedQueue<T>::itemtype LinkedQueue<T>::top() const {
	return head->value;
}

template<class T>
void LinkedQueue<T>::print() const {
	NodePointerQueue<T>* temp = head;
	int i = 0;
	std::cout << "TOP -> [";
	while (temp != nullptr) {
		if (i == 0) {
			std::cout << temp->value;
		} else {
			std::cout << ", " << temp->value;
		}
		temp = temp->next;
		i++;
	}
	std::cout << "] <- BOTTOM" << std::endl;
}



#endif /* CODA_LINKED_QUEUE_H_ */
