/*
      Definición del tipo de dato ABB. Esto es un árbol binario de búsqueda
    con un árbol de huffman en cada nodo. Se ordena con el peso de árbol de huffman.
*/


// Tipo de dato para el ABB (Árbol Binario de Busqueda)
template <typename T>
struct nodoABB{
    arbolHuffman<T> ah;
    nodoABB<T> * izq;
    nodoABB<T> * der;
};

template <typename T>
using ABB = nodoABB<T> *;

// Insertar un Árbol de Huffman en el ABB
template <typename T>
void insertar(ABB<T> &abb, arbolHuffman<T> ah){
    if (abb == NULL){
        abb = new nodoABB<T>;
        abb->ah = ah;
        abb->izq = NULL;
        abb->der = NULL;
    }
    else if (ah->peso <= abb->ah->peso) {
        insertar(abb->izq, ah);
    }
    else {
        insertar(abb->der, ah);
    }
}

// Conseguir la altura del ABB
template <typename T>
int altura(ABB<T> &abb){
    if (abb == NULL)
        return 0;
    return 1 + max(altura(abb->izq), altura(abb->der));
}

// Función para extraer el árbol de huffman con mínimo peso (y eliminarlo del árbol)
template <typename T>
arbolHuffman<T> extraer_ah_minimo(ABB<T> &abb){
    arbolHuffman<T> min;
    // caso base
    if (abb->izq == NULL){
        min = abb->ah;
        abb = abb->der; // "abb->der" es NULL en el último paso
        return min;
    }
    // encontrar minimo
    ABB<T> actual = abb;
    while (actual->izq->izq != NULL)
        actual = actual->izq;
    min = actual->izq->ah;
    // eliminar minimo
    ABB<T> aux = actual->izq;
    if (actual->izq->der != NULL)
        actual->izq = actual->izq->der;
    else 
        actual->izq = NULL;
    delete aux;
    return min;
}

