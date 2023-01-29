/*
      Script principal. En él vienen definidas dos funciones, los programas 
    1 y 2 pedidos en el trabajo:
    
     1) programa1()
     2) programa2()
*/


#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>   // para crear un directorio -> mkdir
using namespace std;

#include "vectorBool.h"
#include "dict.h"
#include "arbolHuffman.h"
#include "abbHuffman.h"
#include "codificar.h"
#include "descodificar.h"


void programa1(bool en_binario) {

    string file_name;
    cout << "\nNombre del fichero de entrada (mensaje.txt): " << endl;
    cout << " > ";
    cin >> file_name;

    ifstream file(file_name);
    if (!file.is_open())
        cout << "Error al leer el fichero !!" << endl;
    else {
        string s;

        // reservar memoria
        file.seekg(std::ios_base::end);
        s.reserve(file.tellg());
        file.seekg(std::ios_base::beg);

        // leer fichero
        string line;
        while(!file.eof()){
            getline(file,line);
            s.append(line + '\n');
        }
        file.close();

        // Caso base
        if (s.size() == 1){
            cout << "\nFichero vacio! No es necesario codificarlo!" << endl;
        } // Codificar en binario
        else if (en_binario){
            codificar_binario(s);
            cout << "\nMensaje codificado en binario correctamente!" << endl;
        } // Codificar en '0' y '1' 
        else {
            codificar(s);
            cout << "\nMensaje codificado correctamente!" << endl;
        }
    }
}

void programa2(bool en_binario) {
    string s1 = "codificaciones", s2 = (en_binario ? "_binario" : ""), s3 = "/mensaje.txt";
    string path = s1 + s2 + s3;
    ifstream file(path);
    if (!file.is_open())
        cout << "\nNo se encuentra el mensaje codificado! Asegurate de primero compilar 'programa1'!" << endl;
    else if (en_binario){
        // cargar mensaje codificado
        vector<bool> cod_mesaje = file_to_vector_bool(path);

        // cargar el árbol de huffman 
        arbolHuffman<char> huff = descodificar_huffman(true);

        string descod = descodificar_binario(cod_mesaje, huff);
        cout << "\nMensaje descodificado correctamente!" << endl;
        
        cout << "\nDescodificacion:" << endl;
        cout << descod << endl;
    }
    else {
        // reservar memoria
        string cod_mensaje;
        file.seekg(std::ios_base::end);
        cod_mensaje.reserve(file.tellg());
        file.seekg(std::ios_base::beg);

        // cargar mensaje codificado
        while(!file.eof()){
            string line;
            getline(file,line);
            cod_mensaje.append(line);
        }
        file.close();

        // cargar el árbol de huffman 
        arbolHuffman<char> huff = descodificar_huffman(false);

        string descod = descodificar(cod_mensaje, huff);
        cout << "\nMensaje descodificado correctamente!" << endl;
        
        cout << "\nDescodificacion:" << endl;
        cout << descod << endl;
    }
}

bool elegir_modo(string s){
    string modo;
    cout << endl << s << ":" << endl;
    cout << " 1) Binario." << endl;
    cout << " 2) Cadenas de '0' y '1'." << endl;
    cout << " > ";
    cin >> modo;
    return (modo == "1") ? true : false;
}

bool exists(string file){
    ifstream f(file);
    bool e = f.is_open();
    f.close();
    return e;
}

int main(){

    // Elegir programa a ejecutar
    cout << "\nElige un programa:" << endl;
    cout << " 1) Programa 1: codificar mensaje." << endl;
    cout << " 2) Programa 2: descodificar mensaje." << endl;
    cout << " > ";

    string opcion;
    cin >> opcion;
    
    bool en_binario;

    // Elegir tipo de des/codificación -> binario / no binario
    if (opcion == "1")
        en_binario = elegir_modo("Elige un modo de codificacion");
    else {
        if (exists("codificaciones_binario/huffman.txt")){
            if (exists("codificaciones/huffman.txt"))
                en_binario = elegir_modo("Elige que tipo de mensaje descodificar");
            else 
                en_binario = true;
        }
        else if (exists("codificaciones/huffman.txt"))
            en_binario = false;
        else {
            cout << "No existe ningun mensaje codificado! Ejecuta 'programa 1' para codificar el mensaje original antes de descodificar!" << endl;
            exit(1);
        }
    }

    // ejecutar programa
    (opcion == "1") ? programa1(en_binario) : programa2(en_binario);

    return 0;
}