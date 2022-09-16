#ifndef SHAPE_BUILDER_H
#define SHAPE_BUILDER_H

#include "shape.h"
#include "rectangle.h"
#include "ellipse.h"
#include "compound_shape.h"
#include "two_dimensional_coordinate.h"
#include "triangle.h"
#include <stack>
#include <deque>
#include <vector>
#include <list>
#include <string>

class ShapeBuilder {
public:
    ShapeBuilder(){
      _pushdown = new std::stack<Shape *>();
      _compounEnd = new std::deque<Shape *>();
      v = new std::vector<Shape *>();
    }

    void buildRectangle(double length, double width) {
      //std::cout << "build rect " << std::endl;
      Shape * r = new Rectangle(std::to_string(_id),length, width);
      _pushdown->push(r);
      this->_id++;
        // build a rectangle with an unique id and push in a std::stack.
    }

    void buildEllipse(double semiMajorAxes, double semiMinorAxes) {
      //std::cout << "build ellipse " << std::endl;
      Shape * e = new Ellipse(std::to_string(_id),semiMajorAxes, semiMinorAxes);
      _pushdown->push(e);
      this->_id++;
      // build a ellipse with an unique id and push in a std::stack.
    }

    void buildTriangle(double x1, double y1, double x2, double y2, double x3, double y3) {
      std::vector<TwoDimensionalCoordinate*> triangleVector;
      //std::cout << "build triangle " << std::endl;
      triangleVector.push_back(new TwoDimensionalCoordinate(x1, y1));
      triangleVector.push_back(new TwoDimensionalCoordinate(x2, y2));
      triangleVector.push_back(new TwoDimensionalCoordinate(x3, y3));
      Shape * t = new Triangle(std::to_string(_id),triangleVector);
      _pushdown->push(t);
      this->_id++;
       // build a triangle with an unique id and push in a std::stack.
     }

     void buildCompoundShapeBegin() {
       //std::cout << "build buildCompoundShapeBegin " << std::endl;
       std::list<Shape*> shapeList;
       Shape * cs = new CompoundShape(std::to_string(_id),shapeList);
        _pushdown->push(cs);
        _compounEnd->push_back(cs);
        this->_id++;
       // for notifing beginning of a Compound Shape.
     }

     void buildCompoundShapeEnd() {
       //std::cout << "build compound end" << std::endl;
       try{
        //條件1:當她不是compoundShape就要pop到vector , 條件2:push down最上面是compoundShape且 堆疊最上面compoundShape是不空的
          while(!dynamic_cast<CompoundShape*>(_pushdown->top()) ||
              (dynamic_cast<CompoundShape*>(_pushdown->top()) && !_pushdown->top()->createIterator()->isDone())
              ) {

              v->push_back(_pushdown->top());
              _pushdown->pop();
          }

          for(auto it=v->rbegin(); it!=v->rend(); it++){
            _pushdown->top()->addShape(*it);
          }
          v->clear();
          _compounEnd->pop_back();
          if(_compounEnd->size()>0){
            v->push_back(_pushdown->top());
            _pushdown->pop();
          }
          //要是有找到end的compoundShape,把pushdown2的都丟到v

         
       }catch(std::string e){
         std::cout << e << std::endl;
       }


       // for notifing ending of a Compound Shape.
     }


    std::deque<Shape*> getResult() {
      //std::cout << "check point" << std::endl;
      std::vector<Shape *> * result = new std::vector<Shape *>();

      while(!_pushdown->empty()){
        //std::cout << "check point2" << std::endl;
        result->push_back(_pushdown->top());
        _pushdown->pop();
      }
      //std::cout << result->size() << std::endl;
      //std::cout << "check point66" << std::endl;
      //std::deque<Shape*> dq(result->rbegin(),result->rend());
      std::deque<Shape*> * dq = new std::deque<Shape*>(result->rbegin(),result->rend());

      return *dq;

    }
private:
  std::stack<Shape *>  * _pushdown;
  std::deque<Shape *>  * _compounEnd;
  std::vector<Shape *> * v;
  static int _id;
};

int ShapeBuilder::_id = 0;
#endif
