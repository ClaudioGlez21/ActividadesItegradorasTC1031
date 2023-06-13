#ifndef IP_H
#define IP_H
#include <iostream>

//O(1)

class Ip {
public:
  // Constructores
  Ip();
  Ip(int c0, int c1, int c2, int c3, int c4);

  // Getters
  int getC0();
  int getC1();
  int getC2();
  int getC3();
  int getC4();

  // Setters
  void setC0(int c0);
  void setC1(int c1);
  void setC2(int c2);
  void setC3(int c3);
  void setC4(int c4);

  // Sobrecargas
  // Sobrecarga de de operador de flujo de entrada
  friend std::istream &operator>>(std::istream &, Ip &);
  // Sobrecarga de operador de flujo de salida
  friend std::ostream &operator<<(std::ostream &, const Ip &);
  // Sobrecarga del operador booleano < como funcion de la clase
  bool operator<(const Ip &) const;
  // Sobrecarga del operador booleano <= como funcion de la clase
  bool operator<=(const Ip &) const;
  // Sobrecarga del operador booleano == como funcion de la clase
  bool operator==(const Ip &) const;

  bool operator!=(const Ip &) const;

private:
  int c0;
  int c1;
  int c2;
  int c3;
  int c4;
};

#endif // IP_H