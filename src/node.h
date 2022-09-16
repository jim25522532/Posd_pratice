#ifndef NODE_H
#define NODE_H
#include <string>
#include "iterator.h"
#include <list>
#include "visitor.h"
class Node {
public:

        Node(std::string id, std::string name, double size);

         std::string id() const;
        //
         std::string name() const;

        virtual std::string route() const;
        //
        virtual double size() const;
        //
        virtual void updatePath(std::string path);
        //
        virtual void addNode(Node* node);
        //
        virtual Node* getNodeById(std::string id) const;
        //
        virtual void deleteNodeById(std::string id);
        //
        virtual Iterator* createIterator() const;


        virtual void addNodes(std::list<Node*> nodes);
        // App: throw std::string "only folder can add nodes.".
        // Folder: add nodes into folder and update the path of the nodes.

        virtual void accept(Visitor* visitor) = 0;


        virtual ~Node()= default;
        
private:
  std::string _path,_id,_name;
  double _size;
};

#endif
