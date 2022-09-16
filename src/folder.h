#ifndef FOLDER_H
#define FOLDER_H

#include "node.h"
#include <string>
#include <list>
#include <iterator>
#include "node_iterator.h"
#include "visitor.h"
class Folder : public Node {
public:
    Folder(std::string id, std::string name):Node(id,name,0.0) {

    } // the default size of folder is zero.

    double size() const {
      double totalSize = 0.0;

      std::list<Node *> ::const_iterator begin = _nodes.begin();
      std::list<Node *> ::const_iterator end = _nodes.end();
      std::list<Node *>::const_iterator it;

      for(it = begin;it!=end;++it){
        //totalSize += (*it)->size();
        
          Iterator * it2 = (*it)->createIterator();
          try{
            for(it2->first();!it2->isDone();it2->next()){
              std::cout << it2->currentItem()->size() << std::endl;
              totalSize += it2->currentItem()->size();
            }
           }catch(std::string){
            totalSize += (*it)->size();
          }
      }

      return totalSize;

    }

    void addNode(Node* node){
      Iterator * it = node->createIterator();
      try{
        it->first();
        //下面node 是個folder 
        //std::cout << this->route() << std::endl;
        node->updatePath(this->route());
        for(it->first();!it->isDone();it->next()){
          //folder內的node做update
          it->currentItem()->updatePath(node->route());
          //要是這個node也是個folder在去對他底下的node做update
          try{
            Iterator * it2 = it->currentItem()->createIterator();
            it2->first();
            for(it2->first();!it2->isDone();it2->next()){
              it2->currentItem()->updatePath(it->currentItem()->route());
            }
            //底下是個folder
          }catch(std::string){

          }
        }
      }catch(std::string e){
       //這邊是個node
       node->updatePath(this->route());
      }
      //node->updatePath(this->route());
      _nodes.push_back(node);
    }

    void deleteNodeById(std::string id){
      try{
        this->getNodeById(id);
      }catch(std::string e){
        if(e=="Expected get node but node not found."){
          throw std::string("Expected delete node but node not found.");
        }
      }

      std::list<Node *> ::iterator begin = this->_nodes.begin();
      std::list<Node *> ::iterator end = this->_nodes.end();
      std::list<Node *>::iterator it;

      for(it = begin;it!=end;++it){
        if((*it)->id()==id){
          //std::cout << (*it)->id() << std::endl;
          _nodes.erase(it);
          return;

        }
        else{
          try{
            (*it)->deleteNodeById(id);
          }catch(std::string e){
            //ignore error
          }
        }
      }
    }

    Node * getNodeById(std::string id) const{

      std::list<Node *> ::const_iterator begin = this->_nodes.begin();
      std::list<Node *> ::const_iterator end = this->_nodes.end();
      std::list<Node *>::const_iterator it;

      try{
        for(it = begin;it!=end;++it){
          if((*it)->id()==id){
            return (*it);
          }
          else{
            try{
              Node * node1;
              node1 = (*it)->getNodeById(id);
              if(node1->id()==id){
                return node1;
              }
            }catch(std::string e){

            }
          }
        }
      }catch(std::string e){
        //ignore
      }

      throw std::string("Expected get node but node not found.");
    }

    Iterator * createIterator() const{
      return new NodeIterator<std::list<Node *>::const_iterator>(_nodes.begin(),_nodes.end());
    }


    void addNodes(std::list<Node*> nodes){
      std::list<Node *> ::iterator begin = nodes.begin();
      std::list<Node *> ::iterator end = nodes.end();
      std::list<Node *>::iterator it;
      
  
        for(it = begin;it!=end;++it){
          addNode(*it);
        }
   
    }

    void accept(Visitor* visitor){
      visitor->visitFolder(this);
    }
private:
    std::list<Node*> _nodes;
};

#endif
