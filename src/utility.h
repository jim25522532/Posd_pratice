#ifndef UTILITY_H
#define UTILITY_H

#include "shape.h"
#include "iterator.h"
#include "shape_iterator.h"
#include "null_iterator.h"
#include <string>
#include <deque>
typedef bool (* fn)(Shape * a);

template<class Filter>
std::deque<Shape *> filterShape(Shape * shape , Filter filter){
  Iterator * it = shape->createIterator();
  std::deque<Shape *> dq;

  try{
    for(it->first();!it->isDone();it->next()){
      Shape * s = it->currentItem();
      if(filter(s)){
        dq.push_back(s);
      }

      //if compoundShape have compoundShape go recursion
      Iterator * it2 = s->createIterator();

      //null_iterator 或是空的shape_iterator 都是done狀態
      if(!it2->isDone()){
        //s 一定是compoundShape 且不為空
        std::deque<Shape *> dq2 = filterShape(s,filter);
        for(auto it3 = dq2.begin();it3 < dq2.end();++it3){
          dq.push_back((*it3));
        }
      }
    }
  }catch(std::string e){
    throw std::string("Only compound shape can filter shape!");
  }
  return dq;
}

class AreaFilter {
    public:
      AreaFilter(double upperBound, double lowerBound):_upperBound(upperBound),_lowerBound(lowerBound) {

      }
    bool operator() (Shape* shape) const {
      return shape->area() <=_upperBound && shape->area()>=_lowerBound;
    }

    double _upperBound,_lowerBound;
};


class PerimeterFilter{
public:
  PerimeterFilter(double upperBound, double lowerBound):_upperBound(upperBound),_lowerBound(lowerBound) {

  }
  bool operator() (Shape* shape) const {
    return shape->perimeter() <=_upperBound && shape->perimeter()>=_lowerBound;
  }


  double _upperBound,_lowerBound;
};

class ColorFilter{
public:
  ColorFilter(std::string color){
    this->_color = color;
  }
  bool operator() (Shape* shape) const {
    return shape->color()==_color;
  }


  std::string _color;
};

class TypeFilter{
public:
  TypeFilter(std::string type):_type(type) {

  }
  bool operator() (Shape* shape) const {
    return shape->type()==_type;
  }

  std::string _type;
};

Shape* getShapeById(Shape* shape, std::string id) {

    Iterator * it = shape->createIterator();
    try{
      it->first();
    }catch(std::string e){
      throw std::string("Only compound shape can get shape!");
    }
    for(it->first();!it->isDone();it->next()){

      //only ShapeIterator can use currentItem or throw exception
      Shape * s = it->currentItem();

      if(s->id()==id){
        return s;
      }
      //if compoundShape have compoundShape go recursion
      Iterator * it2 = s->createIterator();

      //null_iterator 或是空的shape_iterator 都是done狀態
      if(!it2->isDone()){
        //s 一定是compoundShape 且不為空
        Shape * s2 = getShapeById(s,id);
        if(s2){
          return s2;
        }
      }
    }
    throw std::string("Expected get shape but shape not found");

}


#endif
