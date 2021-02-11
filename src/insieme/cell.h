#ifndef INSIEME_CELL_H_
#define INSIEME_CELL_H_

template<class T>
class Cell {
public:
	typedef T itemtype;

	void setElement(itemtype e) {
		element = e;
	}

	itemtype getElement() const {
		return element;
	}

	void setNext(Cell* p) {
		next = p;
	}

	Cell* getNext() const {
		return next;
	}

private:
	itemtype element;
	Cell* next;
};

#endif /* INSIEME_CELL_H_ */
