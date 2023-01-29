/*
      Este script contiene las funciones para codificar un mensaje a través
    de un Árbol de Huffman. Al final de la codificación guardará dos archivos
    en la carpeta "codificaciones":

     1) huffman.txt: contendrá la codificación del árbol de huffman creado,
     para poder recuperarlo luego cuando se quiera descodificar
    
     2) mensaje.txt: contendrá la codificación en 0 y 1 del mensaje original. 
*/


// Crear el Árbol de Huffman a partir de una string "entrada"
arbolHuffman<char> crear_arbol_huffman(string &entrada){
    dict<char,int> contador = NULL;
    string letras = "";
    // contar todas las letras 
    for (char s : entrada){
        if (!buscar(contador,s)){
            par<char, int> dato = {s,1};
            insertar(contador, dato);
            letras += s;
        }
        else {
            int x = 1 + get(contador,s);
            par<char, int> dato = {s,x};
            insertar(contador, dato);
        }
    }
    // crear arbol binario de busqueda 
    ABB<char> abb = NULL;
    for (char s : letras)
        insertar(abb, crear_hoja(get(contador, s), s));
    while ((abb->izq != NULL) || (abb->der != NULL)){
        arbolHuffman<char> a1 = extraer_ah_minimo(abb);
        arbolHuffman<char> a2 = extraer_ah_minimo(abb);
        arbolHuffman<char> a_union = unir_arboles(a1, a2);
        insertar(abb, a_union);
    }
    // el arbol de Huffman final es el que queda en el ABB
    return abb->ah;
}

// codificar el arbol de huffman a una string
string codificar_arbol_huffman(const arbolHuffman<char> &ah){
    if (ah->esHoja()){
        string s("");
        char c = ((nodoHoja<char>*) ah)->dato;
        if (c == '+')
            // el '+' es especial porque lo utilizamos en la codificacion del arbol así que lo tratamos distinto
            return s + "--.";
        else
            return s + c;
    }
    string izq = codificar_arbol_huffman(((nodoInterno<char>*) ah)->izq);
    string der = codificar_arbol_huffman(((nodoInterno<char>*) ah)->der);
    return "+" + izq + der;
} 

// Crear una tabla "tabla_codificaciones" que contenga pares "clave - valor" que indiquen 
// la letra y su codificación con el árbol de Huffman correspondiente 
void codificar_letras(arbolHuffman<char> &ah, dict<char,string> &tabla_codificaciones, string prefijo){
    if (ah->esHoja()){
        par<char, string> dato = {((nodoHoja<char> *) ah)->dato, prefijo};
        insertar(tabla_codificaciones, dato);
    }
    else {
        if (((nodoInterno<char> *) ah)->izq != NULL) {
            string key = prefijo + '0';
            codificar_letras(((nodoInterno<char> *) ah)->izq, tabla_codificaciones, key);
        }
        if (((nodoInterno<char> *) ah)->der != NULL) {
            string key = prefijo + '1';
            codificar_letras(((nodoInterno<char> *) ah)->der, tabla_codificaciones, key);
        }
    }
}

// Codificar la entrada inicial, con los codigos conseguidos por el árbol de huffman
string codificar_string(dict<char,string> &tabla_codificaciones, string &entrada){
    string codificacion = "";
    for (char s : entrada)
        codificacion += get(tabla_codificaciones, s);
    return codificacion;
}

// función principal para codificar el mensaje entrada
void codificar(string entrada) {

    // Codificar
    arbolHuffman<char> ah = crear_arbol_huffman(entrada);
    dict<char,string> tabla_codificaciones = NULL;
    string prefijo = "";
    codificar_letras(ah, tabla_codificaciones, prefijo);
    string cod_mensaje = codificar_string(tabla_codificaciones, entrada);
    
    // Guardar en fichero
    mkdir("codificaciones");
    ofstream f_huff("codificaciones/huffman.txt");
    string cod_huffman = codificar_arbol_huffman(ah);
    f_huff << cod_huffman;
    f_huff.close();
    ofstream f_cod("codificaciones/mensaje.txt");
    f_cod << cod_mensaje;
    f_cod.close();
}



// -----------------------------------------------------------------------------------------
// SE REPITEN LAS FUCNCIONES: "codificar_letras", "codificar_string" y "codificar".
// SON IGUAL QUE LAS ANTERIORES PERO CODIFICAN EN BINARIO EN VEZ DE EN CADENAS DE '0' y '1'.
// -----------------------------------------------------------------------------------------



// Crear una tabla "tabla_codificaciones" que contenga pares "clave - valor" que indiquen 
// la letra y su codificación con el árbol de Huffman correspondiente 
void codificar_letras_binario(arbolHuffman<char> &ah, dict<char,vector<bool>> &tabla_codificaciones, vector<bool> prefijo){
    if (ah->esHoja()){
        par<char, vector<bool>> dato = {((nodoHoja<char> *) ah)->dato, prefijo};
        insertar(tabla_codificaciones, dato);
    }
    else {
        if (((nodoInterno<char> *) ah)->izq != NULL) {
            vector<bool> key = prefijo;
            key.push_back(false);
            codificar_letras_binario(((nodoInterno<char> *) ah)->izq, tabla_codificaciones, key);
        }
        if (((nodoInterno<char> *) ah)->der != NULL) {
            vector<bool> key = prefijo;
            key.push_back(true);
            codificar_letras_binario(((nodoInterno<char> *) ah)->der, tabla_codificaciones, key);
        }
    }
}

// Codificar la entrada inicial, con los codigos conseguidos por el árbol de huffman
vector<bool> codificar_string_binario(dict<char,vector<bool>> &tabla_codificaciones, string &entrada){
    vector<bool> codificacion;
    for (char s : entrada)
        codificacion += get(tabla_codificaciones, s);
    return codificacion;
}

// función principal para codificar el mensaje entrada
void codificar_binario(string &entrada) {

    // Codificar
    arbolHuffman<char> ah = crear_arbol_huffman(entrada);
    dict<char,vector<bool>> tabla_codificaciones = NULL;
    vector<bool> prefijo;
    codificar_letras_binario(ah, tabla_codificaciones, prefijo);
    vector<bool> cod_mensaje = codificar_string_binario(tabla_codificaciones, entrada);
    
    // Guardar en fichero
    mkdir("codificaciones_binario");
    ofstream f_huff("codificaciones_binario/huffman.txt");
    string cod_huffman = codificar_arbol_huffman(ah);
    f_huff << cod_huffman;
    f_huff.close();
    vector_bool_to_file(cod_mensaje, "codificaciones_binario/mensaje.txt");
}