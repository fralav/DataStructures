#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

template <class T>
class Cell{

public:
    typedef T value_type;

    /*****constructors*****/
    Cell();
    //Cell(const value_type &);
    //Cell(value_type &, Cell<T>* p, Cell<T>* n);

    /*****destructor*****/
    ~Cell();

    /*****getters*****/
    value_type get_element() const;
    Cell<T>* get_primoFiglio() const;
    Cell<T>* get_succFratello() const;
    Cell<T>* get_padre() const;
    int get_livello() const;

    /*****setters*****/
    void set_element(value_type);
    void set_primoFiglio(Cell<T>*);
    void set_succFratello(Cell<T>*);
    void set_padre(Cell<T>*);
    void set_livello(int);

    /*****operators overload*****/
    Cell<T>& operator = (const Cell<T> &);

private:
    int livello;
    value_type element;
    Cell<T>* primoFiglio;
    Cell<T>* succFratello;
    Cell<T>* padre;
};

/***********implementation*************/

template <class T>
Cell<T>::Cell(){
    this->primoFiglio = nullptr;
    this->succFratello = nullptr;
    this->padre = nullptr;
    }

/*template <class T>
Cell<T>::Cell(const value_type &value){
    this->element = value;
    Cell();
    }*/

/*template <class T>
Cell<T>::Cell(value_type &value, Cell<T>* p, Cell<T>* n){
    this->element = value;
    this->next = n;
    this->previous = p;
    }*/

template <class T>
Cell<T>::~Cell(){}

template <class T>
typename Cell<T>::value_type Cell<T>::get_element() const{
    return this->element;
    }

template <class T>
Cell<T>* Cell<T>::get_primoFiglio() const{
    return this->primoFiglio;
    }

template <class T>
Cell<T>* Cell<T>::get_succFratello() const{
    return this->succFratello;
    }

template <class T>
Cell<T>* Cell<T>::get_padre() const{
    return this->padre;
    }


template <class T>
int Cell<T>::get_livello() const{
    return this->livello;
    }

template <class T>
void Cell<T>::set_element(value_type value){
    this->element = value;
}

template <class T>
void Cell<T>::set_primoFiglio(Cell<T>* p){
    this->primoFiglio = p;
}

template <class T>
void Cell<T>::set_succFratello(Cell<T>* p){
    this->succFratello = p;
}

template <class T>
void Cell<T>::set_padre(Cell<T>* p){
    this->padre = p;
}

template <class T>
void Cell<T>::set_livello(int liv){
    this->livello = liv;
}

/*****operators*****/

template <class T>
Cell<T>& Cell<T>::operator = (const Cell<T> &c){
    this->element = c.get_element();
    this->primoFiglio = c.get_primoFiglio();
    this->succFratello = c.get_succFratello();
    this->padre = c.get_padre();
}

#endif // CELL_H_INCLUDED
