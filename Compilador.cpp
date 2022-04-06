// Compilador.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <list>

#include "Lexico.h"
#include "Pila.h"
#include "semantico.h"

using namespace std;

int main()
{
    fstream in;
    in.open("Archivo.txt", ios::in);
    Lexico Analizador(in);
    in.close();

    Token Tok;

    list<Token> Lista;

    //Arreglos para guardar las reglas y los elementos que elimina en la pila
    int regla[54];
    int elementPop[54];
    string reglaN[54];

    //Matriz del compilador
    int tablaComp[95][46];

    fstream file("compilador.txt", ios::in);
    int contador = 0;
    int columnas = 0;
    int filas = 0;

    //Carga reglas y tabla

    while (contador < 149) {

        //Carga las reglas y los elementos que elimina
        if (contador < 54) {

            file >> regla[contador] >> elementPop[contador] >> reglaN[contador];

        }

        //Carga la matriz

        if (contador >= 54) {

            columnas = 0;
            while (columnas < 46) {

                file >> tablaComp[filas][columnas];
                columnas++;

            }
            filas++;

        }

        contador++;
    }

    file.close();


    while (Analizador.cadena != "$")
    {
        Tok = Analizador.lex();
        Lista.push_back(Tok);
        //cout << "Token: " << T.GetCad() << " Tipo: " << T.GetTipo() << endl;
    }

    //COMIENZA SINTACTICO

    Pila elementos;
    //OBJETO SEMANTICO
    semantico analizadorSem;

    //Primer Terminal
    T* ter = new T();
    ter->setData("$");
    //Primer Estado
    E* est = new E();
    est->setData(0);

    bool cadenaValida = false;
    int valorTabla = 0;
    int topePila = 0;
    int cantidadEliminar = 0;
    int auxRegla = 0;

    EP* aux = ter;
    elementos.push(aux);
    aux = est;
    elementos.push(aux);

    while (!cadenaValida) {

        Token aux = Lista.front();

        //cout << "Token: " << aux.GetCad() << " Tipo: " << aux.GetTipo() << endl;

        topePila = elementos.top()->getEstado();
        valorTabla = tablaComp[topePila][aux.GetTipo()];

        if (valorTabla == 0) {
            cout << "Entrada No Valida" << endl;
            break;
        }

        if (valorTabla > 0) {

            T* terminal = new T();
            terminal->setData(aux.GetCad());
            E* estado = new E();
            estado->setData(valorTabla);

            EP* elementoPila = terminal;
            elementos.push(elementoPila);

            elementoPila = estado;
            elementos.push(elementoPila);

            Lista.pop_front();
        }

        if (valorTabla < 0) {

            if (valorTabla == -1) {
                cout << "Entrada Valida" << endl;
                break;
            }

            valorTabla = valorTabla + 1;
            int x = valorTabla;
            cantidadEliminar = elementPop[abs(valorTabla)];

            //CREA EL NODO
            Nodo* nodo = new Nodo();

            if (cantidadEliminar > 0) {

                for (int i = 0; i < cantidadEliminar * 2; i++) {

                    //SOLO TOMA LOS ELEMENTOS IMPORTANTES, 1 NO Y 1 SI
                    if (i % 2 != 0) {
                        nodo->insertarElemento(elementos.top());
                    }
                    elementos.pop();
                }

            }

            topePila = elementos.top()->getEstado();
            auxRegla = regla[abs(valorTabla)];
            valorTabla = tablaComp[topePila][auxRegla];

            NT* noTerminal = new NT();
            noTerminal->setData(reglaN[abs(x)]);
            //EL NODO TOMA EL NOMBRE DE LA REGLA DEL NO TERMINAL
            nodo->setReglaString(reglaN[abs(x)]);
            //EL NODO TOMA EL NUMERO DE LA REGLA
            nodo->setRegla(regla[abs(x)]);
            //EL NODO TOMA LOS ELEMENTOS QUE ELIMINA
            nodo->setNumElementos(elementPop[abs(valorTabla)]);
            //SE INSERTA EL NODO AL SEMANTICO
            analizadorSem.insertarNodo(nodo);

            E* estado = new E();
            estado->setData(valorTabla);

            EP* elementoPila;
            elementoPila = noTerminal;
            elementos.push(elementoPila);

            elementoPila = estado;
            elementos.push(elementoPila);

            elementos.imprimir();
        }

    }

    /*analizadorSem.mostrarNodos();*/
    analizadorSem.iniciaSemantico();
    analizadorSem.printTabalSimbolos();
}

