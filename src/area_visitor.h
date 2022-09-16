#ifndef AREA_VISITOR_H
#define AREA_VISITOR_H

#include "ellipse.h"
#include "rectangle.h"
#include "triangle.h"
#include "compound_shape.h"
#include <math.h>
#include "visitor.h"
#include <list>
#include <iterator>
#include "shape.h"
#include "two_dimensional_coordinate.h"
#include <math.h>

class AreaVisitor : public Visitor {
public:
    void visit(Ellipse* ellipse) {
      this->_area =  M_PI * ellipse->getSemiMajorAxes() * ellipse->getSemiMinorAxes();
    }

    void visit(Triangle* triangle) {
      std::vector<TwoDimensionalCoordinate*> m_vectors = triangle->getMvector();
      this->_area = abs(((m_vectors[2]->getX() + m_vectors[0]->getX()) * (m_vectors[2]->getY() - m_vectors[0]->getY())
      +(m_vectors[0]->getX() + m_vectors[1]->getX()) * (m_vectors[0]->getY() - m_vectors[1]->getY())
      +(m_vectors[1]->getX() + m_vectors[2]->getX()) * (m_vectors[1]->getY() - m_vectors[2]->getY())))/2.0;

    }

    void visit(Rectangle* rectangle) {
        this->_area = rectangle->getLength() * rectangle->getWidth();
    }

    void visit(CompoundShape * compoundShape) {
      double totalArea = 0.0;
      this->_shapes = compoundShape->getShapes();
      std::list<Shape *> ::iterator begin = this->_shapes.begin();
      std::list<Shape *> ::iterator end = this->_shapes.end();
      std::list<Shape *>::iterator it;
      AreaVisitor * av = new AreaVisitor();
      for(it = begin;it!=end;++it){
        (*it)->accept(av);
        totalArea += av->area();
      }

      _area = totalArea;
    }

    double area() const {
      return this->_area;
    }

private:
  double _area;
  std::list<Shape *> _shapes;
};

#endif
