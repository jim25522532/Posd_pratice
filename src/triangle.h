#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <sstream>
#include "two_dimensional_coordinate.h"
#include <math.h>
#include "shape.h"
#include "visitor.h"

class Triangle: public Shape{
public:
    Triangle(std::vector<TwoDimensionalCoordinate*> coordinates):m_vectors(coordinates) {
      if(coordinates.size()<3 || coordinates.size()>3 ){
        throw std::string("This is not a triangle!");
      }

      if(this->area() ==0){
        throw std::string("This is not a triangle!");
      }
    }

    Triangle(std::string id, std::vector<TwoDimensionalCoordinate*> coordinates):Shape(id,"white"),m_vectors(coordinates) {
      if(coordinates.size()<3 || coordinates.size()>3 ){
        throw std::string("This is not a triangle!");
      }

      if(this->area() ==0){
        throw std::string("This is not a triangle!");
      }

    }

    Triangle(std::string id, std::vector<TwoDimensionalCoordinate*> coordinates, std::string color):Shape(id,color),m_vectors(coordinates){
      if(coordinates.size()<3 || coordinates.size()>3 ){
        throw std::string("This is not a triangle!");
      }

      if(this->area() ==0){
        throw std::string("This is not a triangle!");
      }

    }

    double area() const {
        return abs(((m_vectors[2]->getX() + m_vectors[0]->getX()) * (m_vectors[2]->getY() - m_vectors[0]->getY())
        +(m_vectors[0]->getX() + m_vectors[1]->getX()) * (m_vectors[0]->getY() - m_vectors[1]->getY())
        +(m_vectors[1]->getX() + m_vectors[2]->getX()) * (m_vectors[1]->getY() - m_vectors[2]->getY())))/2.0;

    }

    double perimeter() const {
        //求出AB AC BC三個邊長利用 distance formula

        //std::cout<< sqrt(abs((m_vectors[0]->getX() - m_vectors[1]->getX()) + abs((m_vectors[0]->getY()-m_vectors[1]->getY())))) << std::endl;
        //AB = A
        //_a = sqrt(pow((m_vectors[0]->getX() - m_vectors[1]->getX()),2) + pow((m_vectors[0]->getY()-m_vectors[1]->getY()),2));
        //AC = B
        //_b = sqrt(pow((m_vectors[0]->getX() - m_vectors[2]->getX()),2) + pow((m_vectors[0]->getY()-m_vectors[2]->getY()),2));
        //BC = C
        //_c = sqrt(pow((m_vectors[1]->getX() - m_vectors[2]->getX()),2) + pow((m_vectors[1]->getY()-m_vectors[2]->getY()),2));
        return sqrt(pow((m_vectors[0]->getX() - m_vectors[1]->getX()),2) + pow((m_vectors[0]->getY()-m_vectors[1]->getY()),2))
          + sqrt(pow((m_vectors[0]->getX() - m_vectors[2]->getX()),2) + pow((m_vectors[0]->getY()-m_vectors[2]->getY()),2))
          + sqrt(pow((m_vectors[1]->getX() - m_vectors[2]->getX()),2) + pow((m_vectors[1]->getY()-m_vectors[2]->getY()),2));

    }

    std::string info() const {
      std::stringstream ss;
      ss << "Triangle ([" << std::setprecision(3) << std::fixed << m_vectors[0]->getX() << ", " << std::setprecision(3)
      << std::fixed << m_vectors[0]->getY() << "], [" << std::setprecision(3) << std::fixed << m_vectors[1]->getX()
      << ", " << std::setprecision(3) << std::fixed << m_vectors[1]->getY() << "], ["
      << std::setprecision(3) << std::fixed << m_vectors[2]->getX() << ", " << std::setprecision(3)
      << std::fixed << m_vectors[2]->getY() << "])";

        // return the info of the Triangle.
        // ex. Triangle ([0.000, 0.000], [0.000, -3.141], [-4.000, 0.000])
        return ss.str();
    }

    std::string type() const {
      return std::string("Triangle");
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

    std::vector<TwoDimensionalCoordinate*>  getMvector(){
      return this->m_vectors;
    }

    void accept(Visitor * visitor){
      visitor->visit(this);
    }
private:
  //double _a,_b,_c;
  std::vector<TwoDimensionalCoordinate*> m_vectors;

};
#endif
