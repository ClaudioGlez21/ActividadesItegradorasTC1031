#include <vector>
#include <iostream>
#include <algorithm>
#include "Registro.h"

//O(log n)
struct RegistroConRecurrencia {
  Registro* registro;
  int recurrencia;

  RegistroConRecurrencia(Registro* reg, int rec) : registro(reg), recurrencia(rec) {}
};

class BinaryHeap {
private:
  std::vector<RegistroConRecurrencia> heap;


public:
  void insert(Registro* registro, int recurrencia) {
    heap.emplace_back(registro, recurrencia);
    siftUp(heap.size() - 1); 
  }

//O(log n)
  Registro* extractMin() {
    if (heap.empty()) {
      return nullptr;
    }

    Registro* minRegistro = heap[0].registro;
    std::swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    siftDown(0);

    return minRegistro;
  }
  //O(n log n)
  std::vector<Registro*> getRegistrosConMayorRecurrencia() {
  std::vector<Registro*> registrosConMayorRecurrencia;
  if (heap.empty()) {
    return registrosConMayorRecurrencia;
  }

  std::partial_sort(heap.begin(), heap.begin() + std::min(5, static_cast<int>(heap.size())), heap.end(),
                    [](const RegistroConRecurrencia& reg1, const RegistroConRecurrencia& reg2) {
                      return reg1.recurrencia > reg2.recurrencia;
                    }); // O(k log k), where k is the number of elements being partially sorted (in this case, the minimum of 5 and the size of the heap)

  for (int i = 0; i < std::min(5, static_cast<int>(heap.size())); ++i) {
    registrosConMayorRecurrencia.push_back(heap[i].registro);
  }

  return registrosConMayorRecurrencia;
}

//O(log n)
private:
  void siftUp(int index) {
    while (index > 0) {
      int parentIndex = (index - 1) / 2;
      if (heap[index].recurrencia < heap[parentIndex].recurrencia) {
        std::swap(heap[index], heap[parentIndex]);
        index = parentIndex;
      } else {
        break;
      }
    }
  }

  //O(log n)
  void siftDown(int index) {
    int n = heap.size();
    while (index < n) {
      int leftChildIndex = 2 * index + 1;
      int rightChildIndex = 2 * index + 2;
      int smallestChildIndex = index;

      if (leftChildIndex < n && heap[leftChildIndex].recurrencia < heap[smallestChildIndex].recurrencia) {
        smallestChildIndex = leftChildIndex;
      }

      if (rightChildIndex < n && heap[rightChildIndex].recurrencia < heap[smallestChildIndex].recurrencia) {
        smallestChildIndex = rightChildIndex;
      }

      if (smallestChildIndex != index) {
        std::swap(heap[index], heap[smallestChildIndex]);
        index = smallestChildIndex;
      } else {
        break;
      }
    }
  }
};
