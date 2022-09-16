#pragma once
#include "filter.h"
#include <list>
#include "shape.h"
#include <iterator>
typedef bool (*Predicate)(Shape *);

class ShapeFilter : public Filter {
public:

    ShapeFilter(Predicate pred):_pred(pred),_next(nullptr) {

    }
    
        // `Predicate` is a template name for lambda,
        //  you may use your own name.

    Filter* setNext(Filter* filter) {
        // seeting next filter.
        _next = filter;
        return _next;
    }

    std::list<Shape*> push(std::list<Shape*> shapes) {
        // push down filtered data and return result.
        std::cout << "filter start" << std::endl;
        if(shapes.size()==0){
            return shapes;
        }
        
        std::list<Shape *> ::iterator begin = shapes.begin();
        std::list<Shape *> ::iterator end = shapes.end();
        std::list<Shape*> tempResult;
        for(std::list<Shape *> ::iterator it  = begin;it!=end;it++){
            if(_pred((*it))) {
                tempResult.push_back((*it));
                std::cout << "filter success" << std::endl;
                
            }
        }
        if(tempResult.size()==0){
            return tempResult;
        }

        if(_next) {
            std::cout << "還有filter" << std::endl;
            try{
                tempResult = _next->push(tempResult);
            }catch(std::string e){
                //ignore
            
            }
        }
        std::cout << "size:" << tempResult.size() <<std::endl;
        return tempResult;

    }
private:
    Filter * _next;
    Predicate _pred;
    std::list<Shape*> _result;
};
