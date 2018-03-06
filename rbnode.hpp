#ifndef __RBNODE__
#define __RBNODE__

namespace bst { namespace rbtree {

enum color {
  kRed,
  kBlack
};

template <class T>
class rbnode {

public:
  rbnode(const T& iValue, color iColor);
  const T& getValue() const;
  void setValue(const T& iValue);
  rbnode<T> *getLeft() const; 
  rbnode<T> *getRight() const; 
  rbnode<T> *getParent() const; 
  void setLeft(rbnode<T> *iNode);
  void setRight(rbnode<T> *iNode);
  void setParent(rbnode<T> *iNode);
  const color getColor() const;
  void setColor(color iColor);

private:
  T _value;
  color _color;
  rbnode *_left;
  rbnode *_right;
  rbnode *_parent;
};

template <class T>
rbnode<T>::rbnode(const T& iValue, color iColor) :
  _value(iValue), _color(iColor), _left(0), _right(0), _parent(0)
{}

template <class T>
const T& rbnode<T>::getValue() const {
  return _value;
}

template <class T>
void rbnode<T>::setValue(const T& iValue) {
  _value = iValue;
}

template <class T>
rbnode<T> *rbnode<T>::getLeft() const {
  return _left;
}

template <class T>
rbnode<T> *rbnode<T>::getRight() const {
  return _right;
}

template <class T>
rbnode<T> *rbnode<T>::getParent() const {
  return _parent;
}

template <class T>
void rbnode<T>::setLeft(rbnode<T> *iNode) {
  _left = iNode;
}

template <class T>
void rbnode<T>::setRight(rbnode<T> *iNode) {
  _right = iNode;
}

template <class T>
void rbnode<T>::setParent(rbnode<T> *iNode) {
  _parent = iNode;
}

template <class T>
const color rbnode<T>::getColor() const {
  return _color;
}

template <class T>
void rbnode<T>::setColor(color iColor) {
  _color = iColor;
}


} // namespace rbtree
} // namspace bst

#endif
