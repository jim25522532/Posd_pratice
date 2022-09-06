#pragma once
#include <string>
#include <deque>
#include "node.h"
#include "node_builder.h"
#include "node_scanner.h"
#include <sstream>
#include <vector>

class NodeParser {
public:
    NodeParser(std::string input):_input(input) {
        _scanner = new NodeScanner(input);
        _nodeBuilder = new NodeBuilder();
        // initialize a scanner for handling input.
        // initialize a node builder for handling building node.
    }

    void parser() {
        std::vector<double> shapeArgument;
        std::vector<Node *>::iterator it;

        double num;
        try{
          while(!_scanner->isDone()){

            std::string parseString("");
            std::stringstream checknum;
            parseString = _scanner->nextToken();


            std::string appName = "";
            if( (parseString[pos] >= 'a' && parseString[pos] <= 'z') || (parseString[pos] >= 'A' && parseString[pos] <= 'Z') ){
              checknum.clear();
              //std::cout << "0:" <<appName <<std::endl;
              appName = parseString;
              parseString = _scanner->nextToken(); //下個期望拿到 ( 就是 app
              if(parseString=="("){
                  //std::cout << "1:" << parseString <<std::endl;

                  parseString = _scanner->nextToken();//
                  checknum << parseString;
                  //std::cout << "appname" <<appName << std::endl;;
                  //std::cout << checknum.str() <<std::endl;
                  //可以轉換成double
                  if(checknum >> num){
                    //std::cout << "2:"<< num <<std::endl;
                    if(_scanner->nextToken()==")"){
                        //std::cout << "build app" << appName <<std::endl;
                        _nodeBuilder->buildApp(appName,num);
                    }
                  }
               }
               else if(parseString=="{"){
                    //std::cout << "buildFolderBegin" << appName <<std::endl;
                    _nodeBuilder->buildFolderBegin(appName);
                }
            }
            else if(parseString=="}"){
              //std::cout << "buildFolderEnd" <<std::endl;
              if(_nodeBuilder->getFolderEndSize()>0){
                _nodeBuilder->buildFolderEnd();
              }
            }
            else if(parseString==","){
              //ignore
            }
          }
        }
        //直到沒token會丟例外
        catch(std::string e){

        }
        // using NodeScanner::nextToken() to get all information to determine what to build,
        // and provide the argument the node needed.
        // use functions in NodeBuilder to build out the node.
        // the node with invalid argument should be ignored.
    }

    std::deque<Node*> getResult() {
        // return result.
        return _nodeBuilder->getResult();
    }
private:
    std::string _input;
    std::string::size_type pos = 0;
    NodeScanner * _scanner ;
    std::deque<Node *> _nodeDeque;
    NodeBuilder * _nodeBuilder;
    static int _id;
};
