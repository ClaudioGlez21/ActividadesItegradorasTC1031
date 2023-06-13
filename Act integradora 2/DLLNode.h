#ifndef _DLLNODE_H
#define _DLLNODE_H

template <class T>
class DLLNode
{
public:
  T data;
  DLLNode<T> *next;
  DLLNode<T> *prev;
  bool operator<(const DLLNode<T> &other) const
  {
    return data < other.data;
  }

  DLLNode();
  DLLNode(T value);
};

template <class T>
DLLNode<T>::DLLNode()
{
  next = NULL;
  prev = NULL;
}

template <class T>
DLLNode<T>::DLLNode(T value)
{
  data = value;
  next = NULL;
  prev = NULL;
}

#endif // _DLLNODE_H
