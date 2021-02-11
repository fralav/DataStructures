#ifndef DIZIONARIO_LINEAR_DICTIONARY_H_
#define DIZIONARIO_LINEAR_DICTIONARY_H_

#include <string>

#include "couple.h"

template<class K, class V>
class LinearDictionary {
public:
	typedef K key;
	typedef V value;

	virtual void create() = 0;
	virtual bool isEmpty() const = 0;
	virtual bool contains(const key) const = 0;
	virtual void insert(const key, const value) = 0;
	virtual void erase(const key) = 0;
	virtual value find(const key) const = 0;
	virtual void modify(const key, const value) = 0;

protected:
	~LinearDictionary() {}
};




#endif /* DIZIONARIO_LINEAR_DICTIONARY_H_ */
