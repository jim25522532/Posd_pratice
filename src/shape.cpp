#include <iostream>
#include "shape.h"
#include "iterator.h"
#include "null_iterator.h"
#include "visitor.h"
#include <string>

Shape::Shape(std::string id){
  this->_color = "white";
  this->_id = id;
}

Shape::Shape(std::string id,std::string color){
  this->_id = id;
  this->_color = color;
}

std::string Shape::color() const {
  return this->_color;
};

std::string Shape::id() const {
  return this->_id;
};


void Shape::addShape(Shape * shape){
  throw std::string("Only compound shape can add shape!");

}

void Shape::deleteShapeById(std::string id){
  throw std::string("Only compound shape can delete shape!");
}


Shape * Shape::getShapeById(std::string id) const{
  throw std::string("Only compound shape can get shape!");
}

Iterator * Shape::createIterator() const{
  Iterator * it = new NullIterator();
  return it;
}

void Shape::setColor(std::string color) {
  std::cout <<"cheangr color " <<std::endl;
  this->_color = color;
};