#ifndef CODA_CON_PRIORITÀ_PRIORITY_QUEUE_H_
#define CODA_CON_PRIORITÀ_PRIORITY_QUEUE_H_

template<typename T>
class PriorityQueue {
public:
	typedef T itemtype;

	virtual void create() = 0;
	virtual bool isEmpty() const = 0;
	virtual void insert(itemtype value) = 0;
	virtual itemtype min() const = 0;
	virtual void eraseMin() = 0;
};



#endif /* CODA_CON_PRIORITÀ_PRIORITY_QUEUE_H_ */
