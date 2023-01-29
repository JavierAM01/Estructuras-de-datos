
template <typename T> struct Cola {
    T *datos;
    int primero;
    int ultimo;
    int tam;
    int max;
};  

template <typename T> class cola_array {
    private:
        Cola <T> cola;
    public:
        cola_array();
        bool empty();
        bool full();
        T* begin();
        int primero();
        int ultimo();
        int tam();
        int max();
        void push_back(T);
        void push_front(T);
        void pop_back();
        void pop_front();
        T top_back();
        T top_front();
};

// -------------------------------------------------

// Inicializador de clase
template <typename T> cola_array<T>::cola_array(){
    int MAX = 5;
    T *datos = new T [MAX];
    cola.datos = datos;
    cola.primero = 0;
    cola.ultimo = MAX-1;
    cola.tam = 0;
    cola.max = MAX;
}

// Salida por pantalla de la cola
template <typename T> ostream& operator << (ostream &o, cola_array<T> cola){
    T *aux = cola.begin();
    int max = cola.max(), tam = cola.tam(), primero = cola.primero();
    o << "[";
    int count = 0;
    while (count < tam){
        int i = (primero+count) % max;
        o << *(aux+i);
        if (count+1 != tam)
            o << ",";
        count++;
    }
    o << "]";
    return o;
}

// Ver si la cola está vacía
template <typename T> bool cola_array<T>::empty(){
    return cola.tam == 0;
}

// Nos devuelve datos[0] (el más a la izquierda de la cola) para poder iterar sobre ella
template <typename T> T* cola_array<T>::begin(){
    return cola.datos;
}

// Ver si la cola está llena (el espacio que hemos reservado para ella) 
template <typename T> bool cola_array<T>::full(){
    return cola.tam == cola.max;
}

// Devuelven las variables que guarda la cola
template <typename T> int cola_array<T>::max(){
    return cola.max;
}
template <typename T> int cola_array<T>::tam(){
    return cola.tam;
}
template <typename T> int cola_array<T>::primero(){
    return cola.primero;
}
template <typename T> int cola_array<T>::ultimo(){
    return cola.primero;
}

// Introducir un elemento en la cola: si no está llena entonces introducimos en el siguiente
// indice (de forma modular), si está llena, duplicamos el tamaño, copiamos la antigua en la nueva,
// introducimos el nuevo valor y renombramos la antigua a la nueva.
template <typename T> void cola_array<T>::push_back(T value){
    if (not full()){
        cola.primero = (cola.primero + cola.max - 1) % cola.max;
        cola.datos[cola.primero] = value;
        cola.tam++;
    }
    else {
        // Aumentando el tamaño al doble ...
        Cola <T> cola2;
        // copia de datos
        T *datos2 = new T [2*cola.max];
        datos2[0] = value;
        for (int i=0; i<cola.max; i++)
            datos2[i+1] = cola.datos[(cola.primero+i) % cola.max];
        // generar nueva cola
        cola2.datos = datos2;
        cola2.primero = 0;
        cola2.ultimo = cola.max;
        cola2.tam = cola.max+1;
        cola2.max = 2*cola.max;
        // eliminar la anterior
        delete [] cola.datos;
        cola = cola2;
    }       
}

template <typename T> void cola_array<T>::push_front(T value){
    if (not full()){
        cola.ultimo = (cola.ultimo + 1) % cola.max;
        cola.datos[cola.ultimo] = value;
        cola.tam++;
    }
    else {
        // Aumentando el tamaño al doble ...
        Cola <T> cola2;
        // copia de datos
        T *datos2 = new T [2*cola.max];
        for (int i=0; i<cola.max; i++)
            datos2[i] = cola.datos[(cola.primero+i) % cola.max];
        datos2[cola.max] = value;
        // generar nueva cola
        cola2.datos = datos2;
        cola2.primero = 0;
        cola2.ultimo = cola.max;
        cola2.tam = cola.max+1;
        cola2.max = 2*cola.max;
        // eliminar la anterior
        delete [] cola.datos;
        cola = cola2;
    }       
}

// Eliminar un elemento: si no está vacía entonces el primero pasa al
// siguiente y el tamaño se reduce en 1. 
template <typename T> void cola_array<T>::pop_back(){
    if (not empty()){
        cola.primero = (cola.primero+1) % cola.max;
        cola.tam--;
    }
}

template <typename T> void cola_array<T>::pop_front(){
    if (not empty()){
        cola.ultimo = (cola.ultimo-1) % cola.max;
        cola.tam--;
    }
}

// Devuelve el primer elemento de la cola
template <typename T> T cola_array<T>::top_back(){
    return cola.datos[cola.primero];
}

template <typename T> T cola_array<T>::top_front(){
    return cola.datos[cola.ultimo];
}

