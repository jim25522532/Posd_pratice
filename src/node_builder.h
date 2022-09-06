#pragma once

#include <stack>
#include <deque>
#include "node.h"
#include "app.h"
#include "folder.h"
#include <string>
#include <vector>

class NodeBuilder {
public:
    void buildApp(std::string name, double size) {
        // build a app with an unique id and push in a std::stack.
        App * e = new App(std::to_string(_id),name,size);
        _pushdown.push(e);
        this->_id++;
    }

    void buildFolderBegin(std::string name) {
        Node * folder = new Folder(std::to_string(_id),name);

        _pushdown.push(folder);
        _folderEnd.push_back(folder);
        this->_id++;
        // notify begin of folder.
    }

    void buildFolderEnd() {
        // notify end of folder.
         //std::cout << "build compound end" << std::endl;
       try{
        //條件1:當她不是Folder就要pop到vector , 條件2:push down最上面是compoundShape且 堆疊最上面Folder是不空的
          while(!dynamic_cast<Folder*>(_pushdown.top()) ||
              (dynamic_cast<Folder*>(_pushdown.top()) && !_pushdown.top()->createIterator()->isDone()) ||
              (_folderEnd.size()>0 && _pushdown.top()==_swapNode) ) {
              //空的好像會進來
              std::cout << _pushdown.top()->route() << std::endl;
              //有folder要掛在上一層的folder下

              v.push_back(_pushdown.top());
              _pushdown.pop();
          }

          for(auto it=v.rbegin(); it!=v.rend(); it++){
            _pushdown.top()->addNode(*it);
          }
          v.clear();

          _folderEnd.pop_back();

          if(_folderEnd.size()>0){
            _swapNode = _pushdown.top();
            //v.push_back(_pushdown.top());
            //_pushdown.pop();
          }

          //要是有找到end的folder,把pushdown2的都丟到v


       }catch(std::string e){
         std::cout << e << std::endl;
       }


       // for notifing ending of a Compound Shape.
    }

    std::deque<Node*> getResult() {
        //std::cout << "check point" << std::endl;
        std::vector<Node *> result;

         while(!_pushdown.empty()){
            //std::cout << "check point2" << std::endl;
            result.push_back(_pushdown.top());
            _pushdown.pop();
        }
      //std::cout << result->size() << std::endl;
      //std::cout << "check point66" << std::endl;
      //std::deque<Shape*> dq(result->rbegin(),result->rend());
      std::deque<Node*> dq(result.rbegin(),result.rend());

      return dq;
    }

    int getFolderEndSize(){
      return _folderEnd.size();
    }
private:
    std::stack<Node *>  _pushdown;
    std::deque<Node *>  _folderEnd;
    Node * _swapNode;
    std::vector<Node *> v;
    static int _id;
};

int NodeBuilder::_id = 0;
