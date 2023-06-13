#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "DLLNode.h"
#include <iostream>
#include <stdexcept>
#include "Registro.h"
using namespace std;

template <class T>
class DLinkedList
{
private:
  DLLNode<T> *head;
  DLLNode<T> *tail;
  int numElements;

  DLLNode<T> *partition(DLLNode<T> *low, DLLNode<T> *high);
  void quickSort(DLLNode<T> *low, DLLNode<T> *high);

  DLLNode<T> *mitad(DLLNode<T> *head);
  DLLNode<T> *merge(DLLNode<T> *h1, DLLNode<T> *h2);
  DLLNode<T> *mergeSort(DLLNode<T> *head);

public:
  DLinkedList();
  ~DLinkedList();
  int getNumElements();
  void printList();
  void printListReversed();
  void addFirst(T value);
  void addLast(T value);
  bool deleteData(T value);
  bool deleteAt(int position);
  T getData(int position);
  void updateData(T value, T newValue);
  void updateAt(int position, T value);
  int findData(T value);
  void invert();
  void sort();
  DLinkedList<T> getReversedSublist(int ini, int fin);

  void mergeSort();
  int dateSearch(T value);
  void busqueda(std::ostream &, Registro l, Registro r);
  template <class U>
  friend std::ostream &operator<<(std::ostream &, const DLinkedList<U> &);
};

// Complejidad O(1)
template <class T>
DLinkedList<T>::DLinkedList()
{
  // std::cout << "---> Creando una lista doblemente ligada vacia: " << this <<
  // std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Complejidad O(n)
template <class T>
DLinkedList<T>::~DLinkedList()
{
  // std::cout << "---> Liberando memoria de la lista doblemente ligada: " <<
  // this << std::endl;
  DLLNode<T> *p, *q;
  p = head;
  while (p != nullptr)
  {
    q = p->next;
    delete p;
    p = q;
  }
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Complejidad O(1)
template <class T>
int DLinkedList<T>::getNumElements() { return numElements; }

// Complejidad O(n)
template <class T>
void DLinkedList<T>::printList()
{
  DLLNode<T> *ptr = head;
  while (ptr != nullptr)
  {
    std::cout << ptr->data << " ";
    ptr = ptr->next;
  }
  std::cout << std::endl;
}

// Complejidad O(n)
template <class T>
void DLinkedList<T>::printListReversed()
{
  DLLNode<T> *ptr = tail;
  while (ptr != nullptr)
  {
    std::cout << ptr->data << " ";
    ptr = ptr->prev;
  }
  std::cout << std::endl;
}

// Complejidad O(1)
template <class T>
void DLinkedList<T>::addFirst(T value)
{
  // 1. crear un newNode
  DLLNode<T> *newNode = new DLLNode<T>(value);
  // Si la lista esta vacia
  if (head == nullptr && tail == nullptr)
  {
    head = newNode;
    tail = newNode;
  }
  else
  {
    // 2. apuntar newNode->next a donde esta head
    newNode->next = head;
    // 3. apuntar head->prev al newNode
    head->prev = newNode;
    // 3. Actualizar head para apuntar al newNode
    head = newNode;
  }
  numElements++;
}

// Complejidad O(1)
template <class T>
void DLinkedList<T>::addLast(T value)
{
  // La lista esta vacia
  if (head == nullptr && tail == nullptr)
    addFirst(value);
  else
  {
    // 1. crear un newNode
    DLLNode<T> *newNode = new DLLNode<T>(value);
    // 2. apuntar tail->next a newNode
    tail->next = newNode;
    newNode->prev = tail;
    // 3. actualizar tail para apuntar al newNode
    tail = newNode;
    numElements++;
  }
}

// Complejidad O(n)
template <class T>
bool DLinkedList<T>::deleteData(T value)
{
  // La lista esta vacia
  if (head == nullptr && tail == nullptr)
    return false;
  else
  {
    DLLNode<T> *p = head;
    DLLNode<T> *previous = nullptr;
    while (p != nullptr && p->data != value)
    {
      previous = p;
      p = p->next;
    }
    // si no existe value en la lista
    if (p == nullptr)
      return false;
    // si debo borrar el primer elemento de la lista
    if (p != nullptr && p == head)
    {
      head = p->next;
      if (head == nullptr) // habia solo un nodo en la lista
        tail = nullptr;
      else
        head->prev = nullptr;
    }
    else if (p->next == nullptr)
    { // debo borrar el ultimo nodo
      previous->next = nullptr;
      tail = previous;
    }
    else
    { // debo borrar cualquier otro nodo
      previous->next = p->next;
      p->next->prev = previous;
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
}

// Complejidad O(n)
template <class T>
bool DLinkedList<T>::deleteAt(int position)
{
  if (position < 0 || position >= numElements)
  {
    throw std::out_of_range("Indice fuera de rango");
  }
  else if (position == 0)
  {
    DLLNode<T> *p = head;
    // si la lista contiene un solo nodo
    if (head != nullptr && head->next == nullptr)
    {
      head = nullptr;
      tail = nullptr;
    }
    else
    {
      head = p->next;
      head->prev = nullptr; // cambio
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
  else
  { // borrar cualquier otro elemento de la lista
    DLLNode<T> *p = head;
    DLLNode<T> *previous = nullptr;
    int index = 0;
    // buscar el indice del elemento a borrar
    while (index != position)
    {
      previous = p;
      p = p->next;
      index++;
    }
    // si debo borrar el ultimo elemento
    if (p->next == nullptr)
    {
      previous->next = nullptr;
      tail = previous;
    }
    else
    { // borrar cualquier otro nodo
      previous->next = p->next;
      p->next->prev = previous; // cambio
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
}

// Complejidad O(n)
template <class T>
T DLinkedList<T>::getData(int position)
{
  if (position < 0 || position >= numElements)
  {
    throw std::out_of_range("Indice fuera de rango");
  }
  else
  {
    if (position == 0)
    { // si es el primero de la lista
      return head->data;
    }
    // debemos buscar el elemento
    DLLNode<T> *p = head;
    int index = 0;
    // buscar el indice del elemento a borrar
    while (p != nullptr)
    {
      if (index == position)
        return p->data;
      p = p->next;
      index++;
    }
    return {};
  }
}

// Complejidad 0(n)
template <class T>
void DLinkedList<T>::updateAt(int position, T Value)
{
  if (position < 0 || position >= numElements)
  {
    throw std::out_of_range("Indice fuera de rango");
  }
  else
  {
    DLLNode<T> *p = head->next;
    int index = 0;
    while (index != position)
    {
      p = p->next;
      index++;
    }
    p->data = Value;
  }
}

// Complejidad 0(n)
template <class T>
void DLinkedList<T>::invert()
{
  if (head == nullptr || head->next == nullptr)
  {
    return;
  }
  DLLNode<T> *current = head;
  DLLNode<T> *temp = nullptr;

  while (current != nullptr)
  {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }

  if (temp != nullptr)
  {
    head = temp->prev;
  }
}

// Complejidad O(n log n)
// sort (usando quicksort)
// algoritmo basado del codigo de:
// (https://www.geeksforgeeks.org/quicksort-for-linked-list/)
template <class T>
void DLinkedList<T>::sort()
{
  if (head == nullptr || head->next == nullptr)
  {
    return;
  }

  quickSort(head, tail);
}

template <class T>
void DLinkedList<T>::quickSort(DLLNode<T> *low, DLLNode<T> *high)
{
  if (high != nullptr && low != high && low != high->next)
  {
    DLLNode<T> *pivot = partition(low, high);
    quickSort(low, pivot->prev);
    quickSort(pivot->next, high);
  }
}

template <class T>
DLLNode<T> *DLinkedList<T>::partition(DLLNode<T> *low, DLLNode<T> *high)
{
  T pivotValue = high->data;
  DLLNode<T> *i = low->prev;

  for (DLLNode<T> *j = low; j != high; j = j->next)
  {
    if (j->data < pivotValue)
    {
      i = (i == nullptr) ? low : i->next;
      std::swap(i->data, j->data);
    }
  }
  i = (i == nullptr) ? low : i->next;
  std::swap(i->data, high->data);
  return i;
}

// Complejidad 0(n)
// Algoritmo basado del codigo de:
// https://www.geeksforgeeks.org/reverse-sublist-linked-list/
template <class T>
DLinkedList<T> DLinkedList<T>::getReversedSublist(int ini, int fin)
{
  if (ini < 0 || ini >= numElements || fin < 0 || fin >= numElements ||
      ini > fin)
  {
    throw std::out_of_range("Indices fuera de rango");
  }
  DLinkedList<T> reversedList;
  DLLNode<T> *currentNode = head;
  int currentIndex = 0;
  while (currentIndex != ini)
  {
    currentNode = currentNode->next;
    currentIndex++;
  }
  while (currentIndex <= fin)
  {
    reversedList.addFirst(currentNode->data);
    currentNode = currentNode->next;
    currentIndex++;
  }

  return reversedList;
}

// Complejidad O(n)
template <class T>
int DLinkedList<T>::findData(T value)
{
  int index = 0;
  DLLNode<T> *current = head;
  while (current != nullptr)
  {
    if (current->data == value)
    {
      return index;
    }
    current = current->next;
    index++;
  }
  return -1;
}

// Complejidad O(n)
template <class T>
void DLinkedList<T>::updateData(T value, T newValue)
{
  DLLNode<T> *current = head;
  while (current != nullptr)
  {
    if (current->data == value)
    { // Si encuentra el elemento a actualizar
      current->data =
          newValue;    // Actualiza el valor del elemento con el nuevo valor
      newValue = true; // Indica que se actualizó el elemento
      break;
    }
    current = current->next; // Avanza al siguiente nodo
  }

  if (!newValue)
  { // Si no se actualizó ningún elemento
    throw std::out_of_range(
        "Indice fuera de rango"); // Lanza una excepción de fuera de rango
  }
}

// Complejidad O(n + m)
template <class T>
DLLNode<T> *DLinkedList<T>::merge(DLLNode<T> *h1, DLLNode<T> *h2)
{
  if (h1 == nullptr)
  {
    return h2;
  }
  if (h2 == nullptr)
  {
    return h1;
  }
  DLLNode<T> *head;
  DLLNode<T> *tail;
  if (h1->data <= h2->data)
  {
    head = h1;
    tail = h1;
    h1 = h1->next;
  }
  else
  {
    head = h2;
    tail = h2;
    h2 = h2->next;
  }
  while (h1 != nullptr && h2 != nullptr)
  {
    if (h1->data <= h2->data)
    {
      tail->next = h1;
      tail = h1;
      h1 = h1->next;
    }
    else
    {
      tail->next = h2;
      tail = h2;
      h2 = h2->next;
    }
  }
  if (h1 == nullptr)
  {
    tail->next = h2;
  }
  else
  {
    tail->next = h1;
  }
  return head;
}

// Complejidad  0(n)
template <class T>
DLLNode<T> *DLinkedList<T>::mitad(DLLNode<T> *head)
{
  DLLNode<T> *tmp = head;
  int tam = 1;
  while (tmp->next != nullptr)
  {
    tmp = tmp->next;
    ++tam;
  }
  tmp = head;
  for (int i = 0; i < tam / 2 - 1; ++i)
  {
    tmp = tmp->next;
  }
  return tmp;
}

// Complejidad: O(n * log(n))
template <class T>
DLLNode<T> *DLinkedList<T>::mergeSort(DLLNode<T> *head)
{
  if (head == nullptr || head->next == nullptr)
  {
    return head;
  }
  DLLNode<T> *h1 = head;
  DLLNode<T> *h1f = mitad(h1);
  DLLNode<T> *h2 = h1f->next;
  h1f->next = nullptr;
  return merge(mergeSort(h1), mergeSort(h2));
}

// Complejidad: O(n * log(n))
template <class T>
void DLinkedList<T>::mergeSort()
{
  this->head = this->mergeSort(this->head);
}

// Complejidad O(log n)
template <class T>
int DLinkedList<T>::dateSearch(T value)
{
  int left = 0;
  int right = numElements - 1;
  int middle = (left + right) / 2;

  DLLNode<T> *current = nullptr;

  if (head == nullptr)
  {
    return -1;
  }

  if (value <= head->data)
  {
    return 0;
  }

  if (tail->data < value)
  {
    return numElements;
  }

  if (head->data <= value && value < tail->data)
  {
    while (left <= right)
    {
      if (middle < numElements / 2)
      {
        current = head;
        for (int i = 0; i < middle; i++)
        {
          current = current->next;
        }
      }
      else
      {
        current = tail;
        for (int i = numElements - 1; i > middle; i--)
        {
          current = current->prev;
        }
      }

      if (value == current->data)
      {
        return middle;
      }
      else if (value < current->data)
      {
        right = middle - 1;
      }
      else
      {
        left = middle + 1;
      }
      middle = (left + right) / 2;
    }
  }
  return -1;
}

// Complejidad O(n)
template <class T>
void DLinkedList<T>::busqueda(std::ostream &salida, Registro l, Registro r)
{
  DLLNode<T> *tmp = this->head;
  while (tmp != nullptr && tmp->data < l)
  {
    tmp = tmp->next;
  }
  while (tmp != nullptr && tmp->data <= r)
  {
    salida << tmp->data;
    std::cout << tmp->data << std::endl;
    if (!(tmp->next == nullptr || !(tmp->next->data <= r)))
    {
      salida << std::endl;
    }
    tmp = tmp->next;
  }
}

// Complejidad O(n)
template <class U>
std::ostream &operator<<(std::ostream &salida, const DLinkedList<U> &DLinkedList)
{
  DLLNode<U> *tmp = DLinkedList.head;
  for (int i = 0; i < DLinkedList.numElements - 1; ++i)
  {
    salida << tmp->data << std::endl;
    tmp = tmp->next;
  }
  salida << tmp->data;
  return salida;
}

#endif // _LINKEDLIST_H_
