#ifndef APP_H
#define APP_H
#include "node.h"
#include <string>
#include "visitor.h"
#include <list>
class App : public Node{
public:
    App(std::string id, std::string name, double size):Node(id,name,size){

    }

    void addNode(Node* node){
      throw std::string("only folder can add node.");
    }

    Node* getNodeById(std::string id) const {
      throw std::string("only folder can get node.");
    }

    void deleteNodeById(std::string id){
      throw std::string("only folder can delete node.");
    }

    void addNodes(std::list<Node*> nodes){
      throw std::string("only folder can add nodes.");
    }

    void accept(Visitor * visitor){
      visitor->visitApp(this);
    }
    // implement any functions inherit from Node that you think is suitable.
};

#endif
