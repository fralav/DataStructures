#ifndef PILA_VECTOR_STACK_H_
#define PILA_VECTOR_STACK_H_

#include <iostream>

#define MAX_LENGTH 100

template<class T>
class VectorStack {
public:
	typedef T itemtype;

	VectorStack();
	VectorStack(int);
	VectorStack(const VectorStack<T> &);
	~VectorStack();

	bool isEmpty() const;
	itemtype top() const;
	void pop();
	void push(itemtype);

	void print() const;

private:
	itemtype *stack;
	int maxLength;
	int head;
};

template<class T>
VectorStack<T>::VectorStack() {
	maxLength = MAX_LENGTH;
	stack = new itemtype[maxLength];
	head = 0;
}

template<class T>
VectorStack<T>::VectorStack(int dim) {
	maxLength = dim;
	stack = new itemtype[maxLength];
	head = 0;
}

template<class T>
VectorStack<T>::VectorStack(const VectorStack<T> &s) {
	maxLength = s.maxLength;
	head = s.head;
	stack = new itemtype[maxLength];
	for (int i = 0; i < head; i++) {
		stack[i] = s.stack[i];
	}
}

template<class T>
VectorStack<T>::~VectorStack() {
	delete [] stack;
}

template<class T>
bool VectorStack<T>::isEmpty() const {
	return head == 0;
}

template<class T>
typename VectorStack<T>::itemtype VectorStack<T>::top() const {
	if (!isEmpty()) {
		return stack[head-1];
	}
	return itemtype();
}

template<class T>
void VectorStack<T>::pop() {
	if (!isEmpty()) {
		head--;
	}
}

template<class T>
void VectorStack<T>::push(itemtype e) {
	if (head < maxLength) {
		stack[head] = e;
		head++;
	}
}

template<class T>
void VectorStack<T>::print() const {
	std::cout << "[";
	if (!isEmpty()) {
		int i = 0;
		while (i < head-1) {
			std::cout << stack[i] << ", ";
			i++;
		}
		std::cout << stack[i];
	}
	std::cout << "] <- TOP" << std::endl;
}


#endif /* PILA_VECTOR_STACK_H_ */
