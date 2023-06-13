/*
Act-Integradora-2 Estructuras de Datos Lineales
Autores:
  Claudio José González Arriaga A00232276
  Enrique Mora Navarro A01635459
Fecha: 20/04/2023
*/

#include "Graph.h"
#include "Registro.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
  std::string filename = "bitacoraGrafos.txt";
  Graph g1;

  g1.lectura(filename);
  g1.grados();
  g1.topGrados();

  std::string bootMaster = g1.findBootMasterIP();
  std::cout << "IP con el Boot Master: " << bootMaster << std::endl;

  int bootMasterNode = g1.findBootMasterNode();
  g1.dijkstraAlgorithm(bootMasterNode);

  std::string ipMenor = g1.getLeastEffortIP(bootMasterNode);
  std::cout << "IP que requiere menos esfuerzo para que el bootmaster la ataque: " << ipMenor << std::endl;
}