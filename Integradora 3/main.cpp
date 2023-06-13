/*
Act-Integradora-2 Estructuras de Datos Lineales
Autores:
  Claudio José González Arriaga A00232276
  Enrique Mora Navarro A01635459
Fecha: 20/04/2023
*/

#include "MaxHeap.h"
#include "Registro.h"
#include "binaryHeap.cpp"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

int k;

int main() {
  //O(1)
  ifstream entrada("bitacoraHeap.txt");
  vector<Registro> bitacora;
  Registro registro;
  while (entrada >> registro)
    bitacora.push_back(registro);
  entrada.close();

  Registro::heapSort(bitacora);

  ofstream salida("bitacora_ordenada_heap.txt");
  
  for (const Registro &reg : bitacora) {
    salida << reg << '\n';
  }
  
  salida.close();

  //O(n)
  int cont = 0;
  int recurrencia = 0;
  vector<Registro> bitacora2;
  while (cont != bitacora.size()) {
    if (bitacora[cont].getIp() == bitacora[cont + 1].getIp()) {
      recurrencia++;
    } else if (bitacora[cont].getIp() != bitacora[cont + 1].getIp()) {
      bitacora[cont].setRecurrencia(recurrencia+1);
      bitacora2.push_back(bitacora[cont]);
      recurrencia = 0;
    }
    cont++;
  }
  //O(n)
  BinaryHeap heap;
  for(int i = 0; i < bitacora2.size(); i++){
    heap.insert(&bitacora2[i], bitacora2[i].getRecurrencia());
  }
  vector<Registro*> registrosConMayorRecurrencia = heap.getRegistrosConMayorRecurrencia();

  for(int i = 0; i < registrosConMayorRecurrencia.size(); i++){
    //solo quiero imprimir la ip con su recurencia
    cout << registrosConMayorRecurrencia[i]->getIp() << " " << registrosConMayorRecurrencia[i]->getRecurrencia() << endl;
  }

  return 0;
}