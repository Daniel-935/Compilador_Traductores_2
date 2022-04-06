#include <iostream>
#include <limits>
#include <fstream>

#include "Lexico.h"

Token::Token(int tipo, std::string cad)
{
    this->tipo = tipo;
    this->cad = cad;
}

Token::Token()
{
    this->tipo = 23;
}

Token::~Token()
{
}

std::string Token::GetCad()
{
    return this->cad;
}

int Token::GetTipo()
{
    return this->tipo;
}

//LEXICO

Lexico::Lexico()
{
    //ctor
}

Lexico::Lexico(fstream& in)
{
    // Posicin inicial del fichero
    const size_t posicionInicial = in.tellg();

    // Descartamos todos los caracteres del fichero
    in.ignore(std::numeric_limits<std::streamsize>::max());

    // Nmero de caracteres descartados
    // nota que coincide con la posici�n final del fichero
    const size_t posicionFinal = in.gcount();

    // Volvemos al inicio (el flag EOF se reinicia)
    in.seekg(posicionInicial);

    this->entrada.resize(posicionFinal);
    in.read(&this->entrada[0], this->entrada.size());
    //cout << entrada.length();
}

Token Lexico::lex()
{
    cadena = "";
    edo = 0;
    bool continua = true;


    if (index >= entrada.length())
    {
        cadena = "$";
        Token t(pesos, cadena);
        return t;
    }

    while (index < this->entrada.length() && continua == true)
    {
        c = entrada[index];

        if ((c[0] == ' ' || c[0] == '\n') && edo != 4)
        {
            index += 1;
            break;
        }

        if (edo == 0)
        {
            if (c[0] >= '0' && c[0] <= '9')
            {
                cadena += c;
                edo = 1;
            }

            else if (c[0] == '"')
            {
                cadena += c;
                edo = 4;
            }

            else if (c[0] == '+' || c[0] == '-')
            {
                cadena += c;
                edo = 6;
            }

            else if (c[0] == '*' || c[0] == '/')
            {
                cadena += c;
                edo = 7;
            }

            else if (c[0] == '=')
            {
                cadena += c;
                edo = 8;
            }

            else if (c[0] == '<' || c[0] == '>')
            {
                edo = 9;
                cadena += c;
            }

            else if (c[0] == '!')
            {
                edo = 10;
                cadena += c;
            }

            else if (c[0] == '&')
            {
                edo = 12;
                cadena += c;
            }

            else if (c[0] == '|')
            {
                edo = 14;
                cadena += c;
            }

            else if (c[0] == ';')
            {
                edo = 16;
                cadena += c;
            }

            else if (c[0] == ',')
            {
                edo = 17;
                cadena += c;
            }

            else if (c[0] == '(')
            {
                edo = 18;
                cadena += c;
            }

            else if (c[0] == ')')
            {
                edo = 19;
                cadena += c;
            }

            else if (c[0] == '{')
            {
                edo = 20;
                cadena += c;
            }

            else if (c[0] == '}')
            {
                edo = 21;
                cadena += c;
            }

            else if ((c[0] >= 'a' && c[0] <= 'z') || (c[0] >= 'A' && c[0] <= 'Z') || c[0] == '_')
            {
                cadena += c;
                edo = 100;
            }

        }

        else if (edo == 1)
        {
            if (c[0] >= '0' && c[0] <= '9')
            {
                cadena += c;
                edo = 1;
            }
            else if (c[0] == '.')
            {
                cadena += c;
                edo = 2;
            }

            else
            {
                continua = false;
                index -= 1;
            }
        }

        else if (edo == 2)
        {
            if (c[0] >= '0' && c[0] <= '9')
            {
                cadena += c;
                edo = 3;
            }
        }

        else if (edo == 3)
        {
            if (c[0] >= '0' && c[0] <= '9')
            {
                cadena += c;
                edo = 3;
            }
        }

        else if (edo == 4)
        {
            if (c[0] == '"') {
                edo = 5;
                cadena += c;
                continua = false;
            }
            else if (c[0] != '"') {
                edo = 4;
                cadena += c;
            }
            else {
                continua = false;
                index -= 1;
            }
        }

        else if (edo == 6)
        {
            continua = false;
            index -= 1;
        }

        else if (edo == 7) {
            continua = false;
            index -= 1;
        }

        else if (edo == 8 || edo == 9 || edo == 10) {
            if (c[0] == '=') {
                edo = 11;
                cadena += c;
            }
            else {
                continua = false;
                index -= 1;
            }
        }

        else if (edo == 11) {
            continua = false;
            index -= 1;
        }

        else if (edo == 12) {
            if (c[0] == '&') {
                edo = 13;
                cadena += c;
            }
            else {
                continua = false;
                index -= 1;
            }
        }

        else if (edo == 13)
        {
            continua = false;
            index -= 1;
        }

        else if (edo == 14) {
            if (c[0] == '|')
            {
                edo = 15;
                cadena += c;
            }
            else {
                continua = false;
                index -= 1;
            }
        }

        else if (edo == 15) {
            continua = false;
            index -= 1;
        }

        else if (edo == 16)
        {
            continua = false;
            index -= 1;
        }

        else if (edo == 17)
        {
            continua = false;
            index -= 1;
        }

        else if (edo == 18) {
            continua = false;
            index -= 1;
        }

        else if (edo == 19) {
            continua = false;
            index -= 1;
        }

        else if (edo == 20) {
            continua = false;
            index -= 1;
        }

        else if (edo == 21)
        {
            continua = false;
            index -= 1;
        }


        else if (edo == 100)
        {
            if ((c[0] >= 'a' && c[0] <= 'z') || (c[0] >= 'A' && c[0] <= 'Z') || c[0] == '_' || (c[0] >= '0' && c[0] <= '9'))
            {
                cadena += c;
                edo = 100;
            }
            else
            {
                continua = false;
                index -= 1;
            }
        }
        index++;
    }
    //index++;

    //MODIFICACION MIA, ASIGNA TIPO
    int tipo;

    switch (edo) {

    case 1:
    {
        tipo = entero;
        break;
    }
    case 3:
    {
        tipo = real;
        break;
    }

    case 5:
    {
        tipo = String;
        break;
    }
    case 6:
    {
        tipo = opSuma;
        break;
    }
    case 7:
    {
        tipo = opMul;
        break;
    }
    case 8:
    {
        tipo = EQUAL;
        break;
    }
    case 9:
    {
        tipo = opRel;
        break;
    }
    case 10:
    {
        tipo = opNOT;
        break;
    }
    case 11:
    {
        tipo = opRel;
        break;
    }
    case 13:
    {
        tipo = opAND;
        break;
    }

    case 15:
    {
        tipo = opOR;
        break;
    }

    case 16:
    {
        tipo = puntoComa;
        break;
    }

    case 17:
    {
        tipo = coma;
        break;
    }

    case 18:
    {
        tipo = parent_ini;
        break;
    }

    case 19:
    {
        tipo = parent_fin;
        break;
    }

    case 20:
    {
        tipo = llave_ini;
        break;
    }

    case 21:
    {
        tipo = llave_fin;
        break;
    }

    case 100:
    {
        if (cadena == "if") {
            tipo = IF;
            break;
        }

        if (cadena == "else") {
            tipo = ELSE;
            break;
        }

        if (cadena == "while") {
            tipo = WHILE;
            break;
        }
        if (cadena == "return") {
            tipo = RETURN;
            break;
        }

        if (cadena == "int" || cadena == "void" || cadena == "float") {
            tipo = TIPO;
            break;
        }

        else {

            tipo = identificador;
            break;
        }

    }

    }

    //cout << "INDEX:" << index << " Token:" << cadena << " EDO:" << edo << endl;
    //cout << "Token: " << cadena << " Tipo: " << tipo << endl;

    Token T(tipo, cadena);
    return T;

}

Lexico::~Lexico()
{
    //dtor
}
