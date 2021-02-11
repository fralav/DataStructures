#ifndef ALBERO_BINARIO_VECTOR_BINTREE_H_
#define ALBERO_BINARIO_VECTOR_BINTREE_H_

#include <cmath>

#include "bintree.h"

template<class T>
class BinTreeVector: public BinTree<T, int> {
public:
	typedef typename BinTree<T, int>::itemtype itemtype;
	typedef typename BinTree<T, int>::node node;

	struct cell {
		itemtype value;
		bool present;
		int numDescendents = 0;
	};
	typedef struct cell Cell;

	BinTreeVector();
	BinTreeVector(int);
	~BinTreeVector();

	void create();

	bool isEmpty() const;
	bool isLeftEmpty(node) const;
	bool isRightEmpty(node) const;

	node root() const;
	node parent(node) const;
	node left(node) const;
	node right(node) const;

	void costr(const BinTreeVector<T> &);
	void erase(node);

	itemtype read(node) const;
	void write(node, itemtype);
	int readNumDescendants(node) const;

	void insRoot(node);
	void insLeft(node);
	void insRight(node);

private:
	int MAXLUNG;
	Cell* space;
	int nNodes;
};

template<class T>
BinTreeVector<T>::BinTreeVector() {
	MAXLUNG = 100;
	space = new Cell[MAXLUNG];
	create();
}

template<class T>
BinTreeVector<T>::BinTreeVector(int nNodes): MAXLUNG(pow(nNodes, 2) -1) {
	space = new Cell[pow(nNodes, 2) - 1];
	create();
}

template<class T>
BinTreeVector<T>::~BinTreeVector() {
	erase(0);
	delete[] space;
}

template<class T>
void BinTreeVector<T>::create() {
	for (int i = 0; i < MAXLUNG; i++) {
		space[i].present = false;
	}
	this->nNodes = 0;
}

template<class T>
bool BinTreeVector<T>::isEmpty() const {
	return (this->nNodes == 0);
}

template<class T>
typename BinTreeVector<T>::node BinTreeVector<T>::root() const {
	return (0);
}

template<class T>
typename BinTreeVector<T>::node BinTreeVector<T>::parent(node n) const {
	if (n != 0) {
		if (n % 2 == 0) {
			return ((n-2)/2);
		} else {
			return ((n-1)/2);
		}
	} else {
		return (n);
	}
}

template<class T>
typename BinTreeVector<T>::node BinTreeVector<T>::left(node n) const {
	if (!isLeftEmpty(n)) {
		return (n * 2 + 1);
	} else {
		return (n);
	}
}

template<class T>
typename BinTreeVector<T>::node BinTreeVector<T>::right(node n) const {
	if (!isRightEmpty(n)) {
		return (n * 2 + 2);
	} else {
		return (n);
	}
}

template<class T>
bool BinTreeVector<T>::isLeftEmpty(node n) const {
	return (!space[n*2+1].present);
}

template<class T>
bool BinTreeVector<T>::isRightEmpty(node n) const {
	return (!space[n*2+2].present);
}

template<class T>
void BinTreeVector<T>::insRoot(node n) {
	if (!space[0].present) {
		this->nNodes++;
		space[0].value = n;
		space[0].present = true;
		space[0].numDescendents = 1;
	}
}

template<class T>
void BinTreeVector<T>::insLeft(node n) {
	if (space[0].present) {
		if (space[n].present) {
			if (!space[n*2+1].present) {
				if (this->nNodes < MAXLUNG) {
					space[n*2+1].present = true;
					space[n*2+1].numDescendents = 0;
					this->nNodes++;
					int p = n*2+1;
					while (p != root()) {
						space[p].numDescendents++;
						p = parent(p);
					}
					space[p].numDescendents++;
				}
			}
		}
	}
}

template<class T>
void BinTreeVector<T>::insRight(node n) {
	if (space[0].present) {
		if (space[n].present) {
			if (!space[n*2+2].present) {
				if (this->nNodes < MAXLUNG) {
					space[n*2+2].present = true;
					space[n*2+2].numDescendents = 0;
					this->nNodes++;
					int p = n*2+2;
					while (p != root()) {
						space[p].numDescendents++;
						p = parent(p);
					}
					space[p].numDescendents++;
				}
			}
		}
	}
}

template<class T>
void BinTreeVector<T>::erase(node n) {
	if (space[n].present) {
		if (!isLeftEmpty(n)) {
			erase(n*2+1);
		}
		if (!isRightEmpty(n)) {
			erase(n*2+2);
		}
		if (n != 0) {
			space[n].present = false;
			node p = parent(n);
			while (p != root()) {
				space[p].numDescendents = space[p].numDescendents - (space[n].numDescendents);
				p = parent(p);
			}
			space[p].numDescendents = space[p].numDescendents - (space[n].numDescendents);
		} else {
			space[0].present = false;
		}
		this->nNodes--;
	}
}

template<class T>
typename BinTreeVector<T>::itemtype BinTreeVector<T>::read(node n) const {
	if (space[n].present) {
		return (space[n].value);
	}
	return itemtype();
}

template<class T>
void BinTreeVector<T>::write(node n, itemtype e) {
	if (space[n].present) {
		space[n].value = e;
	}
}

template<class T>
int BinTreeVector<T>::readNumDescendants(node n) const {
	if (space[n].present) {
		return space[n].numDescendents;
	}
	return int();
}

template<class T>
void BinTreeVector<T>::costr(const BinTreeVector<T> &tree) {

}




#endif /* ALBERO_BINARIO_VECTOR_BINTREE_H_ */
