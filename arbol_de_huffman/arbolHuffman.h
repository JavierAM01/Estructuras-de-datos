/*
      Definición del tipo de dato Árbol de Huffman con tres nodos 
    con herencia:
    
     1) nodoHuffman (nodo padre)
     2) nodoHoja 
     3) nodoInterno

    así como funciones para crear hojas y nodos internos.
*/


// tipo de dato "principal" para los nodos del arbol de huffman
template <typename T>
struct nodoHuffman {
    int peso;
    virtual bool esHoja(){
        return false;
    }
};

// nodo hoja : hereda del nodo "principal"
template <typename T>
struct nodoHoja : nodoHuffman<T> {
    T dato;
    bool esHoja(){
        return true;
    }
};

// nodo interno : hereda del nodo "principal"
template <typename T>
struct nodoInterno : nodoHuffman<T> {
    nodoHuffman<T> *izq;
    nodoHuffman<T> *der;
};

template <typename T>
using arbolHuffman = nodoHuffman<T> *;

// altura de un arbol de huffman
template <typename T>
int altura(arbolHuffman<T> &ah){
    if (ah == NULL)
        return 0;
    if (ah->esHoja())
        return 1;
    return 1 + max(altura(((nodoInterno<T> *) ah)->izq), altura(((nodoInterno<T> *) ah)->der));
}

// crear una hoja a partir del peso y un dato
template <typename T>
arbolHuffman<T> crear_hoja(int peso, T dato){
    nodoHoja<T> *ah = new nodoHoja<T>;
    ah->peso = peso;
    ah->dato = dato;
    return ah;
}

// crear un nodo interno a partir de otros dos nodos huffman
template <typename T>
arbolHuffman<T> unir_arboles(arbolHuffman<T> izq, arbolHuffman<T> der){
    nodoInterno<T> *ah = new nodoInterno<T>;
    ah->peso = (izq->peso) + (der->peso);
    ah->izq = izq;
    ah->der = der;
    return ah;
}
