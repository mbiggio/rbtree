#ifndef __RBTREE__
#define __RBTREE__

#include "rbnode.hpp"
#include <iostream>

namespace bst { namespace rbtree {

template <class T>
class rbtree {

public:

  rbtree();
  int size() const;
  bool empty() const;
  bool contains(const T& key) const;
  void insert(const T& iValue);
  void remove(const T& iValue);

public:
  class iterator;
  iterator begin() {return iterator(minimum(), this);}
  iterator end() {return iterator(&_null, this);}

private:

  rbnode<T> *find(rbnode<T>* subtree, const T& key) const;
  void remove(rbnode<T>* node);
  rbnode<T> *successor(rbnode<T>* iNode);
  rbnode<T> *minimum();

  rbnode<T> *_root;
  rbnode<T> _null;
  int _size;

};

template <class T>
class rbtree<T>::iterator {
public:
  iterator(rbnode<T> *node, rbtree *irbtree): _node(node), _rbtree(irbtree) {}
  iterator &operator++() {_node = _rbtree->successor(_node); return *this;}
  const T& operator*() {return _node->getValue();}
  bool operator!=(const iterator &other) const { return (_node != other._node || _rbtree != other._rbtree);}

private:
  rbnode<T> *_node;
  rbtree *_rbtree;
};


template <class T>
rbtree<T>::rbtree(): _null(0,kBlack), _size(0) {
  _root = &_null;
}

template <class T>
int rbtree<T>::size() const {
  return _size;
}

template <class T>
bool rbtree<T>::empty() const {
  return (_size == 0);
}

template <class T>
bool rbtree<T>::contains(const T& key) const {
  return (find(_root, key) != &_null);
}

template <class T>
rbnode<T> *rbtree<T>::find(rbnode<T> *subtree, const T& key) const {
  if (subtree == &_null || subtree->getValue() == key) {
    return subtree;
  }
  else if (subtree->getValue() > key) {
    return find(subtree->getLeft(), key);
  }
  else {
    return find (subtree->getRight(), key);
  }
}

template <class T>
void rbtree<T>::insert(const T& iValue) {

  rbnode<T> * iNode = new rbnode<T>(iValue,kRed);
  iNode->setRight(&_null);
  iNode->setLeft(&_null);
  iNode->setParent(&_null);
  ++_size;

  rbnode<T> *currentParent = &_null;
  rbnode<T> *currentNode = _root;
  while (currentNode != &_null) {
    currentParent = currentNode;
    if (currentNode->getValue() <= iNode->getValue()) {
      currentNode = currentNode->getRight();
    } else {
      currentNode = currentNode->getLeft();
    }
  }

  if (currentParent != &_null) {
    iNode->setParent(currentParent);
    if (currentParent->getValue() <= iNode->getValue()) {
      currentParent->setRight(iNode);
    } else {
      currentParent->setLeft(iNode);
    }
  } else {
    _root = iNode;
  }

  // TODO: node inserted, now fixup
}

template <class T>
void rbtree<T>::remove(const T& iValue) {  
  rbnode<T> *node = find(_root, iValue);
  if (node == &_null) return;
  remove(node);

  // TODO: node removed, now fixup
}

template <class T>
void rbtree<T>::remove(rbnode<T> *node) {  
  if (node->getLeft() == &_null || node->getRight() == &_null) {
    // at least one son is null
#ifndef NDEBUG
    std::cout << "remove: one son is null" << std::endl;
#endif
    rbnode<T> *sonNode = &_null;
    if (node->getLeft() != &_null) sonNode = node->getLeft();
    if (node->getRight() != &_null) sonNode = node->getRight();
    sonNode->setParent(node->getParent());
    if (node->getParent() == &_null) {
      _root = sonNode;
    } else {
      if (node->getParent()->getLeft() == node) {
        node->getParent()->setLeft(sonNode);
      } else {
        node->getParent()->setRight(sonNode);
      }
    }
    delete node;
  } else {
    // both sons are non-null
#ifndef NDEBUG
    std::cout << "remove: both sons are non-null" << std::endl;
#endif
    rbnode<T> *succ = successor(node);
    T value = succ->getValue();
    remove(succ);
    node->setValue(value);
  }
}

template <class T>
rbnode<T> *rbtree<T>::successor(rbnode<T>* iNode) {
  if (iNode == &_null) return iNode;
  if (iNode->getRight() != &_null) {
    rbnode<T> *subtree = iNode->getRight();
    while(subtree->getLeft() != &_null) {
      subtree = subtree->getLeft();
    }
    return subtree;
  }

  rbnode<T> *currentNode = iNode->getParent();
  rbnode<T> *currentSon = iNode;
  while ((currentNode != &_null) && (currentSon == currentNode->getRight())) {
    currentSon = currentNode;
    currentNode = currentNode->getParent();
  }

  return currentNode;
}

template <class T>
rbnode<T> *rbtree<T>::minimum() {
  if (_root == &_null) return &_null;
  rbnode<T> *currentNode = _root;
  while (currentNode->getLeft() != &_null) currentNode = currentNode->getLeft();
  return currentNode;
}

} // namespace rbtree
} // namespace bst

#endif
