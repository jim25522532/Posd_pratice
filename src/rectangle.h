#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "shape.h"
#include "visitor.h"

class Rectangle : public Shape{
public:
    Rectangle(double length, double width){
        // If the rectangle can't be successfully created,
        // handle the exception by throwing string "This is not a rectangle!"
        if(length<=0.0 || width<=0.0){
          //std::cout<<"test"<< std::endl;
          throw std::string("This is not a rectangle!");
        }
        this->_length = length;
        this->_width = width;
        info();
    }

    Rectangle(std::string id, double length, double width):Shape(id,"white"){
        // If the rectangle can't be successfully created,
        // handle the exception by throwing string "This is not a rectangle!"
        if(length<=0.0 || width<=0.0){
          throw std::string("This is not a rectangle!");
        }
        this->_length = length;
        this->_width = width;
        //this->_id = id;
        //this->_color = "white";
        info();
    }

    Rectangle(std::string id, double length, double width, std::string color):Shape(id,color){
        // If the rectangle can't be successfully created,
        // handle the exception by throwing string "This is not a rectangle!"
        if(length<=0.0 || width<=0.0){
          throw std::string("This is not a rectangle!");
        }
        this->_length = length;
        this->_width = width;
        //this->_id = id;
        //this->_color = color;
        info();
    }

    double area() const {
      return _length * _width;
    }

    double perimeter() const {
        return 2.0 * (_length + _width);
    }

    std::string info() const{
      std::stringstream ss;
      ss << "Rectangle (" << std::setprecision(3) << std::fixed << this->_length << ", " << std::setprecision(3) << std::fixed << this->_width << ")";
      return ss.str();
    }

    std::string type() const {
      return std::string("Rectangle");
    }

    void addShape(Shape * shape){
      throw std::string("Only compound shape can add shape!");
    }

    void deleteShapeById(std::string id){
      throw std::string("Only compound shape can delete shape!");
    }

    Shape * getShapeById(std::string id){
      throw std::string("Only compound shape can get shape!");
    }

    double getLength(){
      return _length;
    }

    double getWidth(){
      return _width;
    }

    void accept(Visitor * visitor){
      visitor->visit(this);
    }
    //data members
private:
  double _length,_width;

};
#endif
