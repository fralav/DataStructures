#ifndef LIST_LINKED_H_
#define LIST_LINKED_H_

#include "linear_list.h"

template<class T>
struct NodeLinkedList {
	NodeLinkedList<T>* prev;
	T item;
	NodeLinkedList<T>* next;
};

template<class T>
class LinkedList: public LinearList<T, NodeLinkedList<T>*> {
public:
	typedef typename LinearList<T, NodeLinkedList<T>*>::itemtype itemtype;
	typedef typename LinearList<T, NodeLinkedList<T>*>::position position;

	LinkedList();
	LinkedList(const LinkedList<T> &);
	~LinkedList();

	bool isEmpty() const;
	itemtype read(position) const;
	void write(itemtype, position);
	position first() const;
	bool isEnd(position) const;
	position next(position) const;
	position prev(position) const;
	void insert(itemtype, position &);
	void erase(position);

private:
	position list;
};

template<class T>
LinkedList<T>::LinkedList() {
	list = new NodeLinkedList<T>;
	list->next = list;
	list->prev = list;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &l) {
	position pThis, pL;
	pL = l.first();
	this->list = new NodeLinkedList<T>;
	this->list->next = list;
	this->list->prev = list;
	pThis = this->first();
	while (!l.isEnd(pL)) {
		this->insert(l.read(pL), pThis);
		pL = l.next(pL);
		pThis = this->next(pThis);
	}
}

template<class T>
LinkedList<T>::~LinkedList() {
	while (list->next != list->prev) {
		erase(list->next);
	}
	delete list;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
	return ((list->next == list) && (list->prev == list));
}

template<class T>
typename LinkedList<T>::itemtype LinkedList<T>::read(position p) const {
	if (p != nullptr) {
		return p->item;
	}
	return T();
}

template<class T>
void LinkedList<T>::write(itemtype e, position p) {
	if (p != list) {
		p->item = e;
	}
}

template<class T>
typename LinkedList<T>::position LinkedList<T>::first() const {
	return list->next;
}

template<class T>
bool LinkedList<T>::isEnd(position p) const {
	return p == list;
}

template<class T>
typename LinkedList<T>::position LinkedList<T>::next(position p) const {
	return p->next;

}

template<class T>
typename LinkedList<T>::position LinkedList<T>::prev(position p) const {
	return p->prev;
}

template<class T>
void LinkedList<T>::insert(itemtype e, position &p) {
	position temp = new NodeLinkedList<T>;
	temp->item = e;
	temp->prev = p->prev;
	temp->next = p;
	p->prev->next = temp;
	p->prev = temp;
	p = temp;
}

template<class T>
void LinkedList<T>::erase(position p) {
	if (p != nullptr) {
		LinkedList::position temp;
		temp = p;
		p->next->prev = p->prev;
		p->prev->next = p->next;
		p = p->next;
		delete temp;
	}
}

#endif /* LIST_LINKED_H_ */
