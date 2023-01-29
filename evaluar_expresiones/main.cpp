# include <iostream>
# include "funciones.h"


using namespace std;



int main(){

    myMap<char,float> dict;

    // poner las expresiones que uno quiera
    string s = "";
    s += "A -> 1.5; B -> 3.5; C -> 0.75; D -> 2.3; E -> 4.5;";
    s += "X = (A + B)*C;";
    s += "Y = E + A*B*C / (A+B+C*C+D) * D * E;";
    s += "Z = (A + B + C) * (B + C) / (B + A);";

    // leer todas las expresiones y añadir variables al diccionario
    leer(s, dict);

    cout << "\nValores tras operar: " << endl;
    leer("X; Y; Z;", dict);

    float A = 1.5, B = 3.5, C = 0.75, D = 2.3, E = 4.5;
    cout << "\nValores objetivo: " << endl;
    cout << "X = " << (A + B)*C << endl;
    cout << "Y = " << E + A*B*C / (A+B+C*C+D) * D * E << endl;
    cout << "Z = " << (A + B + C) * (B + C) / (B + A) << endl << endl;

    return 0;
}