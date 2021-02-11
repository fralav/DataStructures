#ifndef ALBERO_BINARIO_BINTREE_POINTER_H_
#define ALBERO_BINARIO_BINTREE_POINTER_H_

#include "bintree.h"

template<class T>
class CellP {
public:
	typedef T itemtype;
	CellP() {
		itemtype value;
		setParent(NULL);
		setLeft(NULL);
		setRight(NULL);
		setValue(NULL);
	}

	void setParent(CellP* p) {
		parent = p;
	}

	void setLeft(CellP* l) {
		left = l;
	}

	void setRight(CellP* r) {
		right = r;
	}

	void setValue(itemtype v) {
		value = v;
	}

	void setNumDescendents(int numD) {
		numDescendents = numD;
	}

	CellP* getParent() {
		return parent;
	}

	CellP* getLeft() {
		return left;
	}

	CellP* getRight() {
		return right;
	}

	itemtype getValue() {
		return value;
	}

	int getNumDescendents() {
		return numDescendents;
	}

	friend std::ostream& operator<<(std::ostream& stream, const CellP<T> &cell) {
		stream << getValue();
		return stream;
	}

private:
	CellP* parent;
	CellP* left;
	CellP* right;
	itemtype value;
	int numDescendents = 0;
};


template<class T>
class BinTreeP: public BinTree<T, CellP<T>*> {
public:
	typedef T itemtype;
	typedef CellP<T>* node;

	BinTreeP();
	BinTreeP(int);
	~BinTreeP();

	void create();

	bool isEmpty() const;
	bool isLeftEmpty(node) const;
	bool isRightEmpty(node) const;

	node root() const;
	node parent(node) const;
	node left(node) const;
	node right(node) const;

	void costr(const BinTreeP<T> &);
	void erase(node);

	itemtype read(node) const;
	void write(node, itemtype);
	int readNumDescendants(node) const;

	void insRoot(node);
	void insLeft(node);
	void insRight(node);

private:
	int nNodes;
	node start;
};

template<class T>
BinTreeP<T>::BinTreeP() {
	create();
}

template<class T>
BinTreeP<T>::BinTreeP(int n) {
	create();
}

template<class T>
BinTreeP<T>::~BinTreeP() {
	if (!isLeftEmpty(start)) {
		erase(left(start));
	}
	if (!isRightEmpty(start)) {
		erase(right(start));
	}
	delete start;
}

template<class T>
void BinTreeP<T>::create() {
	start = NULL;
	nNodes = 0;
}

template<class T>
bool BinTreeP<T>::isEmpty() const {
	return (nNodes == 0);
}

template<class T>
typename BinTreeP<T>::node BinTreeP<T>::root() const {
	return (start);
}

template<class T>
typename BinTreeP<T>::node BinTreeP<T>::parent(node n) const {
	if (n != start) {
		return n->getParent();
	} else {
		return n;
	}
}

template<class T>
typename BinTreeP<T>::node BinTreeP<T>::left(node n) const {
	if (!isLeftEmpty(n)) {
		return n->getLeft();
	} else {
		return n;
	}
}

template<class T>
typename BinTreeP<T>::node BinTreeP<T>::right(node n) const {
	if (!isRightEmpty(n)) {
		return n->getRight();
	} else {
		return n;
	}
}

template<class T>
bool BinTreeP<T>::isLeftEmpty(node n) const {
	if (n != NULL) {
		return n->getLeft() == NULL;
	}
	return false;
}

template<class T>
bool BinTreeP<T>::isRightEmpty(node n) const {
	if (n != NULL) {
		return n->getRight() == NULL;
	}
	return false;
}

template<class T>
void BinTreeP<T>::insRoot(node n) {
	if (start == NULL) {
		start = new CellP<T>;
		start->setLeft(NULL);
		start->setRight(NULL);
		nNodes++;
	}
}

template<class T>
void BinTreeP<T>::insLeft(node n) {
	if (start != NULL) {
		if (n != NULL) {
			if (n->getLeft() == NULL) {
				node q = new CellP<T>;
				n->setLeft(q);
				q->setLeft(NULL);
				q->setParent(n);
				q->setRight(NULL);
				q->setNumDescendents(0);
				nNodes++;
				node p = q;
				while (p != root()) {
					p->setNumDescendents(p->getNumDescendents()+1);
					p = parent(p);
				}
				p->setNumDescendents(p->getNumDescendents()+1);
			}
		}
	}
}

template<class T>
void BinTreeP<T>::insRight(node n) {
	if (start != NULL) {
		if (n != NULL) {
			if (n->getRight() == NULL) {
				node q = new CellP<T>;
				n->setRight(q);
				q->setLeft(NULL);
				q->setParent(n);
				q->setRight(NULL);
				q->setNumDescendents(0);
				nNodes++;
				node p = q;
				while (p != root()) {
					p->setNumDescendents(p->getNumDescendents()+1);
					p = parent(p);
				}
				p->setNumDescendents(p->getNumDescendents()+1);
			}
		}
	}
}

template<class T>
void BinTreeP<T>::erase(node n) {
	if (n != NULL) {
		if (!isLeftEmpty(n)) {
			erase(n->getLeft());
		}
		if (!isRightEmpty(n)) {
			erase(n->getRight());
		}
		if (n != start) {
			node p = parent(n);
			while (p != root()) {
				p->setNumDescendents(p->getNumDescendents() - n->getNumDescendents());
				p = parent(p);
			}
			p->setNumDescendents(p->getNumDescendents() - n->getNumDescendents());
			p = parent(n);
			if (p->getLeft() == n) {
				p->setLeft(NULL);
			} else {
				delete n;
			}
		} else {
			start = NULL;
		}
		nNodes--;
	}
}

template<class T>
typename BinTreeP<T>::itemtype BinTreeP<T>::read(node n) const {
	if (n != NULL) {
		return n->getValue();
	}
}

template<class T>
void BinTreeP<T>::write(node n, itemtype e) {
	if (n != NULL) {
		n->setValue(e);
	}
}

template<class T>
int BinTreeP<T>::readNumDescendants(node n) const {
	if (n != NULL) {
		return n->getNumDescendents();
	}
	return int();
}

template<class T>
void BinTreeP<T>::costr(const BinTreeP<T> &tree) {}



#endif /* ALBERO_BINARIO_BINTREE_POINTER_H_ */
