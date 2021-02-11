#ifndef ALBERO_BINARIO_BINTREE_H_
#define ALBERO_BINARIO_BINTREE_H_

#include <iostream>

template<class T, class N>
class BinTree {
	static const int NIL = -1;

public:
	typedef T itemtype;
	typedef N node;

	virtual void create() = 0;

	virtual bool isEmpty() const = 0;
	virtual bool isLeftEmpty(node) const = 0;
	virtual bool isRightEmpty(node) const = 0;

	virtual node root() const = 0;
	virtual node parent(node) const = 0;
	virtual node left(node) const = 0;
	virtual node right(node) const = 0;

	virtual void costr(const BinTree<T, N> &) {}
	virtual void erase(node) = 0;

	virtual itemtype read(node) const = 0;
	virtual void write(node, itemtype) = 0;
	virtual int readNumDescendants(node) const = 0;

	virtual void insRoot(node) = 0;
	virtual void insLeft(node) = 0;
	virtual void insRight(node) = 0;

	/////////////////////////////////////////////////////////

	void preVisit(node);
	void inVisit(node);
	void postVisit(node);

	void print() const;
	void printWithDesc() const;
	void copySubTree(const BinTree<T, N> &, node, BinTree<T, N> &, node);
	void mutation(BinTree<T, N> &, node, BinTree<T, N> &, node, BinTree<T, N> &);

protected:
	~BinTree() {}

private:
	void printSubTree(const node) const;
	void printSubTreeWithDesc(const node) const;
};

template<class T, class N>
void BinTree<T, N>::printWithDesc() const {
	if (!isEmpty()) {
		printSubTreeWithDesc(root());
	} else {
		std::cout << "[]" << std::endl;
	}
}

template<class T, class N>
void BinTree<T, N>::printSubTreeWithDesc(const node n) const {
	std::cout << "[" << read(n) << "(" << readNumDescendants(n) << ")" << ", ";
	if (!isLeftEmpty(n)) {
		printSubTreeWithDesc(left(n));
	} else {
		std::cout << "NIL";
	}
	if (!isRightEmpty(n)) {
		printSubTreeWithDesc(right(n));
	} else {
		std::cout << "NIL";
	}
	std::cout << "]";
}

template<class T, class N>
void BinTree<T, N>::print() const {
	if (!isEmpty()) {
		printSubTree(root());
	} else {
		std::cout << "[]" << std::endl;
	}
}

template<class T, class N>
void BinTree<T, N>::printSubTree(const node n) const {
	std::cout << "[" << read(n) << ", ";
	if (!isLeftEmpty(n)) {
		printSubTree(left(n));
	} else {
		std::cout << "NIL";
	}
	if (!isRightEmpty(n)) {
		printSubTree(right(n));
	} else {
		std::cout << "NIL";
	}
	std::cout << "]";
}

template<class T, class N>
std::ostream &operator<<(std::ostream &os, const BinTree<T, N> &t) {
	t.print();
	os << std::endl;
	return os;
}

template<class T, class N>
void BinTree<T, N>::copySubTree(const BinTree<T, N> &t1, node n1, BinTree<T, N> &t2, node n2) {
	t2.write(n2, t1.read(n1));
	if (!t1.isLeftEmpty(n1)) {
		t2.insLeft(n2);
		copySubTree(t1, t1.left(n1), t2, t2.left(n2));
	}
	if (!t1.isRightEmpty(n1)) {
		t2.insRight(n2);
		copySubTree(t1, t1.right(n1), t2, t2.right(n2));
	}
}

template<class T, class N>
void BinTree<T, N>::mutation(BinTree<T, N> &t1, node n1, BinTree<T, N> &t2, node n2, BinTree<T, N> &temp) {
	node p;
	bool leftChild;
	copySubTree(t1, n1, temp, temp.root());
	p = t1.parent(n1);
	leftChild = false;
	if (t1.left(p) == n1) {
		leftChild = true;
	}
	t1.erase(n1);
	if (leftChild) {
		t1.insLeft(p);
		n1 = t1.left(p);
	} else {
		t1.insRight(p);
		n1 = t1.right(p);
	}
	copySubTree(t2, n2, t1, n1);
	p = t2.parent(n2);
	leftChild = false;
	if (t2.left(p) == n2) {
		leftChild = true;
	}
	t2.erase(n2);
	if (leftChild) {
		t2.insLeft(p);
		n2 = t2.left(p);
	} else {
		t2.insRight(p);
		n2 = t2.right(p);
	}
	copySubTree(temp, temp.root(), t2, n2);
}

template<class T, class N>
void BinTree<T, N>::preVisit(node n) {
	if (!isEmpty()) {
		// PRE VISIT
		std::cout << " " << read(n) << " ";
		if (!isLeftEmpty(n)) {
			preVisit(left(n));
		}
		if (!isRightEmpty(n)) {
			preVisit(right(n));
		}
	}
}

template<class T, class N>
void BinTree<T, N>::inVisit(node n) {
	if (!isEmpty()) {
		if (!isLeftEmpty(n)) {
			inVisit(left(n));
		}
		// IN VISIT
		std::cout << " " << read(n) << " ";
		if (!isRightEmpty(n)) {
			inVisit(right(n));
		}
	}
}

template<class T, class N>
void BinTree<T, N>::postVisit(node n) {
	if (!isEmpty()) {
		if (!isLeftEmpty(n)) {
			postVisit(left(n));
		}
		if (!isRightEmpty(n)) {
			postVisit(right(n));
		}
		// POST VISIT
		std::cout << " " << read(n) << " ";
	}
}


#endif /* ALBERO_BINARIO_BINTREE_H_ */
