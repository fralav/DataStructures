#ifndef INSIEME_BOOLEAN_BOOLEAN_ARRAY_SET_H_
#define INSIEME_BOOLEAN_BOOLEAN_ARRAY_SET_H_

#include <iostream>

#define MAX 10;

template<class T>
class BooleanArraySet {
public:
	typedef T itemtype;

	BooleanArraySet();
	BooleanArraySet(int);
	BooleanArraySet(const BooleanArraySet<T> &);
	~BooleanArraySet();

	bool isEmpty() const;
	bool contains(const itemtype) const;
	void insert(const itemtype);
	void remove(const itemtype);

	BooleanArraySet<T> uni(const BooleanArraySet<T> &) const;
	BooleanArraySet<T> inter(const BooleanArraySet<T> &) const;
	BooleanArraySet<T> diff(const BooleanArraySet<T> &) const;

	void print() const;

private:
	bool* set;
	int length;
	void changeDimension(const int);
};

template<class T>
BooleanArraySet<T>::BooleanArraySet() {
	length = MAX;
	set = new bool[length];
	for (int i = 0; i < length; i++) {
		set[i] = false;
	}
}

template<class T>
BooleanArraySet<T>::BooleanArraySet(int dim) {
	length = dim;
	set = new bool[length];
	for (int i = 0; i < length; i++) {
		set[i] = false;
	}
}

template<class T>
BooleanArraySet<T>::BooleanArraySet(const BooleanArraySet<T> &s) {
	length = s.length;
	set = new bool[length];
	for (int i = 0; i < length; i++) {
		set[i] = s.set[i];
	}
}

template<class T>
BooleanArraySet<T>::~BooleanArraySet() {
	delete[] set;
}

template<class T>
bool BooleanArraySet<T>::isEmpty() const {
	for (int i = 0; i < length; i++) {
		if (set[i]) {
			return false;
		}
	}
	return true;
}

template<class T>
bool BooleanArraySet<T>::contains(const itemtype e) const {
	if (e < length) {
		return set[e];
	}
	return false;
}

template<class T>
void BooleanArraySet<T>::insert(const itemtype e) {
	if (e >= length) {
		changeDimension(e + 1);
	}
	set[e] = true;
}

template<class T>
void BooleanArraySet<T>::remove(const itemtype e) {
	if (e < length) {
		set[e] = false;
	}
}

template<class T>
BooleanArraySet<T> BooleanArraySet<T>::uni(const BooleanArraySet<T> &s) const {
	if (length < s.length) {
		return s.uni(*this);
	} else {
		BooleanArraySet<T> setC(length);
		int i = 0;
		while (i < s.length) {
			setC.set[i] = set[i] || s.set[i];
			i++;
		}
		while (i < length) {
			setC.set[i] = set[i];
			i++;
		}
		return setC;
	}
}

template<class T>
BooleanArraySet<T> BooleanArraySet<T>::inter(const BooleanArraySet<T> &s) const {
	int card = (length < s.length) ? length : s.length;
	BooleanArraySet<T> setC(card);
	for (int i = 0; i < card; i++) {
		setC.set[i] = set[i] && s.set[i];
	}
	return setC;
}

template<class T>
BooleanArraySet<T> BooleanArraySet<T>::diff(const BooleanArraySet<T> &s) const {
	BooleanArraySet<T> setC(length);
	for (int i = 0; i < length; i++) {
		setC.set[i] = (s.length >= i) ? (set[i] && !s.set[i]) : set[i];
	}
	return setC;
}

template<class T>
void BooleanArraySet<T>::changeDimension(int dim) {
	if (dim > length) {
		bool* temp = new bool[dim];
		for (int i = 0; i < length; i++) {
			temp[i] = set[i];
		}
		delete[] set;
		set = temp;
		length = dim;
	}
}

template<class T>
void BooleanArraySet<T>::print() const {
	std::cout << "( ";
	for (int i = 0; i < length; i++) {
		bool curr = set[i];
		if (curr) {
			std::cout << i << " ";
		}
	}
	std::cout << ")" << std::endl;
}



#endif /* INSIEME_BOOLEAN_BOOLEAN_ARRAY_SET_H_ */
