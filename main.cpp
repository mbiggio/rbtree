#include "rbtree.hpp"
#include <iostream>
using namespace bst::rbtree;
using namespace std;

template <class T>
void printTree(rbtree<T> &irbtree) {
  for (const auto i : irbtree) 
    cout << i << " ";  
  cout << endl;
}

int main() {

  rbtree<int> aRbTree;
  cout << "is tree empty?: " << aRbTree.empty() << endl;
  cout << "value 10 found? " << aRbTree.contains(10) << endl;

  aRbTree.insert(20);
  aRbTree.insert(10);
  aRbTree.insert(30);
  aRbTree.insert(40);

  cout << "is tree empty?: " << aRbTree.empty() << endl;
  cout << "value 10 found? " << aRbTree.contains(10) << endl;

  printTree(aRbTree);
  aRbTree.remove(20);
  printTree(aRbTree);
  aRbTree.remove(25);
  printTree(aRbTree);
  aRbTree.remove(30);
  printTree(aRbTree);
  aRbTree.remove(10);
  printTree(aRbTree);
  aRbTree.remove(40);
  printTree(aRbTree);
  
  cout << "is tree empty?: " << aRbTree.empty() << endl;

  return 0;
}

