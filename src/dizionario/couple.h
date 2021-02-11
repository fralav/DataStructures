#ifndef DIZIONARIO_COUPLE_H_
#define DIZIONARIO_COUPLE_H_

#include <iostream>

template<class K, class V>
class Couple {
public:
	Couple() {}

	Couple(K key, const V value) {
		this->key = key;
		this->value = value;
	}

	K getKey() {
		return key;
	}

	void setKey(const K key) {
		this->key = key;
	}

	V getValue() {
		return value;
	}

	void setValue(const V value) {
		this->value = value;
	}

private:
	K key;
	V value;
};

template<class K, class I>
std::ostream &operator<<(std::ostream &os, Couple<K, I> &couple) {
	os << couple.getKey() << ": " << couple.getValue();
	return os;
}



#endif /* DIZIONARIO_COUPLE_H_ */
