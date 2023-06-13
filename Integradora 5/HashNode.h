#ifndef _HASH_NODE_H
#define _HASH_NODE_H

#include "IPStats.h"

template <class K> class HashNode {
private:
  K key;
  IPStats data;
  int status;

public:
  HashNode();
  void setKey(K selectedKey);
  K getKey();
  void setData(IPStats selectedData);
  IPStats getData();
  void setStatus(int selectedStatus);
  int getStatus();
};

template <class K> HashNode<K>::HashNode() : data(), status(0) {}

template <class K> void HashNode<K>::setKey(K selectedKey) {
  key = selectedKey;
}

template <class K> K HashNode<K>::getKey() { return key; }

template <class K> void HashNode<K>::setData(IPStats selectedData) {
  data = selectedData;
}

template <class K> IPStats HashNode<K>::getData() { return data; }

template <class K> void HashNode<K>::setStatus(int selectedStatus) {
  status = selectedStatus;
}

template <class K> int HashNode<K>::getStatus() { return status; }

#endif /* _HASH_NODE_H */
