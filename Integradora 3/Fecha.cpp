#include "Fecha.h"
#include <map>

// Complejidad: O(1)  Complejidad de todo el archivo

using namespace std;

// Constructores
Fecha::Fecha() 
{
    this->mes = "";
    this->dia = "";
    this->hora = "";
}

Fecha::Fecha(string mes, string dia, string hora) 
{
    this->mes = mes;
    this->dia = dia;
    this->hora = hora;
}

// Getters
string Fecha::getMes() 
{
    return this->mes;
}

string Fecha::getDia() 
{
    return this->dia;
}

string Fecha::getHora() 
{
    return this->hora;
}

// Setters
void Fecha::setMes(string mes) 
{
    this->mes = mes;
}

void Fecha::setDia(string dia) 
{
    this->dia = dia;
}

void Fecha::setHora(string hora) 
{
    this->hora = hora;
}

// Sobrecargas
// Sobrecarga de operador de flujo de entrada
istream &operator>>(istream &entrada, Fecha &fecha) 
{
    entrada >> fecha.mes >> fecha.dia >> fecha.hora;
    fecha.setMes(fecha.mes);
    fecha.setDia(fecha.dia);
    fecha.setHora(fecha.hora);
    return entrada;
}

// Sobrecarga de operador de flujo de salida
ostream &operator<<(ostream &salida, const Fecha &fecha) 
{
    salida << fecha.mes << " " << fecha.dia << " " << fecha.hora;
    return salida;
}

// Sobrecarga del operador booleano < como funcion de la clase (función miembro)
bool Fecha::operator<(const Fecha &fecha) const 
{
    map<string, int> meses {{"Jan", 1}, {"Feb", 2}, {"Mar", 3}, 
            {"Apr", 4}, {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8}, 
            {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}};

    return make_tuple(meses[this->mes], stoi(this->dia), this->hora) <
           make_tuple(meses[fecha.mes], stoi(fecha.dia), fecha.hora);
}

// Sobrecarga del operador booleano <= como funcion de la clase
bool Fecha::operator<=(const Fecha &fecha) const 
{
    map<string, int> meses {{"Jan", 1}, {"Feb", 2}, {"Mar", 3}, 
            {"Apr", 4}, {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8}, 
            {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}};

    return make_tuple(meses[this->mes], stoi(this->dia), this->hora) <=
           make_tuple(meses[fecha.mes], stoi(fecha.dia), fecha.hora);
}