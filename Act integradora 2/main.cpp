/*
Act-Integradora-2 Estructuras de Datos Lineales
Autores:
  Claudio José González Arriaga A00232276
  Enrique Mora Navarro A01635459
Fecha: 20/04/2023
*/

#include <iostream>
#include <fstream>
#include "DLinkedList.h"
using namespace std;
int numeroBusqueda = 1;
int main()
{
  ifstream entrada("bitacora_1.2.txt");
  DLinkedList<Registro> bitacora;
  Registro registro;
  while (entrada >> registro)
  {
    bitacora.addLast(registro);
  }
  entrada.close();

  bitacora.mergeSort();
  ofstream salida("bitacora_ordenada_merge.txt");
  salida << bitacora;
  salida.close();

  cout << "Ingrese el rango de fechas: " << endl;
  cout << "Ingresa la fecha inicial en formato: mm dd hh:mm:ss" << endl;
  Registro fechaInicial;
  cin >> fechaInicial;
  cout << "Ingresa la fecha final en formato: mm dd hh:mm:ss" << endl;
  Registro fechaFinal;
  cin >> fechaFinal;

  int posInicial = bitacora.dateSearch(Registro(fechaInicial));
  int posFinal = bitacora.dateSearch(Registro(fechaFinal));


  cout << "Resultados de busqueda:" << endl;
  salida.open("resultado_busqueda.txt");
  bitacora.busqueda(salida, Registro(fechaInicial), Registro(fechaFinal));
  salida.close();
  cout << endl;

  return 0;
}
