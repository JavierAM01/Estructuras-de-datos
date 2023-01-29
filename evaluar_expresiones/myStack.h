
template <typename T> struct Pila {
    T *datos;
    int top;
    int max;
};  


template <typename T> class myStack {
    private:
        Pila <T> pila;
    public:
        myStack();
        bool empty();
        bool full();
        void push(T);
        void pop();
        T top();
};

// ----------------------------------------------------

// El nombre de las funciones son el mismo que el de las colas, por lo que su funcionalidad 
// también, teniendo en cuenta claro las diferencias de comportamiento entre colas y pilas.
// En este caso he hecho una pila tipo array.

template <typename T> myStack<T>::myStack(){
    int MAX = 20;
    T *datos = new T [MAX];
    pila.datos = datos;
    pila.top = 0;
    pila.max = MAX;
}

template <typename T> bool myStack<T>::empty(){
    return pila.top == 0;
}

template <typename T> bool myStack<T>::full(){
    return pila.top == pila.max;
}

template <typename T> void myStack<T>::push(T value){
    if (not full()){
        pila.datos[pila.top] = value;
        pila.top++;
    }
    else {
        Pila <T> pila2;
        // copia de datos
        T *datos2 = new T [pila.max*2];
        for (int i=0; i<pila.max; i++)
            datos2[i] = pila.datos[i];
        datos2[pila.max] = value;
        // generar nueva pila
        pila2.datos = datos2;
        pila2.top = pila.top+1;
        pila2.max = 2*pila.max;
        // eliminar la anterior
        delete pila.datos;
        pila = pila2;
    }       
}

template <typename T> void myStack<T>::pop(){
    if (not empty())
        pila.top--;
}

template <typename T> T myStack<T>::top(){
    return pila.datos[pila.top-1];
}


