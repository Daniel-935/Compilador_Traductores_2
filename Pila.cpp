#include <iostream>

#include "Pila.h"

using namespace std;

EP::EP() { }
EP::~EP() { }

//NO TERMINAL

NT::NT() { data = ""; }
NT::~NT() { }

void NT::setData(string e) {

	data = e;
}

string NT::getNoTerminal() {

	return data;
}

int NT::getEstado() {
	return 0;
}

string NT::getTerminal() {
	return "";
}

void NT::imprimir() {
	cout << this->data << " ";
}

//TERMINAL

T::T() { data = ""; }
T::~T() { }

void T::setData(string e) {

	data = e;
}

string T::getTerminal() {

	return data;

}

int T::getEstado() {
	return 0;
}

string T::getNoTerminal() {
	return "";
}

void T::imprimir() {
	cout << this->data << " ";
}

//ESTADO

E::E() { data = 0; }
E::~E() { }

void E::setData(int e) {

	data = e;
}

int E::getEstado() {

	return data;
}

string E::getNoTerminal() {
	return "";
}

string E::getTerminal() {
	return "";
}

void E::imprimir() {
	cout << this->data << " ";
}

//NODO

Nodo::Nodo() {

	regla = 0;
	reglaString = "";
	numDeElementos = 0;
}

Nodo::~Nodo() { }

void Nodo::insertarElemento(EP* e) {

	elementos.push_back(e);
}

EP* Nodo::getElemento() {

	return elementos.back();
}

void Nodo::popElemento() {

	elementos.pop_back();
}

void Nodo::setRegla(int r) {
	regla = r;
}

int Nodo::getSize() {

	return elementos.size();
}

int Nodo::getRegla() {

	return regla;
}

void Nodo::setReglaString(string r) {

	reglaString = r;
}

string Nodo::getReglaString() {

	return reglaString;
}

void Nodo::setNumElementos(int n) {

	numDeElementos = n;
}

int Nodo::getNumElementos() {

	return numDeElementos;
}

void Nodo::printElementos() {

	EP* aux;

	while (!elementos.empty()) {

		aux = elementos.front();
		elementos.pop_front();

		/*aux = elementos.back();
		elementos.pop_back();*/

		aux->imprimir();

	}

}

//PILA

Pila::Pila() { }
Pila::~Pila() { }

void Pila::push(EP* e) {

	lista.push_back(e);
}

void Pila::pop() {

	lista.pop_back();
}

EP* Pila::top() {

	return lista.back();
}

void Pila::imprimir() {
	size_t cant = this->lista.size();
	for (auto const& i : this->lista) {
		i->imprimir();
	}
	cout << endl;
}
