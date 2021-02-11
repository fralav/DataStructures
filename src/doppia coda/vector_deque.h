#ifndef CODA_VECTOR_DEQUE_H_
#define CODA_VECTOR_DEQUE_H_

#include <iostream>

#define MAX_LENGTH 100

template<class T>
class VectorDeque {
public:
	typedef T itemtype;
	VectorDeque();
	VectorDeque(int);
	VectorDeque(const VectorDeque<T> &);
	~VectorDeque();

	bool isEmpty() const;
	itemtype top() const;
	itemtype bottom() const;
	void popFront();
	void popBack();
	void pushFront(itemtype);
	void pushBack(itemtype);

	void print() const;

private:
	itemtype *deque;
	int head;
	int tail;
	int length;
	int maxLength;
};

template<class T>
VectorDeque<T>::VectorDeque() {
	maxLength = MAX_LENGTH;
	deque = new itemtype[maxLength];
	head = 0;
	tail = 0;
	length = 0;
}

template<class T>
VectorDeque<T>::VectorDeque(int dim) {
	maxLength = dim;
	deque = new itemtype[maxLength];
	head = 0;
	tail = 0;
	length = 0;
}

template<class T>
VectorDeque<T>::VectorDeque(const VectorDeque<T> &d) {
	head = d.head;
	tail = d.tail;
	length = d.length;
	maxLength = d.maxLength;
	deque = new itemtype[maxLength];
	for (int i = head; i <= length; i++) {
		deque[i%maxLength] = d.deque[i%maxLength];
	}
}

template<class T>
VectorDeque<T>::~VectorDeque() {
	delete [] deque;
}

template<class T>
bool VectorDeque<T>::isEmpty() const {
	return length == 0;
}

template<class T>
typename VectorDeque<T>::itemtype VectorDeque<T>::top() const {
	if (!isEmpty()) {
		return deque[head];
	}
	return itemtype();
}

template<class T>
typename VectorDeque<T>::itemtype VectorDeque<T>::bottom() const {
	if (!isEmpty()) {
		return deque[tail];
	}
	return itemtype();
}

template<class T>
void VectorDeque<T>::popFront() {
	if (!isEmpty()) {
		head++;
		head = head % maxLength;
		length--;
	}
}

template<class T>
void VectorDeque<T>::popBack() {
	if (!isEmpty()) {
		tail--;
		tail = tail % maxLength;
		length--;
	}
}

template<class T>
void VectorDeque<T>::pushFront(itemtype e) {
	if (isEmpty()) {
		deque[head] = e;
		length++;
	} else if (length != maxLength) {
		head--;
		if (head < 0) {
			head = head + maxLength;
		}
		deque[head] = e;
		length++;
	}
}

template<class T>
void VectorDeque<T>::pushBack(itemtype e) {
	if (isEmpty()) {
		deque[tail] = e;
		length++;
	} else if (length != maxLength) {
		tail++;
		tail = tail % maxLength;
		deque[tail] = e;
		length++;
	}
}

template<class T>
void VectorDeque<T>::print() const {
	std::cout << "TOP -> [";
	if (!isEmpty()) {
		int i = head;
		int end;
		if (i > tail) {
			end = maxLength + tail;
		} else {
			end = tail;
		}
		while (i < end) {
			std::cout << deque[(i%maxLength)] << ", ";
			i++;
		}
		std::cout << deque[(i%maxLength)];
	}
	std::cout << "] <- BOTTOM" << std::endl;
}


#endif /* CODA_VECTOR_DEQUE_H_ */
