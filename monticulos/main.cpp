#include <iostream>
#include "monticulo_PrimUlt.h"

using namespace std;

template <typename T>
void print(monticulo<T> & m){
    cout << "Monticulo: " << m << endl;
    cout << "Primero: " << m.datos[m.primero]->dato << endl;
    cout << "Ultimo: " << m.datos[m.ultimo]->dato << endl;
}

int main(){

    const int N = 9;
    int valores [N] = {8,3,4,5,2,7,9,1,6};

    cout << "Valores: [";
    for (int i=0; i<N; i++)
        cout << valores[i] << ",";
    cout << "]" << endl;

    monticulo<int> m;
    for (int i=0; i<N; i++){
        insertar(m, valores[i]);
    }

    cout << "\n< Situacion inicial >" << endl;
    print(m);

    cout << "\n< Eliminar ultimo >" << endl;
    eliminar_ultimo(m);
    print(m);

    cout << "\n< Eliminar primero >" << endl;
    eliminar_primero(m);
    print(m);

    cout << "\n< Eliminar minimo >" << endl;
    eliminar(m, 0);
    print(m);

    cout << "\n< Eliminar ultimo >" << endl;
    eliminar_ultimo(m);
    print(m);

    cout << "\n< Eliminar primero >" << endl;
    eliminar_primero(m);
    print(m);

    cout << "\n< Eliminar minimo >" << endl;
    eliminar(m, 0);
    print(m);

    cout << "\n\n\n" << endl;

    return 0;
}