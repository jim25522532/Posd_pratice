#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H
#include <string>
#include "shape.h"
#include "iterator.h"

class NullIterator : public Iterator {
public:
  void first(){
    throw std::string("No child member!");
  }
  void next(){
    throw std::string("No child member!");
  }

  bool isDone() const{
      return true;
  }

  Shape * currentItem() const {
      if(isDone()){
        throw std::string("No child member!");
      }
      return nullptr;
    }

};

#endif
