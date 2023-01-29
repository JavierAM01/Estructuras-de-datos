
template <typename T> struct tabla_valores{
    T valores[256];
    bool asignado[256];
};

// nosotros solo utilizaremos 'T1 = char' pero esto también nos dejaría utilizar
// 'T1 = int' (enteros de 0 a 255, por como se ha definido la tabla de valores)
template <typename T1, typename T2> class myMap {
    private:
        tabla_valores <T2> tabla;
    public:
        myMap();
        T2 operator [] (T1);
        void insert(T1,T2);
        bool find(T1);
};

// ----------------------------------------------------------------------------

// Inicializador de clase
template <typename T1, typename T2> myMap<T1,T2>::myMap(){
    for(int i=0; i<256; i++)
        tabla.asignado[i] = false;
}

// Sobredefinimos el operador [] para un uso del map más natural
//     diccionario[key] --> value
template <typename T1, typename T2> T2 myMap<T1,T2>::operator [] (T1 key){
    return tabla.valores[key];
}


// Insertar tuplas (key,value) en el diccionario
template <typename T1, typename T2> void myMap<T1,T2>::insert(T1 key, T2 value){
    tabla.asignado[key] = true;
    tabla.valores[key] = value;
}

// Ver si un cierto valor (key) esta asignado en nuestro diccionario
template <typename T1, typename T2> bool myMap<T1,T2>::find(T1 key){
    return tabla.asignado[key];
}