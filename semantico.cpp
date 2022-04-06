#include <iostream>

#include "semantico.h"

using namespace std;

semantico::semantico() { }

semantico::~semantico() { }

void semantico::insertarNodo(Nodo* n) {

	pilaNodos.push_back(n);
}

Nodo* semantico::top() {

	return pilaNodos.back();
}

void semantico::pop() {

	pilaNodos.pop_back();
}

bool semantico::buscaSimbolo(string nombre, string ambito) {

	Simbolo* aux;

	for (list<Simbolo*>::iterator it = listaSimbolos.begin(); it != listaSimbolos.end(); ++it) {

		aux = *it;
		if (aux->getNombre() == nombre && aux->getAmbito() == ambito) {

			return true;
		}
	}
	return false;
}


void semantico::iniciaSemantico() {

	string ambitoActual = "Global";
	Nodo* aux;
	EP* auxEP;
	int regla = 0;

	while (!pilaNodos.empty())
	{
		//TOMA EL PRIMER NODO DE LA PILA
		aux = pilaNodos.back();
		pilaNodos.pop_back();
		//TOMA EL VALOR DE LA REGLA
		regla = aux->getRegla();

		//EVALUA LA ACCION A REALIZAR
		switch (regla)
		{

			//DEF FUNCION
		case 29:
		{
			Simbolo* newSimbolo = new Simbolo();
			//DELCARA EL ID Y AMBITO
			newSimbolo->setId(2);
			newSimbolo->setAmbito(ambitoActual);

			//TOMA EL TERMINAL Y DELCARA TIPO QUE REGRESA
			auxEP = aux->getElemento();
			aux->popElemento();
			newSimbolo->setTipo(auxEP->getTerminal());

			//DELCARA EL NUEVO AMBITO Y NOMBRE
			auxEP = aux->getElemento();
			aux->popElemento();
			ambitoActual = auxEP->getTerminal();
			newSimbolo->setNombre(auxEP->getTerminal());

			if (buscaSimbolo(newSimbolo->getNombre(), newSimbolo->getAmbito())) {
				//AGREGA UN ERROR
				string error = "La funcion: '" + newSimbolo->getNombre() + "' ya ha sido declarada anteriormente. Ambito: " + newSimbolo->getAmbito();
				listaErrores.push_back(error);
			}
			else {
				//AGREGA EL SIMBOLO A LA TABLA DE SIMBOLOS
				listaSimbolos.push_back(newSimbolo);
			}

			break;
		}
		//DEF VARIABLE
		case 27:
		{

			if (aux->getSize() == 4) {

				Simbolo* newVariable = new Simbolo();
				newVariable->setId(1);

				//DECLARA EL AMBITO
				newVariable->setAmbito(ambitoActual);

				//TOMA EL TERMINAL
				auxEP = aux->getElemento();
				aux->popElemento();
				//DECLARA TIPO
				newVariable->setTipo(auxEP->getTerminal());
				//DECLARA EL NOMBRE
				auxEP = aux->getElemento();
				aux->popElemento();
				newVariable->setNombre(auxEP->getTerminal());

				if (buscaSimbolo(newVariable->getNombre(), newVariable->getAmbito())) {
					//AGREGA UN ERROR
					string error = "La variable: '" + newVariable->getNombre() + "' ya ha sido declarada anteriormente. Ambito: " + newVariable->getAmbito();
					listaErrores.push_back(error);

				}
				else {

					//INSERTA EN LA TABLA DE SIMBOLOS
					listaSimbolos.push_back(newVariable);
				}
			}

			break;
		}
		//PARAMETROS
		case 31:
		{
			if (aux->getSize() == 4) {

				Simbolo* newVariable = new Simbolo();
				newVariable->setId(1);

				//DECLARA EL AMBITO
				newVariable->setAmbito(ambitoActual);

				//HACE UN POP PARA ELIMINAR LA COMA Y TOMA EL SIGUIENTE TERMINAL
				aux->popElemento();
				auxEP = aux->getElemento();
				aux->popElemento();
				//DECLARA TIPO
				newVariable->setTipo(auxEP->getTerminal());
				//DECLARA EL NOMBRE
				auxEP = aux->getElemento();
				aux->popElemento();
				newVariable->setNombre(auxEP->getTerminal());

				if (buscaSimbolo(newVariable->getNombre(), newVariable->getAmbito())) {
					//AGREGA UN ERROR
					string error = "La variable: '" + newVariable->getNombre() + "' ya ha sido declarada anteriormente. Ambito: " + newVariable->getAmbito();
					listaErrores.push_back(error);

				}
				else {

					//INSERTA EN LA TABLA DE SIMBOLOS
					listaSimbolos.push_back(newVariable);
				}

			}
			break;
		}
		//PARAMETROS
		case 30:
		{
			if (aux->getSize() == 3) {

				Simbolo* newVariable = new Simbolo();
				newVariable->setId(1);

				//DECLARA EL AMBITO
				newVariable->setAmbito(ambitoActual);

				//TOMA EL TERMINAL
				auxEP = aux->getElemento();
				aux->popElemento();
				//DECLARA TIPO
				newVariable->setTipo(auxEP->getTerminal());
				//DECLARA EL NOMBRE
				auxEP = aux->getElemento();
				aux->popElemento();
				newVariable->setNombre(auxEP->getTerminal());

				if (buscaSimbolo(newVariable->getNombre(), newVariable->getAmbito())) {
					//AGREGA UN ERROR
					string error = "La variable: '" + newVariable->getNombre() + "' ya ha sido declarada anteriormente. Ambito: " + newVariable->getAmbito();
					listaErrores.push_back(error);

				}
				else {

					//INSERTA EN LA TABLA DE SIMBOLOS
					listaSimbolos.push_back(newVariable);
				}

			}
			break;
		}
		}
	}

}

void semantico::printTabalSimbolos() {

	cout << "*************** TABLA DE SIMBOLOS *********************" << endl;
	Simbolo* aux;

	while (!listaSimbolos.empty()) {

		aux = listaSimbolos.front();
		listaSimbolos.pop_front();
		//IMPRIME CONFORME A ID
		switch (aux->getId())
		{
		case 1:
		{
			cout << "Simbolo: Variable - Identificador: " << aux->getNombre() << " - Tipo: " << aux->getTipo() << " - Ambito: " << aux->getAmbito() << endl;
			break;
		}
		case 2:
		{
			cout << "Simbolo: Funcion - Identificador: " << aux->getNombre() << " - Regresa: " << aux->getTipo() << " - Ambito: " << aux->getAmbito() << endl;
			break;
		}
		}
	}

	cout << endl << "*************** TABLA DE ERRORES *********************" << endl;
	if (listaErrores.empty()) {
		cout << "No se genero ningun error durante el analisis" << endl;
	}
	else {

		for (list<string>::iterator it = listaErrores.begin(); it != listaErrores.end(); ++it) {

			cout << *it << endl;
		}

	}
}

void semantico::mostrarNodos() {

	cout << "*************** PILA DE NODOS *********************" << endl;
	Nodo* aux;

	cout << "Tamanio de la pila: " << pilaNodos.size() << endl;
	while (!pilaNodos.empty()) {

		aux = pilaNodos.back();
		pilaNodos.pop_back();
		cout << aux->getReglaString() << aux->getRegla() << endl;
		aux->printElementos();
		cout << endl << endl;
	}

}

//SIMBOLO

Simbolo::Simbolo() {

	id = 0;
	nombre = "";
	tipo = "";
	ambito = "";
}

Simbolo::~Simbolo() { }

void Simbolo::setId(int i) {

	id = i;
}

void Simbolo::setNombre(string n) {

	nombre = n;
}

void Simbolo::setTipo(string t) {

	tipo = t;
}

void Simbolo::setAmbito(string a) {

	ambito = a;
}

int Simbolo::getId() {

	return id;
}

string Simbolo::getNombre() {

	return nombre;
}

string Simbolo::getTipo() {

	return tipo;
}

string Simbolo::getAmbito() {

	return ambito;
}