#include "Registro.h"

// Constructores
Registro::Registro() { this->razon = ""; }

Registro::Registro(Ip ip) {
  this->ip = ip;
  this->razon = "";
}

Registro::Registro(Fecha fecha, Ip ip, std::string razon) {
  this->fecha = fecha;
  this->ip = ip;
  this->razon = razon;
}

void Registro::setRecurrencia(int recurrencia){
  this->recurrencia = recurrencia;
}
// Getters
Fecha Registro::getFecha() { return this->fecha; }

Ip Registro::getIp() { return this->ip; }

std::string Registro::getRazon() { return this->razon; }

int Registro::getRecurrencia(){ return this->recurrencia; } 

// Setters
void Registro::setFecha(Fecha fecha) { this->fecha = fecha; }

void Registro::setIp(Ip ip) { this->ip = ip; }

void Registro::setRazon(std::string razon) { this->razon = razon; }

// Sobrecargas
// Sobrecarga de operador de flujo de entrada
std::istream &operator>>(std::istream &entrada, Registro &registro) {
  entrada >> registro.fecha;
  entrada.ignore(1);
  entrada >> registro.ip;
  getline(entrada, registro.razon, '\n');
  return entrada;
}

// Sobrecarga de operador de flujo de salida
std::ostream &operator<<(std::ostream &salida, const Registro &registro) {
  salida << registro.fecha << " " << registro.ip << " " << registro.razon;
  return salida;
}

// Se puede cambiar por ip o fecha

// Sobrecarga del operador booleano < como funcion de la clase (función miembro)
bool Registro::operator<(const Registro &registro) const {
  return this->ip < registro.ip;
}

// Sobrecarga del operador booleano <= como funcion de la clase
bool Registro::operator<=(const Registro &registro) const {
  return this->ip <= registro.ip;
}

// Sobrecarga del operador booleano == como funcion de la clase
bool Registro::operator==(const Registro &registro) const {
  return this->ip == registro.ip;
}

void Registro::heapify(std::vector<Registro> &arr, int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && arr[left] < arr[largest])
    largest = left;

  if (right < n && arr[right] < arr[largest])
    largest = right;

  if (largest != i) {
    std::swap(arr[i], arr[largest]);
    heapify(arr, n, largest);
  }
}

// Complejidad: O(n log n)
void Registro::heapSort(std::vector<Registro> &arr) {
  int n = arr.size();

  // Build max heap
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  // Heap sort
  for (int i = n - 1; i > 0; i--) {
    std::swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}