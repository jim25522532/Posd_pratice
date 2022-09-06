#include "node.h"
#include <string>
#include "null_iterator.h"
Node::Node(std::string id, std::string name, double size):_id(id),_name(name),_size(size),_path(""){

}
std::string Node::id() const{
  return _id;
}

std::string Node::name() const{
  return _name;
}

std::string Node::route() const{
  return _path + "/" + _name;
}

double Node::size() const{
  return _size;
}

void Node::updatePath(std::string path){
  this->_path = path;
}

void Node::addNode(Node* node){
  throw std::string("only folder can add node.");
}

Node* Node::getNodeById(std::string id) const {
  throw std::string("only folder can get node.");
}

void Node::deleteNodeById(std::string id){
  throw std::string("only folder can delete node.");
}

void Node::addNodes(std::list<Node*> nodes){
  throw std::string("only folder can add nodes.");
}

Iterator * Node::createIterator() const{
  Iterator * it = new NullIterator();
  return it;
}
