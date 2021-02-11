#ifndef INSIEME_SET_H_
#define INSIEME_SET_H_

#include <iostream>

#include "cell.h"

template<class T>
class Set {
public:
	typedef T itemtype;
	typedef Cell<T>* position;

	Set();
	Set(const Set<T> &);
	~Set();

	bool isEmpty() const;
	bool isContained(const itemtype &) const;
	void insert(const itemtype &);
	void erase(const itemtype &);

	void print() const;

	Set<T> setUnion(const Set<T> &);
	Set<T> setIntersection(const Set<T> &);
	Set<T> setDifference(const Set<T> &);

	Set<T> primeNumbers(const int);

	Set<T>& operator=(const Set<T> &);
	bool operator==(const Set<T> &) const;

private:
	position set;
};


template<class T>
Set<T>::Set() {
	set = nullptr;
}

template<class T>
Set<T>::Set(const Set<T> &s) {
	this->set = nullptr;
	position p;
	for (p = s.set; p != nullptr; p = p->getNext()) {
		this->insert(p->getElement());
	}
}

template<class T>
Set<T>::~Set() {
	position q;
	while (set != nullptr) {
		q = set;
		set = set->getNext();
		delete q;
	}
}

template<class T>
bool Set<T>::isEmpty() const {
    return set == nullptr;
}

template<class T>
bool Set<T>::isContained(const itemtype &a) const {
	position p = set;
	bool contained = false;
	while ((p != nullptr) && (!contained)) {
		contained = a == p->getElement();
		p = p->getNext();
	}
	return contained;
}

template<class T>
void Set<T>::insert(const itemtype &a) {
	if (!isContained(a)) {
		position p = set;
		set = new Cell<T>;
		set->setElement(a);
		set->setNext(p);
	}
}

template<class T>
void Set<T>::erase(const itemtype &a) {
	if (isContained(a)) {
		position p = set;
		position q = p;
		while ((p != nullptr) && (p->getElement() != a)) {
			q = p;
			p = p->getNext();
		}
		if (p == set) {
			if (p->getNext() == nullptr) {
				set = nullptr;
			} else {
				set = p->getNext();
			}
		} else {
			q->setNext(p->getNext());
		}
		delete q;
	}
}

template<class T>
Set<T>& Set<T>::operator =(const Set<T> &s) {
	if (this != &s) {
		if (!this->isEmpty()) {
			position q;
			while (set != nullptr) {
				q = set;
				set = set->getNext();
				delete q;
			}
			set = nullptr;
		}
		position p;
		for (p = s.set; p != nullptr; p = p->getNext()) {
			this->insert(p->getElement());
		}
	}
	return *this;
}

template<class T>
bool Set<T>::operator ==(const Set<T> &s) const {
	position p;
	for (p = this->set; p != nullptr; p = p->getNext()) {
		if (!s.isContained(p->getElement())) {
			return false;
		}
	}
	for (p = s.set; p != nullptr; p = p->getNext()) {
		if (!iscontained(p->getElement())) {
			return false;
		}
	}
	return true;
}

template<class T>
void Set<T>::print() const {
	position p;
	p = set;
	std::cout << "[";
	while (p != nullptr) {
		if (p != set) {
			std::cout << ", " << p->getElement();
		} else {
			std::cout << p->getElement();
		}
		p = p->getNext();
	}
	std::cout << "]" << std::endl;
}

template<class T>
Set<T> Set<T>::setUnion(const Set<T> &a) {
	Set<T> c;
	position p = set;
	while (p != nullptr) {
		c.insert(p->getElement());
		p = p->getNext();
	}
	p = a.set;
	while (p != nullptr) {
		c.insert(p->getElement());
		p = p->getNext();
	}
	return c;
}

template<class T>
Set<T> Set<T>::setIntersection(const Set<T> &a) {
	Set<T> c;
	position p= set;
	while (p != nullptr) {
		if (a.isContained(p->getElement())) {
			c.insert(p->getElement());
		}
		p = p->getNext();
	}
	return c;
}

template<class T>
Set<T> Set<T>::setDifference(const Set<T> &a) {
	Set<T> c;
	position p = set;
	while (p != nullptr) {
		if (!a.isContained(p->getElement())) {
			c.insert(p->getElement());
		}
		p = p->getNext();
	}
	return c;
}

template<class T>
Set<T> Set<T>::primeNumbers(const int n) {
	Set<T> sieve;
	Set<T> primes;
	for (int i = n; i >= 2; i--) {
		sieve.insert(i);
	}
	position p = sieve.set;
	while (p != nullptr) {
		primes.insert(p->getElement());
		itemtype v = p->getElement();
		itemtype u = p->getElement();
		while (v <= n) {
			sieve.erase(v);
			v = v+u;
		}
		p = sieve.set;
	}
	return primes;
}

#endif /* INSIEME_SET_H_ */
