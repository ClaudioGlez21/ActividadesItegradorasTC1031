/*
Act-Integradora-5 Uso de Hash Tables
Autores:
  Claudio José González Arriaga A00232276
  Enrique Mora Navarro A01635459
Fecha: 09/06/2023
*/

#include "Graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
  std::string filename = "bitacoraGrafos.txt";
  Graph g1;
  g1.lectura(filename);

  HashTable<std::string, IPStats> ipTable;
  g1.buildHashTable(ipTable);
  std::cout << "Numero de colisiones: " << ipTable.getNumCollisions() << std::endl;

  std::string inputIP;
  std::cout << "Ingresa una IP: ";
  std::cin >> inputIP;
  g1.getIPSummary(inputIP, ipTable);

  return 0;
}