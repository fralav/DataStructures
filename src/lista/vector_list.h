#ifndef LIST_VECTOR_H_
#define LIST_VECTOR_H_

#include "linear_list.h"

#define MAX_DIM 100

template<class T>
class VectorList: public LinearList<T, int> {
public:
	typedef typename LinearList<T, int>::itemtype itemtype;
	typedef typename LinearList<T, int>::position position;

	VectorList();
	VectorList(int);
	VectorList(const VectorList<T> &);
	~VectorList();

	void create();

	bool isEmpty() const;
	itemtype read(position) const;
	position first() const;
	bool isEnd(position) const;
	position next(position) const;
	position prev(position) const;
	void erase(position);

	void write(itemtype, position);
	void insert(itemtype, position);

	int size() const;

private:
	itemtype* list;
	int maxDim;
	int length;
};

template<class T>
VectorList<T>::VectorList() {
	maxDim = MAX_DIM;
	list = new itemtype[maxDim];
	length = 0;
}

template<class T>
void VectorList<T>::create() {
	list = new itemtype[maxDim];
	length = 0;
}

template<class T>
VectorList<T>::VectorList(int dim) {
	maxDim = dim;
	list = new itemtype[maxDim];
	length = 0;
}

template<class T>
VectorList<T>::VectorList(const VectorList<T> &l) {
	this->maxDim = l.maxDim;
	this->list = new itemtype[maxDim];
	this->length = l.length;
	for (int i = 0; i < this->length; i++) {
		this->list[i] = l.list[i];
	}
}

template<class T>
VectorList<T>::~VectorList() {
	delete [] list;

}

template<class T>
bool VectorList<T>::isEmpty() const {
	return size() == 0;
}

template<class T>
typename VectorList<T>::itemtype VectorList<T>::read(position p) const {
	if ((p >= 1) && (p <= size())) {
		return list[p-1];
	}
	return itemtype();
}

template<class T>
typename VectorList<T>::position VectorList<T>::first() const {
	return 1;
}

template<class T>
bool VectorList<T>::isEnd(position p) const {
	return p == size() + 1;
}

template<class T>
typename VectorList<T>::position VectorList<T>::next(position p) const {
	if ((p >= 1) && (p <= size())) {
		return p + 1;
	} else {
		return p;
	}
}

template<class T>
typename VectorList<T>::position VectorList<T>::prev(position p) const {
	if ((p >= 2) && (p <= size() + 1)) {
		return p - 1;
	} else {
		return p;
	}
}

template<class T>
void VectorList<T>::insert(itemtype e, position p) {
	if (size() < maxDim) {
		if ((p >= 1) && (p <= size())) {
			for (int i = size(); i >= p; i--) {
				list[i] = list[i-1];
			}
		}
		length++;
		list[p-1] = e;
	}
}

template<class T>
void VectorList<T>::write(itemtype e, position p) {
	if ((p >= 1) && (p <= size())) {
		list[p-1] = e;
	}
}

template<class T>
void VectorList<T>::erase(position p) {
	if ((p >= 1) && (p <= size())) {
		for (int i = p-1; i < size()-1; i++) {
			list[i] = list[i+1];
		}
		length--;
	}
}

template<class T>
int VectorList<T>::size() const {
	return length;
}

#endif /* LIST_VECTOR_H_ */
