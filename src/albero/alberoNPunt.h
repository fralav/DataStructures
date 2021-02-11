#ifndef ALBERONPUNT_H
#define ALBERONPUNT_H


#include "alberoN.h"
#include "cell.h"
#include "exceptions.h"

template <class T>
class AlberoNPunt : public AlberoN<T, Cell<T>*>{

public:
    typedef typename AlberoN<T, Cell<T>*>::tipoElem tipoElem;
    typedef typename AlberoN<T, Cell<T>*>::nodo nodo;

    /*****constructors*****/
    AlberoNPunt();

    /*****copy constructor*****/
    //AlberoNPunt(const AlberoNPunt<T> &);

    /*****destructor*****/
    ~AlberoNPunt();

    /*****operators*****/
    void creaAlbero();
    bool alberoVuoto() const;
    nodo getRadice()const;
    nodo padre(nodo)const;
    bool foglia(nodo)const;
    bool ultimoFratello(nodo)const;
    nodo primoFiglio(nodo)const;
    nodo succFratello(nodo)const;

    void insRadice();
    void insRadice(nodo);

    void insPrimoSottoalbero(nodo, AlberoN<T,Cell<T>*>&);
    void insSottoalbero(nodo, AlberoN<T,Cell<T>*>&);
    void cancSottoalbero(nodo);

    void scriviNodo(tipoElem, nodo);
    tipoElem leggiNodo(nodo) const;

    int getLivello(nodo) const;

private:
    nodo radice;

    void aggiornaLivello(int, nodo);
};

template <class T>
AlberoNPunt<T>::AlberoNPunt() {
    this->creaAlbero();
}

template <class T>
AlberoNPunt<T>::~AlberoNPunt(){
    //cancSottoalbero(radice);
    //cout << "deleting " << endl;
    delete radice;
}

template <class T>
void AlberoNPunt<T>::creaAlbero() {
    radice = nullptr;
}

template <class T>
bool AlberoNPunt<T>::alberoVuoto() const{
    if(radice == nullptr)
        return true;
    else
        return false;
}

template <class T>
typename AlberoNPunt<T>::nodo AlberoNPunt<T>::getRadice() const {
    if(!alberoVuoto())
        return radice;
    else throw EmptyTree();
}

template <class T>
typename AlberoNPunt<T>::nodo AlberoNPunt<T>::padre(nodo n) const{
    if(!alberoVuoto()){
        if (n->get_livello() > 0)
            return n->get_padre();
        else return n;
    }else throw EmptyTree();
}

template <class T>
bool AlberoNPunt<T>::foglia(nodo n) const{
    if (n->get_primoFiglio() == nullptr)
        return true;
    else return false;
}

template <class T>
bool AlberoNPunt<T>::ultimoFratello(nodo n) const{
    if (n->get_succFratello() == nullptr)
        return true;
    else return false;
}

template <class T>
typename AlberoNPunt<T>::nodo AlberoNPunt<T>::primoFiglio(nodo n) const{
        if(!alberoVuoto()){
            if(!foglia(n))
                return n->get_primoFiglio();
            else return NULL;
        }else throw EmptyTree();
}

template <class T>
typename AlberoNPunt<T>::nodo AlberoNPunt<T>::succFratello(nodo n) const{
        if(!alberoVuoto()){
            if(!ultimoFratello(n))
                return n->get_succFratello();
            else return NULL;
        }else throw EmptyTree();
}

template <class T>
void AlberoNPunt<T>::insRadice(){
    if (this->alberoVuoto()){
        radice = new Cell<T>();
        radice->set_livello(0);
    }
    else throw RootExists();
}

template <class T>
void AlberoNPunt<T>::insRadice(nodo n){
    if (this->alberoVuoto()){
        radice = n;
        radice->set_livello(0);
    }
    else throw RootExists();
}

template <class T>
void AlberoNPunt<T>::insPrimoSottoalbero(nodo n, AlberoN<T,Cell<T>*>& A){
    if (!alberoVuoto() && !A.alberoVuoto()){
        if(foglia(n)){
            n->set_primoFiglio(A.getRadice());
        }
        else{
            A.getRadice()->set_succFratello(n->get_primoFiglio());
            n->set_primoFiglio(A.getRadice());
        }
        aggiornaLivello(getLivello(n), n);
        A.getRadice()->set_padre(n);
    }else throw EmptyTree();
}

template <class T>
void AlberoNPunt<T>::insSottoalbero(nodo n, AlberoN<T,Cell<T>*>& A){
        if (!alberoVuoto() && !A.alberoVuoto()){
            if(ultimoFratello(n)){
                n->set_succFratello(A.getRadice());
            }
            else{
                A.getRadice()->set_succFratello(n->get_succFratello());
                n->set_succFratello(A.getRadice());
            }
            aggiornaLivello(getLivello(padre(n)), padre(n));
            A.getRadice()->set_padre(padre(n));
        }else throw EmptyTree();
}

template <class T>
void AlberoNPunt<T>::cancSottoalbero(nodo n){
    if (!alberoVuoto()){
       // cout << "albero non vuoto, ciclo " << leggiNodo(n) << endl;
       // cout << "padre = n : " << leggiNodo(padre(n)) << " = " << leggiNodo(n) << "? " <<  (padre(n) == n) << endl;
        if (padre(n) != n){
            if(primoFiglio(padre(n)) == n){
                //cout << leggiNodo(n) << " è primofiglio di " << leggiNodo(padre(n)) << endl;
                if(!ultimoFratello(n))
                    padre(n)->set_primoFiglio(succFratello(n));
                else
                    padre(n)->set_primoFiglio(nullptr);
            }else{
                //cout << leggiNodo(n) << " è succFiglio di " << leggiNodo(padre(n)) << endl;
                nodo temp = primoFiglio(padre(n));
                bool found = false;
                while(!ultimoFratello(temp) && found == false){
                    if(temp->get_succFratello() == n){
                        if(ultimoFratello(n))
                            temp->set_succFratello(nullptr);
                        else
                            temp->set_succFratello(n->get_succFratello());
                        found = true;
                    }
                temp = temp->get_succFratello();
                //cout << "changed" << endl;
                }
            }
        }
        while(!foglia(n)){
            //cout << leggiNodo(n) << " non è foglia..." << endl;
            cancSottoalbero(primoFiglio(n));
            }
       // cout << "è foglia, cancello " << leggiNodo(n) << endl;
        delete n;
    }
}

template <class T>
void AlberoNPunt<T>::scriviNodo(tipoElem e, nodo n) {
    n->set_element(e);
}

template <class T>
typename AlberoNPunt<T>::tipoElem AlberoNPunt<T>::leggiNodo(nodo n) const{
    return n->get_element();
}

template <class T>
int AlberoNPunt<T>::getLivello(nodo n) const{
    return n->get_livello();
}

template <class T>
void AlberoNPunt<T>::aggiornaLivello(int liv, nodo n){
    n->set_livello(liv);
    if(!foglia(n)){
        nodo son = primoFiglio(n);
        aggiornaLivello(liv + 1, son);
        while(!ultimoFratello(son)){
            son = succFratello(son);
            aggiornaLivello(liv + 1, son);
        }
    }
}


#endif
