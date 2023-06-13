#include "Ip.h"
#include <string>
#include <tuple>

// Constructores
Ip::Ip() {
  this->c0 = 0;
  this->c1 = 0;
  this->c2 = 0;
  this->c3 = 0;
  this->c4 = 0;
}

Ip::Ip(int c0, int c1, int c2, int c3, int c4) {
  this->c0 = c0;
  this->c1 = c1;
  this->c2 = c2;
  this->c3 = c3;
  this->c4 = c4;
}

// Getters
int Ip::getC0() { return this->c0; }

int Ip::getC1() { return this->c1; }

int Ip::getC2() { return this->c2; }

int Ip::getC3() { return this->c3; }

int Ip::getC4() { return this->c4; }

// Setters
void Ip::setC0(int c0) { this->c0 = c0; }

void Ip::setC1(int c1) { this->c1 = c1; }

void Ip::setC2(int c2) { this->c2 = c2; }

void Ip::setC3(int c3) { this->c3 = c3; }

void Ip::setC4(int c4) { this->c4 = c4; }

// Sobrecargas
// Sobrecarga de operador de flujo de entrada
std::istream &operator>>(std::istream &entrada, Ip &ip) {
  std::string s;
  getline(entrada, s, '.');
  if (s.size())
    ip.setC0(std::stoi(s));
  getline(entrada, s, '.');
  if (s.size())
    ip.setC1(std::stoi(s));
  getline(entrada, s, '.');
  if (s.size())
    ip.setC2(std::stoi(s));
  getline(entrada, s, ':');
  if (s.size())
    ip.setC3(std::stoi(s));
  getline(entrada, s, ' ');
  if (s.size())
    ip.setC4(std::stoi(s));
  return entrada;
}

// Sobrecarga de operador de flujo de salida
std::ostream &operator<<(std::ostream &salida, const Ip &ip) {
  salida << ip.c0 << "." << ip.c1 << "." << ip.c2 << "." << ip.c3;
  return salida;
}

// Sobrecarga del operador booleano < como funcion de la clase (función miembro)
bool Ip::operator<(const Ip &ip) const {
  return std::make_tuple(this->c0, this->c1, this->c2, this->c3) <
         std::make_tuple(ip.c0, ip.c1, ip.c2, ip.c3);
}

// Sobrecarga del operador booleano <= como funcion de la clase
bool Ip::operator<=(const Ip &ip) const {
  return std::make_tuple(this->c0, this->c1, this->c2, this->c3) <=
         std::make_tuple(ip.c0, ip.c1, ip.c2, ip.c3);
}

// Sobrecarga del operador booleano == como funcion de la clase
bool Ip::operator==(const Ip &ip) const {
  return std::make_tuple(this->c0, this->c1, this->c2, this->c3) ==
         std::make_tuple(ip.c0, ip.c1, ip.c2, ip.c3);
}

//bool Ip::operator!=(const Ip &ip) const {
  //return std::make_tuple(this->c0, this->c1, this->c2, this->c3) !=
    //     std::make_tuple(ip.c0, ip.c1, ip.c2, ip.c3);
//}