#include <string>
using namespace std;

#include "albero/alberoNPunt.h"

int main() {
	   AlberoNPunt<int> A, B, C, D;
	    AlberoNPunt<int>::nodo n = new Cell<int>();
	    n->set_element(2);
	    A.print();
	    A.insRadice();
	    A.print();
	    A.scriviNodo(1,A.getRadice());
	    A.print();
	    B.insRadice(n);
	    B.print();
	    A.insPrimoSottoalbero(A.getRadice(),B);
	    A.print();
	    C.insRadice();
	    C.scriviNodo(3,C.getRadice());
	    B.insSottoalbero(B.getRadice(),C);
	    A.print();
	    D.insRadice();
	    D.scriviNodo(4,D.getRadice());
	    B.insPrimoSottoalbero(B.getRadice(),D);
	    cout << "before delete: "; A.print();

	    cout << A.leggiNodo(A.padre(D.getRadice())) << " è padre di " << A.leggiNodo(D.getRadice()) << endl;
	    cout << A.leggiNodo(A.padre(B.getRadice())) << " è padre di " << A.leggiNodo(B.getRadice()) << endl;
	    cout << A.leggiNodo(A.padre(C.getRadice())) << " è padre di " << A.leggiNodo(C.getRadice()) << endl;

	    cout << "max lvl: " << A.maxLivello() << "  dim: " << A.dimAlbero(A.getRadice()) << endl;
	    A.cancSottoalbero(B.getRadice());
	    cout << "after delete: "; A.print();
	    A.cancSottoalbero(A.getRadice());
	    cout << "after delete: "; A.print();

	    cout << "pt" ;
	    //A.postVisita(A.getRadice());
	    return 0;
}


