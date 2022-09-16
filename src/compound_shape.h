#ifndef COMPOUND_SHAPE_H
#define COMPOUND_SHAPE_H
#include <string>
#include <list>
#include <sstream>
#include "shape.h"
#include "iterator.h"
#include "shape_iterator.h"
#include "visitor.h"
#include <iterator>
class CompoundShape : public Shape {
public:
  CompoundShape(std::string id, std::list<Shape*> shapes):Shape(id,"transparent") {
    // The default color of compound shape should be "transparent".
    //if(shapes.size()==0){
      // should throw std::string "This is not a compound shape!"
      //throw std::string("This is not a compound shape!");
    //}

    std::list<Shape *> ::iterator begin = shapes.begin();
    std::list<Shape *> ::iterator end = shapes.end();
    std::list<Shape *>::iterator it;


    for(it = begin;it!=end;++it){
      _shapes.push_back(*it);
    }


  }

  double area() const {
    double totalArea = 0.0;

    std::list<Shape *> ::const_iterator begin = _shapes.begin();
    std::list<Shape *> ::const_iterator end = _shapes.end();
    std::list<Shape *>::const_iterator it;

    for(it = begin;it!=end;++it){
      totalArea += (*it)->area();
    }

    return totalArea;

  }

  double perimeter() const {
    double totalPermiter = 0.0;
    std::list<Shape *> ::const_iterator begin = _shapes.begin();
    std::list<Shape *> ::const_iterator end = _shapes.end();
    std::list<Shape *>::const_iterator it;
    for(it = begin;it!=end;++it){
      totalPermiter += (*it)->perimeter();
    }

    return totalPermiter;
  }

  std::string info() const {
    std::stringstream ss;
    ss << "Compound Shape {";

    std::list<Shape *> ::const_iterator begin = this->_shapes.begin();
    std::list<Shape *> ::const_iterator end = this->_shapes.end();
    std::list<Shape *>::const_iterator it;
    for(it = begin;it!=end;){
      ss << (*it)->info();
      if((++it)!=end){
        ss << ", ";
      }
    }
    ss<< "}";

    return ss.str();
      // return list of all containing shapes info with wrapped of "CompoundShape {}".
      // ex."Compound Shape {Ellipse (4.000, 3.000), Rectangle (3.000, 4.000), Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])}"
  }

  std::string type() const {
    return std::string("Compound Shape");
  }

  void addShape(Shape* shape) {
      this->_shapes.push_back(shape);
  }

  void deleteShapeById(std::string id) {
    try{
      this->getShapeById(id);
    }catch(std::string e){
      if(e=="Expected get shape but shape not found"){
        throw std::string("Expected delete shape but shape not found");
      }
    }

    std::list<Shape *> ::iterator begin = this->_shapes.begin();
    std::list<Shape *> ::iterator end = this->_shapes.end();
    std::list<Shape *>::iterator it;

    for(it = begin;it!=end;++it){
      if((*it)->id()==id){
        _shapes.erase(it);
        return;
      }
      else{
        try{
          (*it)->deleteShapeById(id);
        }catch(std::string e){
          //ignore error
        }
      }
    }

  }

  Shape* getShapeById(std::string id) const{

    std::list<Shape *> ::const_iterator begin = this->_shapes.begin();
    std::list<Shape *> ::const_iterator end = this->_shapes.end();
    std::list<Shape *>::const_iterator it;

    try{
      for(it = begin;it!=end;++it){
        if((*it)->id()==id){
          return (*it);
        }
        else{
          try{
            Shape * mbox1;
            mbox1 = (*it)->getShapeById(id);
            if(mbox1->id()==id){
              return mbox1;
            }
          }catch(std::string e){

          }
        }
      }
    }catch(std::string e){
      //ignore
    }

    throw std::string("Expected get shape but shape not found");
  }

  Iterator * createIterator() const{
    return new ShapeIterator<std::list<Shape *>::const_iterator>(_shapes.begin(),_shapes.end());
  }

  int getNumberOfComponents() {
    return this->_shapes.size();
  }

  void accept(Visitor * visitor){
    visitor->visit(this);
  }

  std::list<Shape *> getShapes(){
    return this->_shapes;
  }

private:
  std::list<Shape *> _shapes;

};
#endif
