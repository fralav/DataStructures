#ifndef DIZIONARIO_HASH_TABLE_H_
#define DIZIONARIO_HASH_TABLE_H_

#include <string>
#include <bitset>
#include <cmath>

#include "linear_dictionary.h"
#include "couple.h"

const int MAX_DIMENSION = 23;

template<class E>
class HashTable: public LinearDictionary<std::string, E> {
public:
	typedef typename LinearDictionary<std::string, E>::key key;
	typedef typename LinearDictionary<std::string, E>::value element;

	HashTable();
	HashTable(int);
	HashTable(const HashTable<E> &);
	~HashTable();

	void create();
	bool isEmpty() const;
	bool contains(const key) const;
	void insert(const key, const element);
	void erase(const key);
	element find(const key) const;
	void modify(const key, const element);

	template<class F>
	friend std::ostream &operator<<(std::ostream &, const HashTable<F> &);

private:
	Couple<key, element>* table;
	int dimension;
	int size;

	void changeDimension(const int);
	int hash(const key) const;
	int search(const key) const;
};

template<class E>
HashTable<E>::HashTable() {
	dimension = MAX_DIMENSION;
	size = 0;
	create();
}

template<class E>
HashTable<E>::HashTable(int dimension) {
	this->dimension = dimension;
	size = 0;
	create();
}

template<class E>
HashTable<E>::HashTable(const HashTable<E> &copyHash) {
	dimension = copyHash.dimension;
	size = copyHash.size;
	create();
	for (int i = 0; i < dimension; i++) {
		table[i].setKey(copyHash.table[i].getKey());
		table[i].setValue(copyHash.table[i].getKey());
	}
}

template<class E>
HashTable<E>::~HashTable() {
	delete[] table;
}

template<class E>
void HashTable<E>::create() {
	table = new Couple<HashTable<E>::key, HashTable<E>::element>[dimension];
	for (int i = 0; i < dimension; i++) {
		table[i].setKey("");
	}
	return;
}

template<class E>
bool HashTable<E>::isEmpty() const {
	return size == 0;
}

template<class E>
bool HashTable<E>::contains(const HashTable<E>::key key) const {
	int i = search(key);
	return (table[i].getKey() == key) ? true : false;
}

template<class E>
void HashTable<E>::insert(const HashTable<E>::key key, const HashTable<E>::element element) {
	int i = search(key);
	if (table[i].getKey() == "") {
		table[i].setKey(key);
		table[i].setValue(element);
		size++;
	} else {
		if (table[i].getKey() == key) {
			table[i].setValue(element);
		}
	}
}

template<class E>
void HashTable<E>::erase(const HashTable<E>::key key) {
	int i = search(key);
	if (table[i].getKey() == key) {
		table[i].setKey("");
		size--;
	}
	return;
}

template<class E>
typename HashTable<E>::element HashTable<E>::find(const HashTable<E>::key key) const {
	element el;
	int i = search(key);
	if (table[i].getKey() == key) {
		el = table[i].getValue();
	} else {
		return element();
	}
	return el;
}

template<class E>
void HashTable<E>::modify(const HashTable<E>::key key, const HashTable<E>::element element) {
	int i = search(key);
	if (table[i].getKey() == key) {
		table[i].setValue(element);
	}
	return;
}

template<class E>
void HashTable<E>::changeDimension(const int newDimension) {
	if (newDimension > dimension) {
		Couple<HashTable<E>::key, HashTable<E>::element>* temp = new Couple<HashTable<E>::key, HashTable<E>::element>[newDimension];
		for (int i = 0; i < dimension; i++) {
			temp[i].setKey(table[i].getKey());
			temp[i].setValue(table[i].getValue());
		}
		dimension = newDimension;
		delete[] table;
		table = temp;
	}

}

template<class E>
int HashTable<E>::hash(const HashTable<E>::key key) const {
	/* HASH-0
	int b = 0;
	in l = key.length();
	for (int i = 0; i < l; i++) {
		b += (int) key[i];
	}
	std::cout << "Hash: " << key << "->" << b << std::endl;
	return b; */

	// HASH-3 ...

	int bit = 6; // Numero di bit per rappresentare ciascun carattere della chiave
	// int C = (sqrt(5)-1) / 2;
	unsigned int i = 0;
	for (int j = 0; i < key.length(); j++) {
		std::bitset<8> ord(std::toupper(key[j])); // Per caratteri e numeri fino al sesto bin, sono uguali
		i += (2^bit^(key.length()-j))* std::stoi(ord.to_string(), nullptr, 2);
	}
	return i/dimension % dimension;
}

template<class E>
int HashTable<E>::search(const HashTable<E>::key key) const {
	int i = hash(key) % dimension;
	int j = i;
	do {
		if (table[j].getKey() == "" || table[j].getKey() == key) {
			break;
		}
		j = (j+1) % dimension;
	} while (j != i);
	return j;
}

template<class E>
std::ostream &operator<<(std::ostream &os, const HashTable<E> &h) {
	if (h.isEmpty()) {
		os << "Tabella vuota!" << std::endl;
	} else {
		int count = 0;
		os << std::endl;
		for (int i = 0; i < h.dimension && count < h.size; i++) {
			if (h.table[i].getKey() != "") {
				count++;
				os << "|" << h.table[i];
				if (count != h.size) {
					os << std::endl;
				}
			}
		}
	}
	os << std::endl;
	return os;
}

#endif /* DIZIONARIO_HASH_TABLE_H_ */
