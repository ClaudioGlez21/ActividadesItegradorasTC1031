#ifndef REGISTRO_H
#define REGISTRO_H
#include "Fecha.h"
#include "Ip.h"
#include <iostream>
#include <string>
#include <vector>
//O(1)

struct IPCount {
  Ip ip;
  int count;

  IPCount(const Ip& ip, int count) : ip(ip), count(count) {}

  bool operator<(const IPCount& other) const {
    return count < other.count;
  }
};


class Registro {
public:
  int recurrencia;
   
  // Constructores
  Registro();
  Registro(Ip ip);
  Registro(Fecha fecha, Ip ip, std::string razon);

  // Getters
  Fecha getFecha();
  Ip getIp();
  std::string getRazon();

  // Setters
  void setFecha(Fecha fecha);
  void setIp(Ip ip);
  void setRazon(std::string razon);
  void setRecurrencia(int recurrencia);

  int getRecurrencia();

  // Sobrecargas
  //O(n)
  // Sobrecarga de de operador de flujo de entrada
  friend std::istream &operator>>(std::istream &, Registro &);
  // Sobrecarga de operador de flujo de salida
  friend std::ostream &operator<<(std::ostream &, const Registro &);
  // Sobrecarga del operador booleano < como funcion de la clase
  bool operator<(const Registro &) const;
  // Sobrecarga del operador booleano <= como funcion de la clase
  bool operator<=(const Registro &) const;
  // Sobrecarga del operador booleano == como funcion de la clase
  bool operator==(const Registro &) const;

  static void heapify(std::vector<Registro> &arr, int n, int i);
  static void heapSort(std::vector<Registro> &arr);

private:
  Fecha fecha;
  Ip ip;
  std::string razon;
};

#endif // REGISTRO_H