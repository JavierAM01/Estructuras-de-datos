# include <iostream>

using namespace std;

template <typename T> struct Nodo {
    T data;
    Nodo <T> *next;
    Nodo <T> *pred;
};

template <typename T> struct Cola2 {
    Nodo <T> *front;
    Nodo <T> *back;
};

template <typename T> class cola_anidada_doble {
    private:
        Cola2 <T> cola;
    public:
        cola_anidada_doble();
        ostream & operator << (ostream &o);
        bool empty();
        Nodo<T>* begin();
        void push_front(T);
        void push_back(T);
        void pop_front();
        void pop_back();
        T front();
        T back();
};

// ---------------------------------------------

// Inicializador de clase
template <typename T> cola_anidada_doble<T>::cola_anidada_doble(){
    cola.front = NULL;
    cola.back = NULL;
}

// Salida por pantalla de la cola
template <typename T> ostream& operator << (ostream &o, cola_anidada_doble<T> cola){
    Nodo<T> *aux = cola.begin();
    o << "[";
    while (aux != NULL){
        o << aux->data;
        if (aux->next != NULL)
            o << ",";
        aux = aux->next;
    }
    o << "]";
    return o;
}

// Ver si está la cola vacía
template <typename T> bool cola_anidada_doble<T>::empty(){
    return cola.front == NULL && cola.back == NULL;
}

// Nos devuelve el nodo más a la izquierda de la cola doble para poder iterar sobre ella
template <typename T> Nodo<T>* cola_anidada_doble<T>::begin(){
    return cola.back;
}

// Introducir elementos a la cola: Tener en cuenta si está o no vacía y actualizar 
// los punteros siguiente (next) y anterior (pred) de los nodos de los extremos
template <typename T> void cola_anidada_doble<T>::push_front(T value){
    Nodo <T> *aux = new Nodo <T>;
    aux->data = value;
    aux->next = NULL;
    if (not empty()){
        aux->pred = cola.front;
        cola.front->next = aux;
        cola.front = aux;
    }
    else {
        aux->pred = NULL;
        cola.front = aux;
        cola.back = aux;
    }
}
template <typename T> void cola_anidada_doble<T>::push_back(T value){
    Nodo <T> *aux = new Nodo <T>;
    aux->data = value;
    aux->pred = NULL;
    if (not empty()){
        aux->next = cola.back;
        cola.back->pred = aux;
        cola.back = aux;
    }
    else {
        aux->next = NULL;
        cola.front = aux;
        cola.back = aux;
    }
}

// Eliminar un elemento de la cola: Si esta vacía no hacemos nada, si solo hay un elemento,
// reiniciamos la cola, y si hay más de uno entonces solo eliminamos el del extremo (front / back) 
// de la cola (delete) y actualizamos
template <typename T> void cola_anidada_doble<T>::pop_front(){
    if (empty())
        int a; // pass
    else if (cola.front == cola.back){
        delete cola.front;
        delete cola.back;
        cola.front = NULL;
        cola.back = NULL;
    }
    else {
        cola.front = cola.front->pred;
        delete cola.front->next;
        cola.front->next = NULL;
    }   
}
template <typename T> void cola_anidada_doble<T>::pop_back(){
    if (empty())
        int a;
    else if (cola.front == cola.back){
        delete cola.front;
        delete cola.back;
        cola.front = NULL;
        cola.back = NULL;
    }
    else {
        cola.back = cola.back->next;
        delete cola.back->pred;
        cola.back->pred = NULL;
    }   
}

// Ver el primer valor de la cola (intentar hacerlo solo si sabemos que no está la cola vacía)
// if (not cola.empty()) cout << cola.top();
template <typename T> T cola_anidada_doble<T>::front(){
    if (empty())
        return NULL;
    return cola.front->data;
}
template <typename T> T cola_anidada_doble<T>::back(){
    if (empty())
        return NULL;
    return cola.back->data;
}
