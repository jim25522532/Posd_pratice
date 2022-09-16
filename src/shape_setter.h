#pragma once
#include <list>
#include "../src/filter.h"
#include "../src/shape.h"
#include "../src/iterator.h"
typedef void (*Setter)(Shape *);

class ShapeSetter : public Filter {
public:

    ShapeSetter(Setter set):_set(set),_next(nullptr) {

    }
        // `Setter` is a template name for lambda,
        //  you may use your own name.

    Filter* setNext(Filter* filter) {
        // seeting next filter.
        _next = filter;
        return _next;
    }

    std::list<Shape*> push(std::list<Shape*> shapes) {
        // push down setted data and return result.
        // push down filtered data and return result.
        std::cout << "filter start" << std::endl;
        std::list<Shape *> ::iterator begin = shapes.begin();
        std::list<Shape *> ::iterator end = shapes.end();

        if(shapes.size()==0){
            return shapes;
        }

        for(std::list<Shape *> ::iterator it  = begin;it!=end;it++){
            _set((*it));
            _result.push_back((*it));
        }


        if(_next) {
            std::cout << "還有filter" << std::endl;
            try{
                _result = _next->push(_result);
            }catch(std::string e){
                //ignore
            }
        }
        
        return _result;
    }

private:
    Filter * _next;
    Setter _set;
    std::list<Shape*> _result;

};
