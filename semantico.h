#pragma once
#include <iostream>
#include <string>
#include <list>

#include "Pila.h"

using namespace std;

class Simbolo {

private:

	//1 - PARA VARIABLE, 2 -  PARA FUNCION
	int id;
	string nombre;
	string tipo;
	string ambito;

public:

	Simbolo();
	~Simbolo();

	void setId(int i);
	void setNombre(string n);
	void setTipo(string t);
	void setAmbito(string a);

	int getId();
	string getNombre();
	string getTipo();
	string getAmbito();

};


class semantico
{
private:

	list<Nodo*> pilaNodos;
	list<Simbolo*> listaSimbolos;
	list<string> listaErrores;

public:

	semantico();
	~semantico();

	void insertarNodo(Nodo* n);
	Nodo* top();
	void pop();

	void iniciaSemantico();

	bool buscaSimbolo(string n, string a);

	void printTabalSimbolos();
	void mostrarNodos();
};

