#pragma once
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

enum tipoToken {
    identificador,
    entero,
    real,
    String,
    TIPO,
    opSuma,
    opMul,
    opRel,
    opOR,
    opAND,
    opNOT,
    opIgualdad,
    puntoComa,
    coma,
    parent_ini,
    parent_fin,
    llave_ini,
    llave_fin,
    EQUAL,
    IF,
    WHILE,
    RETURN,
    ELSE,
    pesos
};

class Token
{
private:
    int tipo = 23;
    std::string cad;
public:
    Token(int tipo, std::string cad);
    Token();
    int GetTipo();
    std::string GetCad();
    ~Token();
};

class Lexico
{
public:
    Lexico();
    Lexico(fstream& in);
    virtual ~Lexico();
    Token lex();
    std::string cadena;

protected:

private:
    int index = 0, edo = 0;
    std::string c;
    std::string entrada;
};

