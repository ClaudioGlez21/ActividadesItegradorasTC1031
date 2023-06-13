#ifndef _MAXHEAP_H_
#define _MAXHEAP_H_

#include "Registro.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Ip.h"

//O(n)
template <class T> class MaxHeap {
private:
  // contiene los elementos del heap
  std::vector<T> data;
  // capacidad maxima del heap
  int maxSize;
  // tamano actual del heap
  int currentSize;

  int parent(int k);
  int left(int k);
  int right(int k);

//O(1)
public:
  MaxHeap(int maxCapacity);
  ~MaxHeap();
  bool isEmpty();
  int getMaxCapacity();
  int getCurrentSize();

  void printHeap();
  void push(T key);
  T getTop();

  void pop();
};

template <class T> MaxHeap<T>::MaxHeap(int maxCapacity) {
  maxSize = maxCapacity;
  currentSize = 0;
  data.resize(maxSize);
}

template <class T> MaxHeap<T>::~MaxHeap() {
  maxSize = 0;
  currentSize = 0;
  data.clear();
}
//O(1)
template <class T> bool MaxHeap<T>::isEmpty() { return (currentSize <= 0); }
//O(1)
template <class T> int MaxHeap<T>::getMaxCapacity() { return maxSize; }
//O(1)
template <class T> int MaxHeap<T>::getCurrentSize() { return currentSize; }

//O(n)
template <class T> void MaxHeap<T>::printHeap() {
  std::cout << "Contenido del maxheap:" << std::endl;
  for (int i = 0; i < currentSize; i++) {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}

//O(1)
template <class T> int MaxHeap<T>::parent(int k) { return (k - 1) / 2; }
//O(1)
template <class T> int MaxHeap<T>::left(int k) { return (2 * k + 1); }
//O(1)
template <class T> int MaxHeap<T>::right(int k) { return (2 * k + 2); }

//O(log n)
template <class T> void MaxHeap<T>::push(T key) {
  if (currentSize == maxSize) {
    throw std::out_of_range("Overflow: no se puede insertar la llave");
  }
  // Insertamos la nueva llave al final del vector
  int k = currentSize;
  data[k] = key;
  currentSize++;

  // Reparar las propiedades del maxheap si son violadas
  while (k != 0 && data[parent(k)] < data[k]) {
    std::swap(data[k], data[parent(k)]);
    k = parent(k);
  }
}

//O(1)
template <class T> T MaxHeap<T>::getTop() {
  if (isEmpty()) {
    throw std::out_of_range("El heap esta vacio");
    return {};
  }
  return data[0];
}

// Referencia para el desarrollo del método:
// https://www.geeksforgeeks.org/cpp-stl-heap/ Complejidad 0(log n)
template <class T> void MaxHeap<T>::pop() {

  if (currentSize <= 0) {
    throw std::out_of_range("El heap esta vacio");
  }

  T top = data[0];
  data[0] = data[currentSize - 1];
  currentSize--;
  int k = 0;
  while (true) {
    int maxIdx = k;
    int leftIdx = left(k);
    int rightIdx = right(k);

    if (leftIdx < currentSize && data[leftIdx] > data[maxIdx]) {
      maxIdx = leftIdx;
    }

    if (rightIdx < currentSize && data[rightIdx] > data[maxIdx]) {
      maxIdx = rightIdx;
    }

    if (maxIdx == k) {
      break;
    }

    std::swap(data[k], data[maxIdx]);
    k = maxIdx;
  }
}

#endif // _MAXHEAP_H_
