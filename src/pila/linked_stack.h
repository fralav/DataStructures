#ifndef PILA_LINKED_STACK_H_
#define PILA_LINKED_STACK_H_

#include <iostream>

template<class T>
class LinkedStack;

template<class T>
class NodePointerStack {
public:
	friend class LinkedStack<T>;

	NodePointerStack() {
		prev = nullptr;
	}
private:
	T value;
	NodePointerStack* prev;
};

template<class T>
class LinkedStack {
public:
	typedef T itemtype;

	LinkedStack();
	LinkedStack(const LinkedStack<T> &);
	~LinkedStack();

	bool isEmpty() const;
	itemtype top() const;
	void pop();
	void push(itemtype);

	void print() const;

private:
	NodePointerStack<T>* head;
};

template<class T>
LinkedStack<T>::LinkedStack() {
	head = nullptr;
}

template<class T>
LinkedStack<T>::LinkedStack(const LinkedStack<T> &s) {
	if (!s.isEmpty()) {
		head = new NodePointerStack<T>();
		head->value = s.head->value;
		NodePointerStack<T>* toCopy = s.head->prev;
		NodePointerStack<T>* whCopy = head;
		while (toCopy != nullptr) {
			NodePointerStack<T>* temp = new NodePointerStack<T>();
			temp->value = toCopy->value;
			whCopy->prev = temp;
			toCopy = toCopy->prev;
			whCopy = whCopy->prev;
		}
	}
}

template<class T>
LinkedStack<T>::~LinkedStack() {
	while (!isEmpty()) {
		pop();
	}
}

template<class T>
bool LinkedStack<T>::isEmpty() const {
	return head == nullptr;
}

template<class T>
typename LinkedStack<T>::itemtype LinkedStack<T>::top() const {
	if (!isEmpty()) {
		return head->value;
	}
	return itemtype();
}

template<class T>
void LinkedStack<T>::pop() {
	if (!isEmpty()) {
		NodePointerStack<T>* temp = head;
		head = head->prev;
		delete temp;
	}
}

template<class T>
void LinkedStack<T>::push(itemtype e) {
	NodePointerStack<T>* temp = new NodePointerStack<T>();
	temp->value = e;
	temp->prev = head;
	head = temp;
}

template<class T>
void LinkedStack<T>::print() const {
	std::cout << "TOP -> [";
	if (!isEmpty()) {
		NodePointerStack<T>* temp = head;
		while (temp->prev != nullptr) {
			std::cout << temp->value << ", ";
			temp = temp->prev;
		}
		std::cout << temp->value;
	}
	std::cout << "]" << std::endl;
}

#endif /* PILA_LINKED_STACK_H_ */
