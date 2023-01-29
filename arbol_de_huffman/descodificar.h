/*
      Este script contiene las funciones para descodificar un mensaje codificado.
    
     1) Primero debemos descodificar y guardar el árbol de huffman que se utilizó
    para codificar guardado en "codificaciones/huffman.txt". 

     2) Una vez tenemos el árbol de huffman descodificamos el mensaje codificado 
    guardado en "codificaciones/mensaje".
*/


// pasar el fichero a una string
string leer_fich(string file){
    ifstream f(file);
    if (!f.is_open()){
        cout << "Error!" << endl;
        exit(1);
    }
    string ss_file;
    while (!f.eof()){
        string linea;
        getline(f,linea);
        ss_file += linea;
        if (!f.eof())
            ss_file += "\n";
    }
    f.close();
    return ss_file;
}

// desencriptar el arbol de huffman que teniamos codificado en una string
arbolHuffman<char> leer_huffman_code(string &code){
    
    char c = code[0];
    code.erase(code.begin());
    
    if (c != '+'){
        // tratamiento del simbolo '+' que recordemos que está codificado como "--."
        if ((c == '-') && (code.size() > 1) && (code[0] == '-') && (code[1] == '.')){
            code.erase(code.begin());
            code.erase(code.begin());
            c = '+';
        }
        nodoHoja<char> *hoja = new nodoHoja<char>;
        hoja->peso = 0;   // para dar algún valor (evita errores)
        hoja->dato = c;
        return hoja;
    }
    else {
        // datos
        arbolHuffman<char> izq = leer_huffman_code(code);
        arbolHuffman<char> der = leer_huffman_code(code);
        // nodo
        nodoInterno<char> *interno = new nodoInterno<char>;
        interno->peso = 0;   // para dar algún valor (evita errores)
        interno->izq = izq;
        interno->der = der;
        return interno;
    }
}

// hacer la cargar completa del árbol de hufman
arbolHuffman<char> descodificar_huffman(bool en_binario){
    string s1 = "codificaciones", s2 = (en_binario ? "_binario" : ""), s3 = "/huffman.txt";
    string path = s1 + s2 + s3; 
    string ss_file = leer_fich(path);
    arbolHuffman<char> huff = leer_huffman_code(ss_file);
    return huff;
} 

// descodificar el mensaje encriptado con ayuda del árbol de huffman 
string descodificar(string cod, arbolHuffman<char> &ah){
    arbolHuffman<char> actual = ah;
    string descod = "";
    for (char s : cod){
        if (s == '0')
            actual = ((nodoInterno<char>*) actual)->izq;
        else   
            actual = ((nodoInterno<char>*) actual)->der;
        if (actual->esHoja()){
            descod += ((nodoHoja<char>*) actual)->dato;
            actual = ah;
        }
    }
    return descod;
}

// descodificar el mensaje BINARIO encriptado con ayuda del árbol de huffman 
string descodificar_binario(vector<bool> cod_mensaje, arbolHuffman<char> &ah){
    arbolHuffman<char> actual = ah;
    string descod = "";
    for (bool c : cod_mensaje){
        if (c == false)
            actual = ((nodoInterno<char>*) actual)->izq;
        else   
            actual = ((nodoInterno<char>*) actual)->der;
        if (actual->esHoja()){
            descod += ((nodoHoja<char>*) actual)->dato;
            actual = ah;
        }
    }
    return descod;
}