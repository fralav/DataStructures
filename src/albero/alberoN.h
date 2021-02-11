#ifndef ALBERON_H_
#define ALBERON_H_

#include <iostream>
using namespace std;

template <class T, class N>
class AlberoN{
public:

    // tipi
    typedef T tipoElem;
    typedef N nodo;

    virtual void creaAlbero() = 0;
    virtual bool alberoVuoto() const = 0;
    virtual nodo getRadice()const = 0;
    virtual nodo padre(nodo)const = 0;
    virtual bool foglia(nodo)const = 0;
    virtual bool ultimoFratello(nodo) const = 0;
    virtual nodo primoFiglio(nodo)const = 0;
    virtual nodo succFratello(nodo)const = 0;

    virtual void insRadice() = 0;
    virtual void insRadice(nodo) = 0;

    virtual void insPrimoSottoalbero(nodo, AlberoN<T,N>&) = 0;
    virtual void insSottoalbero(nodo, AlberoN<T,N>&) = 0;
    virtual void cancSottoalbero(nodo) = 0;

    virtual void scriviNodo(tipoElem, nodo) = 0;
    virtual tipoElem leggiNodo(nodo) const = 0;

 // funzioni di servizio da implementare qui
    virtual void preVisita(nodo);
    virtual void inVisita(nodo, int);
    virtual void postVisita(nodo);

    virtual void print() const;

    virtual int maxLivello() const;
    virtual int dimAlbero(nodo) const;

private:
    virtual void printSubTree(const nodo) const;
    virtual int calcolaMaxLivello(nodo) const;

};

template <class T, class N>
void AlberoN<T,N>::preVisita(nodo n){
    if (!alberoVuoto()){
        cout << leggiNodo(n) << ", ";
        if(!foglia(n)){
            nodo m = primoFiglio(n);
            preVisita(m);
            while(!ultimoFratello(m)){
                m = succFratello(m);
                preVisita(m);
            }
        }
    }
}

template <class T, class N>
void AlberoN<T,N>::postVisita(nodo n){
    if (!alberoVuoto()){
        if(!foglia(n)){
            nodo m = primoFiglio(n);
            postVisita(m);
            while(!ultimoFratello(m)){
                m = succFratello(m);
                postVisita(m);
            }
        }
    cout << leggiNodo(n) << ", ";
    }
}

template <class T, class N>
void AlberoN<T,N>::inVisita(nodo n, int i){
    if (!alberoVuoto()){
        if(!foglia(n)){
            if( i < 1) i = 1;
            nodo m = primoFiglio(n);
            inVisita(m, i);

            int k = 2;
            while (k <= i && !ultimoFratello(m)){
                m = succFratello(m);
                inVisita(m, i);
                k++;
            }
            cout << leggiNodo(n) << ", ";
            while(!ultimoFratello(m)){
                m = succFratello(m);
                inVisita(m, i);
            }
        }
        else
            cout << leggiNodo(n) << ", ";
    }
}

template <class T, class N>
void AlberoN<T,N>::print() const{
	if (!this->alberoVuoto())
		printSubTree(getRadice());
	else
		std::cout << "[]" << std::endl;
	std::cout << std::endl;
}

template <class T, class N>
void AlberoN<T,N>::printSubTree(const nodo n) const{
	std::cout << "[" << leggiNodo(n);
	if(!foglia(n)){
        cout << ", ";
        nodo m = primoFiglio(n);
        printSubTree(m);
        while(!ultimoFratello(m)){
            cout << ", ";
            m = succFratello(m);
            printSubTree(m);
        }
    }
    std::cout << "]";
}

template <class T, class N>
int AlberoN<T,N>::maxLivello() const{
    int maxLvl = 0;
    if(!alberoVuoto()){
        if (!foglia(getRadice())){
            nodo m = primoFiglio(getRadice());
            maxLvl = calcolaMaxLivello(m);
            while(!ultimoFratello(m)){
                m = succFratello(m);
                int calc = calcolaMaxLivello(m);
                if( calc > maxLvl)
                    maxLvl = calc;
            }
        }
    }
    return maxLvl;
}

template <class T, class N>
int AlberoN<T,N>::calcolaMaxLivello(nodo n) const{
    int maxLvl = 0;

    if (!foglia(n)){
        nodo m = primoFiglio(n);
        maxLvl = calcolaMaxLivello(m);
        while(!ultimoFratello(m)){
            m = succFratello(m);
            int calc = calcolaMaxLivello(m);
            if( calc > maxLvl)
                maxLvl = calc;
        }
    }
    return maxLvl + 1;
}

template <class T, class N>
int AlberoN<T,N>::dimAlbero(nodo n) const{
    int dim = 0;
    if(!alberoVuoto()){
        dim++;
        if (!foglia(n)){
            nodo m = primoFiglio(n);
            dim = dim + dimAlbero(m);
            while(!ultimoFratello(m)){
                m = succFratello(m);
                dim = dim + dimAlbero(m);
            }
        }
    }
    return dim;
}


#endif
