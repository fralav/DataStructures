#ifndef LINEAR_LIST_H_
#define LINEAR_LIST_H_

#include <iostream>

template<class T, class P>
class LinearList {
public:
	typedef T itemtype;
	typedef P position;

	// Algebra fondamentale
	virtual bool isEmpty() const = 0;
	virtual itemtype read(position) const = 0;
	virtual position first() const = 0;
	virtual bool isEnd(position) const = 0;
	virtual position next(position) const = 0;
	virtual position prev(position) const = 0;
	virtual void erase(position) = 0;

	// Funzioni aggiuntive
	void purge();
	position last() const;
	bool search(itemtype) const;
	void print() const;
	int size() const;

protected:
	~LinearList() {};
};

template<class T, class P>
void LinearList<T, P>::purge() {
	typename LinearList<T, P>::position p, q;
	p = first();
	while (!isEnd(p)) {
		q = next(p);
		while (!isEnd(q)) {
			if (read(p) == read(q)) {
				erase(q);
			} else {
				q = next(q);
			}
		}
		p = next(p);
	}
}

template<class T, class P>
typename LinearList<T, P>::position LinearList<T, P>::last() const {
	position p = first();
	while (!isEnd(p)) {
		p = next(p);
	}
	return (p);
}

template<class T, class P>
bool LinearList<T, P>::search(itemtype e) const {
	typename LinearList<T, P>::position p;
	p = first();
	while (!isEnd(p)) {
		if (read(p) == e) {
			return true;
		}
		p = next(p);
	}
	return false;
}

template<class T, class P>
void LinearList<T, P>::print() const {
	typename LinearList<T, P>::position p;
	std::cout << "[";
	p = first();
	while (!isEnd(p)) {
		if (p == first()) {
			std::cout << read(p);
		} else {
			std::cout << ", " << read(p);
		}
		p = next(p);
	}
	std::cout << "]" << std::endl;
}

template<class T, class P>
std::ostream &operator<<(std::ostream &os, const LinearList<T, P> &l) {
	l.print();
	return os;
}

template<class T, class P>
int LinearList<T, P>::size() const {
	int dim = 0;
	LinearList<T, P>::position p;
	p = first();
	while (!isEnd(p)) {
		dim++;
		p = next(p);
	}
	return dim;
}

#endif /* LINEAR_LIST_H_ */
