#ifndef UTILITY_H
#define UTILITY_H

#include "node.h"
#include "iterator.h"
#include "node_iterator.h"
#include "null_iterator.h"
#include <string>
#include <deque>

template<class Filter>
std::deque<Node*> filterNode(Node* node, Filter filter) {
  Iterator * it = node->createIterator();
  std::deque<Node *> dq;

  try{
    for(it->first();!it->isDone();it->next()){
      Node * s = it->currentItem();
      if(filter(s)){
        dq.push_back(s);
      }


      Iterator * it2 = s->createIterator();

      //null_iterator 或是空的shape_iterator 都是done狀態
      if(!it2->isDone()){
        std::deque<Node *> dq2 = filterNode(s,filter);
        for(auto it3 = dq2.begin();it3 < dq2.end();++it3){
          dq.push_back((*it3));
        }
      }
    }
  }catch(std::string e){
    throw std::string("Only folder can filter node!");
  }
  return dq;
}

class SizeFilter {
public:
    SizeFilter(double upperBound, double lowerBound):_upperBound(upperBound),_lowerBound(lowerBound){

    }
    bool operator() (Node* node) const {
        return node->size() <=_upperBound && node->size()>=_lowerBound;
    }
private:
  double _upperBound, _lowerBound;
};

#endif
