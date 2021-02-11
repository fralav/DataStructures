#ifndef CODA_VECTOR_QUEUE_H_
#define CODA_VECTOR_QUEUE_H_

#include <iostream>

#define MAX_LENGTH 100

template<class T>
class VectorQueue {
public:
	typedef T itemtype;

	VectorQueue();
	VectorQueue(int);
	VectorQueue(const VectorQueue<T> &);
	~VectorQueue();

	bool isEmpty() const;
	itemtype top() const;
	void pop();
	void push(itemtype);

	void print() const;

private:
	itemtype *queue;
	int head;
	int length;
	int maxLength;
};

template<class T>
VectorQueue<T>::VectorQueue() {
	maxLength = MAX_LENGTH;
	queue = new itemtype[maxLength];
	head = 0;
	length = 0;
}

template<class T>
VectorQueue<T>::VectorQueue(int dim) {
	maxLength = dim;
	queue = new itemtype[maxLength];
	head = 0;
	length = 0;
}

template<class T>
VectorQueue<T>::VectorQueue(const VectorQueue<T> &q) {
	head = q.head;
	length = q.length;
	maxLength = q.maxLength;
	queue = new itemtype[maxLength];
	for (int i = head; i < length; i++) {
		queue[i] = q.queue[i];
	}
}

template<class T>
VectorQueue<T>::~VectorQueue() {
	delete [] queue;
}

template<class T>
bool VectorQueue<T>::isEmpty() const {
	return length == 0;
}

template<class T>
typename VectorQueue<T>::itemtype VectorQueue<T>::top() const {
	if (!isEmpty()) {
		return queue[head];
	}
	return itemtype();
}

template<class T>
void VectorQueue<T>::pop() {
	if (!isEmpty()) {
		head = (head+1) % maxLength;
		length--;
	}
}

template<class T>
void VectorQueue<T>::push(itemtype e) {
	if (length != maxLength) {
		queue[(head+length) % maxLength] = e;
		length++;
	}
}

template<class T>
void VectorQueue<T>::print() const {
	std::cout << "TOP -> [";
	if (!isEmpty()) {
		int i = head;
		while (i < length-1) {
			std::cout << queue[i] << ", ";
			i++;
		}
		std::cout << queue[i];
	}
	std::cout << "] <- BOTTOM" << std::endl;
}



#endif /* CODA_VECTOR_QUEUE_H_ */
