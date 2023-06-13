#include "Registro.h"
#include <iostream>
#include <map>

// Constructores
Registro::Registro()
{
    this->mes = "";
    this->dia = "";
    this->hora = "";
    this->ip = "";
    this->razon = "";
}

Registro::Registro(std::string mes, std::string dia, std::string hora, std::string ip, std::string razon)
{
    this->mes = mes;
    this->dia = dia;
    this->hora = hora;
    this->ip = ip;
    this->razon = razon;
}

// Getters

std::string Registro::getMes()
{
    return this->mes;
}

std::string Registro::getDia()
{
    return this->dia;
}

std::string Registro::getHora()
{
    return this->hora;
}

std::string Registro::getIp()
{
    return this->ip;
}

std::string Registro::getRazon()
{
    return this->razon;
}

// Setters

void Registro::setMes(std::string mes)
{
    this->mes = mes;
}

void Registro::setDia(std::string dia)
{
    this->dia = dia;
}

void Registro::setHora(std::string hora)
{
    this->hora = hora;
}

void Registro::setIp(std::string ip)
{
    this->ip = ip;
}

void Registro::setRazon(std::string razon)
{
    this->razon = razon;
}

// Sobrecarga de operador de flujo de entrada
std::istream &operator>>(std::istream &entrada, Registro &registro)
{
    entrada >> registro.mes >> registro.dia >> registro.hora >> registro.ip;
    entrada.ignore(1);
    getline(entrada, registro.razon);
    registro.setMes(registro.mes);
    registro.setDia(registro.dia);
    registro.setHora(registro.hora);
    registro.setIp(registro.ip);
    registro.setRazon(registro.razon);
    return entrada;
}

// Sobrecarga de operador de flujo de salida
std::ostream &operator<<(std::ostream &salida, const Registro &registro)
{
    salida << registro.mes << " " << registro.dia << " " << registro.hora << " " << registro.ip << " " << registro.razon;
    return salida;
}

// Sobrecarga del operador booleano < como funcion de la clase (función miembro)
bool Registro::operator<(const Registro &registro) const
{
    std::map<std::string, int> meses{{"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}};

    return std::make_tuple(meses[this->mes], stoi(this->dia), this->hora) <
           std::make_tuple(meses[registro.mes], stoi(registro.dia), registro.hora);
}

// Sobrecarga del operador booleano <= como funcion de la clase
bool Registro::operator<=(const Registro &registro) const
{
    std::map<std::string, int> meses{{"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}};

    return std::make_tuple(meses[this->mes], stoi(this->dia), this->hora) <=
           std::make_tuple(meses[registro.mes], stoi(registro.dia), registro.hora);
}

// Sobrecarga del operador booleano == como funcion de la clase
bool Registro::operator==(const Registro &registro) const
{
    std::map<std::string, int> meses{{"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}};

    return std::make_tuple(meses[this->mes], stoi(this->dia), this->hora) ==
           std::make_tuple(meses[registro.mes], stoi(registro.dia), registro.hora);
}