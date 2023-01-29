template <typename T>
struct Nodo {
    T dato;
    Nodo<T> *izq;
    Nodo<T> *der;
};

template <typename T>
using Monticulo_max = Nodo<T> *;

template <typename T>
void anadir(Monticulo_max<T> &mm, T dato){
    if (mm == NULL)
        mm = {dato, NULL, NULL};
    else if (mm->dato)
} 