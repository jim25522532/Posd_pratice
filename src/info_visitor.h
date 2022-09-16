#ifndef INFO_VISITOR_H
#define INFO_VISITOR_H

#include "ellipse.h"
#include "rectangle.h"
#include "triangle.h"
#include "compound_shape.h"
#include <math.h>
#include "visitor.h"
#include <list>
#include <iterator>
#include "shape.h"
#include <sstream>
#include <string>
#include "two_dimensional_coordinate.h"


class InfoVisitor : public Visitor {
public:
    void visit(Ellipse* ellipse) {
      _ss << "Ellipse (" << std::setprecision(3) << std::fixed << ellipse->getSemiMajorAxes() << ", " << std::setprecision(3) << std::fixed << ellipse->getSemiMinorAxes() << ")";
      _info = _ss.str();
    }

    void visit(Triangle* triangle) {
      std::vector<TwoDimensionalCoordinate*> m_vectors = triangle->getMvector();

      _ss << "Triangle ([" << std::setprecision(3) << std::fixed << m_vectors[0]->getX() << ", " << std::setprecision(3)
      << std::fixed << m_vectors[0]->getY() << "], [" << std::setprecision(3) << std::fixed << m_vectors[1]->getX()
      << ", " << std::setprecision(3) << std::fixed << m_vectors[1]->getY() << "], ["
      << std::setprecision(3) << std::fixed << m_vectors[2]->getX() << ", " << std::setprecision(3)
      << std::fixed << m_vectors[2]->getY() << "])";
        // return the info of the Triangle.
        // ex. Triangle ([0.000, 0.000], [0.000, -3.141], [-4.000, 0.000])
      _info = _ss.str();
    }

    void visit(Rectangle* rectangle) {
      _ss << "Rectangle (" << std::setprecision(3) << std::fixed << rectangle->getLength() << ", " << std::setprecision(3) << std::fixed << rectangle->getWidth() << ")";
      _info = _ss.str();
    }

    void visit(CompoundShape * compoundShape) {

      _ss << "Compound Shape {";
      this->_shapes = compoundShape->getShapes();
      std::list<Shape *> ::iterator begin = this->_shapes.begin();
      std::list<Shape *> ::iterator end = this->_shapes.end();
      std::list<Shape *>::iterator it;

      for(it = begin;it!=end;){
        InfoVisitor * iv = new InfoVisitor();
        (*it)->accept(iv);
        _ss << iv->info();
        if((++it)!=end){
          _ss << ", ";
        }

      }
      _ss<< "}";

       this->_info = _ss.str();
    }

    std::string info() const {
      return this->_info;
    }

private:
  std::string _info;
  std::list<Shape *> _shapes;
  std::stringstream _ss;
};

#endif
