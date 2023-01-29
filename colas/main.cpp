# include <iostream>
# include "cola_anidada_doble.h"
# include "cola_array.h"

using namespace std;


void pruebas_colas_dobles(){
    cola_anidada_doble <int> cola;
    cout << "\n" << cola << endl;
    cout << "Insertar del 0 a 5 por la derecha..." << endl;
    for (int i=0; i<6; i++)
        cola.push_front(i);
    cout << cola << endl;
    cout << "Insertar del 6 a 10 por la izquierda..." << endl;
    for (int i=6; i<11; i++)
        cola.push_back(i);
    cout << cola << endl;
    cout << "Eliminar 3 elementos por la derecha..." << endl;
    for (int i=0; i<3; i++)
        cola.pop_front();
    cout << cola << endl;
    cout << "Eliminar 3 elementos por la izquierda..." << endl;
    for (int i=0; i<3; i++)
        cola.pop_back();
    cout << cola << endl;
}

void pruebas_colas_array(){
    cola_array <int> cola;
    cout << "\nTamano maximo: " << cola.max() << endl;
    cout << cola << endl;
    cout << "Insertar del 0 a 5 por la derecha ... " << endl;
    for (int i=0; i<6; i++)
        cola.push_front(i);
    cout << "Tamano maximo: " << cola.max() << endl;
    cout << cola << endl;
    cout << "Insertar del 6 a 10 por la izquierda..." << endl;
    for (int i=6; i<11; i++)
        cola.push_back(i);
    cout << cola << endl;
    cout << "Eliminar 3 elementos por la derecha..." << endl;
    for (int i=0; i<3; i++)
        cola.pop_front();
    cout << cola << endl;
    cout << "Eliminar 3 elementos por la izquierda..." << endl;
    for (int i=0; i<3; i++)
        cola.pop_back();
    cout << cola << endl;
}


int main(){

    cout << "------------- COLAS DOBLEMENTE ENLAZADAS ------------- " << endl;
    pruebas_colas_dobles();

    cout << "\n\n------------- COLAS ARRAY -------------" << endl;
    pruebas_colas_array();

    return 0;
}
