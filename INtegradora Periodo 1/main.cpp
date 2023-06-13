//Actividad 1.3 Estructura de datos y algoritmos fundamentales
//28/03/2023
//Autores: Claudio José González Arriaga A00232276, Enrique Mora Navarro A01635459
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Registro.h"
using namespace std;

//Implemntacion de Binary Search. Complejidad O(log(n))
int dateSearch(vector<Registro> &v, Registro x) {
    int left = 0;
    int right = v.size() - 1;
    int pos = -1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (v[mid] <= x) {
            pos = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return pos + 1;
}

//Implementacion de Bubble sort. Complejidad: O(n^2)
void bubbleSort(vector<Registro> &v){
    for (int i = 0; i < v.size(); i++){
        for (int j = i+1; j < v.size(); j++){
            if (v[j] < v[i]) 
                swap(v[j], v[i]);
        }   
    } 
}


//Implementacion de Merge sort Complejidad O(n log n)
void mergeSort(vector<Registro> &v, int l, int r) {
    if (l >= r) {
        return;
    }
    int m = (l + r) / 2;
    mergeSort(v, l, m);
    mergeSort(v, m + 1, r);
    vector<Registro> vTemp(r - l + 1);
    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= r) { //Mezclamos los elementos
        if (v[i] < v[j]) {
            vTemp[k++] = v[i++];
        } else {
            vTemp[k++] = v[j++];
        }
    }
    while (i <= m) {
        vTemp[k++] = v[i++];
    }
    while (j <= r) {
        vTemp[k++] = v[j++];
    }
    for (k = 0, i = l; i <= r; ++i, ++k) {
        v[i] = vTemp[k];
    }
}
//Funcion auxiliar para llamar a la funcion merge sort con los argumentos para que esta funcione
void mergeSort(vector<Registro> &v) {
    mergeSort(v, 0, v.size() - 1);
}

int main(){
    ifstream entrada("bitacora-1.txt");
    vector<Registro> bitacora;
    Registro registro;
    while(entrada >> registro){
        bitacora.push_back(registro);
    }
    entrada.close();

    mergeSort(bitacora);
    ofstream salida("bitacora_ordenada_merge.txt");
    //bubbleSort(bitacora);   //El metodo de bubble funciona correctamente, para correrlo basta con eliminar los comentarios de la llamada, fue comentado por que merge es más eficiente
    //ofstream salida("bitacora_ordenada_sort.txt");
    for(int i = 0; i < bitacora.size(); i++){
        salida << bitacora[i] << endl;
    }
    salida.close();


    cout << "Ingrese el rango de fechas: " << endl;
    cout << "Ingresa la fecha inicial en formato: mm dd hh:mm:ss" << endl;
    Registro fechaInicial;
    cin >> fechaInicial;
    cout << "Ingresa la fecha final en formato: mm dd hh:mm:ss" << endl;   
    Registro fechaFinal;
    cin >> fechaFinal;

    int posInicial = dateSearch(bitacora, Registro(fechaInicial));
    int posFinal = dateSearch(bitacora, Registro(fechaFinal));

    cout << "Rango de fechas: " << endl;
    for(int i = posInicial; i < posFinal; i++){
        cout << bitacora[i] << endl;
    }

    return 0;
}