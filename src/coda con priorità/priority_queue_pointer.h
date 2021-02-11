#ifndef CODA_CON_PRIORITÀ_PRIORITY_QUEUE_POINTER_H_
#define CODA_CON_PRIORITÀ_PRIORITY_QUEUE_POINTER_H_

#include "priority_queue.h"
#include "../albero binario/vector_bintree.h"

template<class T>
class PriorityQueuePointer: public BinTreeVector<T> {
public:
	typedef typename PriorityQueue<T>::itemtype itemtype;

	PriorityQueuePointer();

	void create();
	bool isEmpty() const;
	void insert(itemtype);
	itemtype min() const;
	void eraseMin();
};

template<class T>
PriorityQueuePointer<T>::PriorityQueuePointer() {
	create();
}


#endif /* CODA_CON_PRIORITÀ_PRIORITY_QUEUE_POINTER_H_ */
