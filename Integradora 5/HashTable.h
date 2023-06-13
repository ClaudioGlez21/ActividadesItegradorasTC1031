#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include "Graph.h"
#include "HashNode.h"
#include "LinkedList.h"
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>
#include <algorithm>

template <class K, class T> class HashTable {
private:
  std::vector<HashNode<K>> table;
  int numElements;
  int maxSize;
  int numCollisions;

public:
  HashTable();
  HashTable(int selectedMaxSize);
  void setMaxSize(int selectedMaxSize);
  int getHashIndex(const K &key);
  int getNumElements();
  int getNumCollisions();
  void print();
  void add(K key, T value);
  int find(K key);
  T getDataAt(int index);
  void remove(K key);
};

template <class K, class T> HashTable<K, T>::HashTable() {
  maxSize = 0;
  numElements = 0;
  numCollisions = 0;
  table = std::vector<HashNode<K>>(maxSize);
}

template <class K, class T> HashTable<K, T>::HashTable(int selectedMaxSize) {
  maxSize = selectedMaxSize;
  numElements = 0;
  numCollisions = 0;
  table = std::vector<HashNode<K>>(maxSize);
}

template <class K, class T>
void HashTable<K, T>::setMaxSize(int selectedMaxSize) {
  maxSize = selectedMaxSize;
  numElements = 0;
  numCollisions = 0;
  table = std::vector<HashNode<K>>(maxSize);
}

// Complejidad O(n)
// Referencia: https://cpp.hotexamples.com/examples/-/-/GetHashIndex/cpp-gethashindex-function-examples.html
template <class K, class V> int HashTable<K, V>::getHashIndex(const K &key) {
  std::hash<K> hashFunc;
  size_t hashValue = hashFunc(key);
  return static_cast<int>(hashValue % maxSize);
}

template <class K, class T> int HashTable<K, T>::getNumElements() {
  return numElements;
}

// Complejidad
template <class K, class T> int HashTable<K, T>::getNumCollisions() {
  return numCollisions;
}

template <class K, class T> void HashTable<K, T>::print() {
  std::cout << "Content of the hash table: " << std::endl;
  for (int i = 0; i < maxSize; i++) {
    if (table[i].getStatus() == 1) {
      std::cout << "Cell: " << i << " Key: " << table[i].getKey()
                << ", Value: " << table[i].getData().ip
                << ", Outgoing Links: " << table[i].getData().outgoingLinks
                << ", Incoming Links: " << table[i].getData().incomingLinks
                << std::endl;
    }
  }
}

template <class K, class T> void HashTable<K, T>::add(K key, T value) {
  if (numElements == maxSize) {
    throw std::out_of_range("Hash Table is full");
  }
  if (find(key) != -1) {
    throw std::out_of_range("Element is already in the Hash Table");
  }

  int hashVal = getHashIndex(key);
  HashNode<K> &node = table[hashVal];

  if (node.getStatus() != 1) {
    node.setKey(key);
    node.setData(value);
    node.setStatus(1);
    numElements++;
  } else {
    int i = 1;
    int newIndex = (hashVal + i * i) % maxSize;
    while (table[newIndex].getStatus() == 1) {
      i++;
      newIndex = (hashVal + i * i) % maxSize;
      numCollisions++;
    }
    HashNode<K> &newNode = table[newIndex];
    newNode.setKey(key);
    newNode.setData(value);
    newNode.setStatus(1);
    numElements++;
  }
}

template <class K, class T> int HashTable<K, T>::find(K key) {
  int hashVal = getHashIndex(key);
  HashNode<K> &node = table[hashVal];

  if (node.getStatus() == 1 && node.getKey() == key) {
    return hashVal;
  }

  int i = 1;
  int newIndex = (hashVal + i * i) % maxSize;
  while (table[newIndex].getStatus() == 1 && table[newIndex].getKey() != key) {
    i++;
    newIndex = (hashVal + i * i) % maxSize;
  }

  if (table[newIndex].getStatus() == 1 && table[newIndex].getKey() == key) {
    return newIndex;
  }

  return -1;
}

template <class K, class T> T HashTable<K, T>::getDataAt(int index) {
  if (index < 0 || index >= maxSize) {
    throw std::out_of_range("Invalid index");
  }
  return table[index].getData();
}

template <class K, class T> void HashTable<K, T>::remove(K key) {
  int index = find(key);
  if (index == -1) {
    throw std::out_of_range("Element not found in the Hash Table");
  }
  table[index].setStatus(0);
  numElements--;
}

#endif /* _HASH_TABLE_H */
