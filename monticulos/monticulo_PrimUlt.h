# include <iostream>
using namespace std;


const int CAP = 10;

template <typename T>
struct nodo {
    T dato;
    int ant;
    int sig;
};

// monticulo con nodos triples (guardan posiciones de entrada)
template <typename T>
struct monticulo {
    nodo<T>* *datos = new nodo<T>* [CAP];
    int capacidad = CAP;
    int tam = 0; 
    int primero = -1;
    int ultimo = -1;
};

template <typename T>
ostream & operator << (ostream & o, const monticulo<T> & m){
    o << "[";
    for (int i=0; i < m.tam; i++)
        o << m.datos[i]->dato << ",";
        //o << "(" << m.datos[i]->dato << "," << m.datos[i]->ant << "," << m.datos[i]->sig << ")";
    o << "]";
    return o;
}

template <typename T>
void insertar(monticulo<T> & m, T dato){
    if (m.tam == 0)
        m.primero = 0;
    // crear nuevo nodo
    nodo<T> *new_nodo = new nodo<T>;
    new_nodo->dato = dato;
    new_nodo->ant = m.ultimo;
    new_nodo->sig = -1;
    // actualizar "sig" del anterior último
    if (m.ultimo != -1)
        m.datos[m.ultimo]->sig = m.tam;
    // duplicar espacio si es necesario
    if (m.tam == m.capacidad)
        duplicar_cap(m);
    // insertar datos
    m.datos[m.tam] = new_nodo;
    m.ultimo = m.tam;
    // actualizar tamaño
    m.tam++;
    // flotar
    flotar(m, m.tam-1);
}

// return 0 -> sin errores / 1 -> el índice no existe
template <typename T>
int eliminar(monticulo<T> & m, int pos){
    // lidiar con errores
    if (es_vacio(m) || pos < 0 || pos >= m.tam)
        return 1;
    // swap con el último
    if (pos != m.tam-1)
        swap(m, pos, m.tam-1);
    // actualizar anteriores y siguientes
    int ant = m.datos[m.tam-1]->ant;
    int sig = m.datos[m.tam-1]->sig;
    if (ant != -1)
        m.datos[ant]->sig = sig;
    if (sig != -1)
        m.datos[sig]->ant = ant;
    // actualizar primero y último
    if (m.primero == m.tam-1)
        m.primero = sig;
    if (m.ultimo == m.tam-1)
        m.ultimo = ant;
    // eliminar 
    delete m.datos[m.tam-1];
    m.tam--;
    // hundir / flotar el nuevo cambio
    if (pos != m.tam){
        if (pos > 0 && m.datos[pos]->dato < m.datos[(pos-1)/2]->dato)
            flotar(m, pos);
        else
            hundir(m, pos);
    }
    return 0;
}

template <typename T>
void duplicar_cap(monticulo<T> & m){
    nodo<T>* *new_datos = new nodo<T>* [2*m.capacidad];
    for (int i=0; i<m.tam; i++)
        new_datos[i] = m.datos[i];
    m.capacidad *= 2;
    delete [] m.datos;
    m.datos = new_datos;
}

// template<typename T> 
// void swap(T & a, T & b){
//     T aux = a;
//     a = b;
//     b = aux;
// }

template <typename T>
void swap(monticulo<T> & m, int pos1, int pos2){
    // Actualizar los anteriores y siguientes de los 2 nodos que vamos a cambiar 
    // El -1 indica que no existe y se encuentra en dos posiciones: 
    //  1) el 1º no tiene anterior
    //  2) el último no tiene siguiente
    int p1_ant = m.datos[pos1]->ant;
    int p1_sig = m.datos[pos1]->sig;
    int p2_ant = m.datos[pos2]->ant;
    int p2_sig = m.datos[pos2]->sig; 
    if (p1_sig != -1)
        m.datos[p1_sig]->ant = pos2;
    if (p1_ant != -1)
        m.datos[p1_ant]->sig = pos2;
    if (p2_sig != -1)
        m.datos[p2_sig]->ant = pos1;
    if (p2_ant != -1)
        m.datos[p2_ant]->sig = pos1;
    // Observar si este cambio afecta al primero / último
    if (pos1 == m.primero)
        m.primero = pos2;
    else if (pos2 == m.primero)
        m.primero = pos1;
    if (pos1 == m.ultimo)
        m.ultimo = pos2;
    else if (pos2 == m.ultimo)
        m.ultimo = pos1;
    // Hacemos un swap de los dos nodos del monticulo
    swap(m.datos[pos1], m.datos[pos2]);
}

template <typename T>
void flotar(monticulo<T> & m, int pos){
    while (pos > 0 && m.datos[pos]->dato < m.datos[(pos-1)/2]->dato){
        swap(m, pos, (pos-1)/2);
        pos = (pos-1)/2;
    }
}

template <typename T>
void hundir(monticulo<T> & m, int pos){
    while (true){
        int sig = pos;
        if (2*pos+1 < m.tam && m.datos[2*pos+1]->dato < m.datos[sig]->dato)   
            sig = 2*pos+1;
        if (2*pos+2 < m.tam && m.datos[2*pos+2]->dato < m.datos[sig]->dato)
            sig = 2*pos+2;
        if (sig == pos)
            break;
        else {
            swap(m, pos, sig);
            pos = sig;
        }
    }
}

template <typename T>
void eliminar_primero(monticulo<T> & m){
    eliminar(m, m.primero);
}

template <typename T>
void eliminar_ultimo(monticulo<T> & m){
    eliminar(m, m.ultimo);
}

template <typename T>
bool es_vacio(monticulo<T> & m){
    return (m.primero == -1);
}