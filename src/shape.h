#ifndef SHAPE_H
#define SHAPE_H
#include "iterator.h"
#include <string>
class Visitor;
class Shape {
public:
  Shape(){};
  Shape(std::string id); // interface for default color "white".
  Shape(std::string id, std::string color); // interface for color input by user.
  std::string id() const ; // return id of shape.
  std::string color() const ; // return color of shape.

  virtual double area() const = 0;
  virtual double perimeter() const = 0;
  virtual std::string info() const = 0;
  virtual std::string type() const = 0;
  virtual void addShape(Shape * shape); // throw std::string "Only compound shape can add shape!"
  virtual void deleteShapeById(std::string id); // throw std::string "Only compound shape can add shape!"
  virtual Shape * getShapeById(std::string id) const;// throw std::string "Only compound shape can add shape!"
  virtual Iterator* createIterator() const;
  void setColor(std::string color);
  virtual void accept(Visitor * visitor) = 0;
  virtual ~Shape() = default;

private:
  std::string _id,_color;

};
#endif
