#pragma once
#include <iostream>
#include <string>
#include <list>

using namespace std;

//ELEMENTO PILA
class EP {

private:

public:

	EP();
	~EP();

	virtual int getEstado() = 0;
	virtual string getTerminal() = 0;
	virtual string getNoTerminal() = 0;
	virtual void imprimir() = 0;

};

//NO TERMINAL
class NT : public EP {

private:

	string data;

public:

	NT();
	~NT();

	void setData(string e);
	int getEstado();
	string getTerminal();
	string getNoTerminal();

	void imprimir();

};

//TERMINAL

class T :public EP {

private:

	string data;

public:

	T();
	~T();

	void setData(string e);
	int getEstado();
	string getNoTerminal();
	string getTerminal();

	void imprimir();

};

//ESTADO

class E :public EP {

private:

	int data;

public:

	E();
	~E();

	void setData(int e);
	int getEstado();
	string getNoTerminal();
	string getTerminal();

	void imprimir();

};

//NODO

class Nodo {

private:

	list<EP*> elementos;
	int regla;
	string reglaString;
	int numDeElementos;

public:

	Nodo();
	~Nodo();

	void insertarElemento(EP* e);
	EP* getElemento();
	void popElemento();
	void setRegla(int r);
	int getRegla();
	int getSize();

	void setReglaString(string r);
	string getReglaString();

	void setNumElementos(int n);
	int getNumElementos();

	void printElementos();

};

class Pila
{
private:

	list<EP*> lista;

public:

	Pila();
	~Pila();

	void push(EP* e);
	void pop();
	EP* top();

	void imprimir();
};

