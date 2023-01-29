# include <iostream>
# include "myStack.h"
# include "myMap.h"
# include <map>


using namespace std;

// pasar la cadena 'num' a un float (no se si se podía utilizar algo como 'atof'
// implementado ya en C++)
float pasar_a_float(string num){
    float n = 0;
    int decimales = 0;
    int N = num.size();
    for (int i=0; i<N; i++){
        char c = num[i];
        if (c == ' ')
            continue;
        else if (c == '.')   
            decimales = 1;
        else {
            if (decimales == 0)
                n = 10*n + (c-'0');
            else {
                float d = c-'0';
                for (int i=0; i<decimales; i++)
                    d /= 10;
                n += d;
                decimales++;
            }
        }
    }
    return n;
}

// operar con un operador binario, los dos elementos superiores de la pila
void operar(char operador, myStack <float> &pila){
    float x2 = pila.top();
    pila.pop();
    float x1 = pila.top();
    pila.pop();
    float res;
    if (operador == '+')
        res = x1+x2;
    else if (operador == '-')
        res = x1-x2;
    else if (operador == '*')
        res = x1*x2;
    else
        res = x1/x2;
    pila.push(res);
}

// operar una explerasión del tipo: "(A+B)*C..."
// hay que tener en cuenta el orden de precedencia de los operadores
float operar_expresion(string operacion, myMap<char,float> &dict){
    myStack <char> pila_operadores;
    pila_operadores.push('#');  // indica el final de la pila 
    myStack <float> pila_valores;
    
    int N = operacion.size();
    for (int i=0; i<N; i++){
        char c = operacion[i];
        if (c == ' ')
            continue;
        else if (c == '(')
            pila_operadores.push(c);
        else if (c == ')'){
            char op = pila_operadores.top();
            pila_operadores.pop();
            while (op != '('){
                operar(op, pila_valores);
                op = pila_operadores.top();
                pila_operadores.pop();
            }
        }
        else if (c == '+' or c == '-'){
            char op = pila_operadores.top();
            while (op == '*' or op == '/' or op == '+' or op == '-'){
                operar(op, pila_valores);
                pila_operadores.pop();
                op = pila_operadores.top();
            }
            pila_operadores.push(c);
        }
        else if (c == '*' or c == '/'){
            char op = pila_operadores.top();
            while (op == '*' or op == '/'){
                operar(op, pila_valores);
                pila_operadores.pop();
                op = pila_operadores.top();
            }
            pila_operadores.push(c);
        }
        else {
            float value = dict[c];
            pila_valores.push(value);
        }
    }

    // terminamos de vaciar la pila de operadores
    while (pila_operadores.top() != '#'){
        char op = pila_operadores.top();
        operar(op, pila_valores);
        pila_operadores.pop();
    }

    // si todo está bien, en la pila de valores solo queda un nº y este es el resultado
    return pila_valores.top();
}

// leer una expresión, esta puede ser de 3 tipos:
// 1) A -> 1.23; (asignacion)
// 2) C = B+C;   (evaluacion)
// 3) A;         (hacer un print por consola)
int leer_expresion(string expr, myMap<char,float> &dict){
    // leer variable a asignar
    int inicio = 0;
    int N = expr.size();
    while (true){
        if (expr[inicio] == ' ')
            inicio++;
        else 
            break;
    }
    char asignacion = expr[inicio];

    // ver si solo quiere hacer un print del valor
    bool print = true;
    inicio++;
    while (inicio < N){
        if (expr[inicio] == ' ')
            inicio++;
        else {
            print = false;
            break;
        }
    }
    if (print){
        cout << asignacion << " = " << dict[asignacion] << endl;
        return 0;
    }

    // Ver si es '<-' o bien '='
    bool evaluar = false;
    if (expr[inicio] == '='){
        evaluar = true;
        inicio++;
    }

    // (=) evaluar la expresion y asignar el resultado a 'asignacion'
    if (evaluar){
        string operacion = expr.substr(inicio);
        float res = operar_expresion(operacion, dict);
        dict.insert(asignacion,res);
    }
    // (<-) asignar un float a una variable
    else {
        while (expr[inicio] == '>' || expr[inicio] == '-' || expr[inicio] == ' '){
            inicio++;
        }
        string num = expr.substr(inicio);
        float n = pasar_a_float(num);
        dict.insert(asignacion,n);
    }
    return 0;
}

// leer una expresión completa del tipo:
// "A <- 1.5; B <- 3.5; C <- 2; D <- 4; E = (A+B)*(C+D) / (A+B+C+D) + ...; A; B; C; D; E;"
// vamos a hacer un bucle leyendo una a una todas las expresiones (estas se separan por ';')
void leer(string s, myMap<char,float> &dict){
    int inicio = 0, length = 0;
    int N = s.size();
    string expr = "";
    for (int i=0; i<N; i++){
        char c = s[i];
        if (c == ';'){
            expr = s.substr(inicio,length);
            leer_expresion(expr, dict);
            inicio += length + 1;
            length = 0;
        }
        else {
            length++;
        }
    }
}

