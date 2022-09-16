#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <math.h>
#include <string>
#include <iomanip>
#include <sstream>
#include "shape.h"
#include "visitor.h"

class Ellipse: public Shape {
public:
    Ellipse(double semiMajorAxes, double semiMinorAxes):_semiMajorAxes(semiMajorAxes),_semiMinorAxes(semiMinorAxes) {
        // If the ellipse can't be successfully created,
        // handle the exception by throwing string "This is not a ellipse!"
        if(semiMajorAxes<=0.0 || semiMinorAxes<=0.0 || semiMajorAxes < semiMinorAxes){
          throw std::string("This is not an ellipse!");
        }

    }

    Ellipse(std::string id , double semiMajorAxes, double semiMinorAxes):Shape(id) {
          // If the ellipse can't be successfully created,
          // handle the exception by throwing string "This is not a ellipse!"
        if(semiMajorAxes<=0.0 || semiMinorAxes<=0.0 || semiMajorAxes < semiMinorAxes){
          throw std::string("This is not an ellipse!");
        }

        this->_semiMajorAxes = semiMajorAxes;
        this->_semiMinorAxes = semiMinorAxes;
    }

    Ellipse(std::string id, double semiMajorAxes, double semiMinorAxes, std::string color):Shape(id,color) {
        // If the ellipse can't be successfully created,
        // handle the exception by throwing string "This is not a ellipse!"
        if(semiMajorAxes<=0.0 || semiMinorAxes<=0.0 || semiMajorAxes < semiMinorAxes){
          throw std::string("This is not an ellipse!");
        }

        this->_semiMajorAxes = semiMajorAxes;
        this->_semiMinorAxes = semiMinorAxes;

    }

    double area() const {
        // return the area of the Ellipse.
        return M_PI * this->_semiMajorAxes * this->_semiMinorAxes;
    }

    double perimeter() const {
        // return the perimeter of the Ellipse.
        //std::cout << 2 * M_PI * sqrt(((_semiMajorAxes * _semiMajorAxes) + (_semiMinorAxes * _semiMinorAxes))/( 2.0)) << std::endl;
        return 2.0 * M_PI * this->_semiMinorAxes + 4.0 * ( this->_semiMajorAxes  - this->_semiMinorAxes );
    }

    std::string info() const {
      std::stringstream ss;
      ss << "Ellipse (" << std::setprecision(3) << std::fixed << this->_semiMajorAxes << ", " << std::setprecision(3) << std::fixed << this->_semiMinorAxes << ")";

      return ss.str();
    }

    std::string type() const {
      return std::string("Ellipse");
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

    double getSemiMajorAxes() const{
      return this->_semiMajorAxes;
    }

    double getSemiMinorAxes() const{
      return this->_semiMinorAxes;
    }

    void accept(Visitor * visitor){
      visitor->visit(this);
    }
private:
  double _semiMajorAxes , _semiMinorAxes;

};
#endif
