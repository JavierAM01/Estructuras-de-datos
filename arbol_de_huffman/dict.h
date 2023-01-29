/*
      Este script contine el tipo de dato "dict" que hace la función de un diccionario.
    Así podremos acceder con una "clave" a su "valor" correspondiente. 
    
      Se ha implementado internamente como un ABB (Árbol Binario de Busqueda) para que la 
    búsqueda de la "clave" sea logaritmica en función del tamaño. Para ello, el tipo de dato "clave", 
    que a lo largo del script se representa con el template "T1", tiene que tener un orden definido.
*/


// Tipo de dato "par" para guardar pares "clave - valor" en el ABB  
template <typename T1, typename T2> 
struct par {
    T1 clave;
    T2 valor;
};

// Tipo de dato para el diccionario (usaremos la struct "par" como dato) 
template <typename T1, typename T2> 
struct nodoDict {
    par<T1,T2> dato;
    nodoDict<T1,T2> * izq;
    nodoDict<T1,T2> * der;
};

template <typename T1, typename T2> 
using dict = nodoDict<T1,T2> *; 


// Insertar un par en la Tabla de Frecuencias
template <typename T1, typename T2>
void insertar(dict<T1,T2> &tabla, par<T1,T2> dato){
    if (tabla == NULL){
        tabla = new nodoDict<T1,T2>;
        tabla->dato = dato;
        tabla->izq = NULL;
        tabla->der = NULL;
    }
    else if (dato.clave == tabla->dato.clave){
        tabla->dato.valor = dato.valor;
    }
    else if (dato.clave < tabla->dato.clave)
        insertar(tabla->izq, dato);
    else 
        insertar(tabla->der, dato);
}


// Conseguir el valor de la tabla, dada una clave
template <typename T1, typename T2> 
T2 get(dict<T1,T2> &tabla, T1 clave){
    dict<T1,T2> aux = tabla;
    if (aux == NULL)
        throw std::invalid_argument("Error! El diccionario no contine dicha clave!");
    while (aux->dato.clave != clave){
        if (clave < aux->dato.clave)
            aux = aux->izq;
        else 
            aux = aux->der;
        if (aux == NULL)
            throw std::invalid_argument("Error! El diccionario no contine dicha clave!");
    }  
    return aux->dato.valor;
}

// Ver si cierta clave esta asignada en nuestra Tabla de Frecuencias
template <typename T1, typename T2> 
bool buscar(dict<T1,T2> tabla, T1 clave){
    dict<T1,T2> aux = tabla;
    if (aux == NULL)
        return false;
    while (aux->dato.clave != clave){
        if (clave < aux->dato.clave)
            aux = aux->izq;
        else 
            aux = aux->der;
        if (aux == NULL)
            return false;
    }
    return true;
}