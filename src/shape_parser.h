#ifndef SHAPE_PARSER_H
#define SHAPE_PARSER_H

#include "scanner.h"
#include "shape_builder.h"
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
class ShapeParser {
public:
    ShapeParser(std::string input){
        // initialize a scanner for handling input.
        _scanner = new Scanner(input);
        // initialize a shape builder for handling building shape.
        _sb = new ShapeBuilder();
    }

    void parser() {

      std::vector<double> shapeArgument;
      std::vector<Shape *>::iterator it;

      double num;
        try{
          while(true){
            //
            std::string parseString("");
            std::stringstream checknum;
            parseString = _scanner->nextToken();
            //std::cout << parseString <<std::endl;

            //把參數壓到argumet vecotr
            if(parseString=="Rectangle"){
              checknum.clear();
              //std::cout << "1" <<std::endl;
              if(_scanner->nextToken()=="("){
                  //std::cout << "2" <<std::endl;
                  parseString = _scanner->nextToken();//
                  checknum << parseString;
                  //std::cout << checknum.str() <<std::endl;
                  if(checknum >> num){
                      shapeArgument.push_back(num);
                  }
                  if(_scanner->nextToken()==","){
                    parseString = _scanner->nextToken();
                    checknum.clear();
                    checknum << parseString;

                    if(checknum >> num){
                      //std::cout << "argu2" << std::endl;
                      shapeArgument.push_back(num);
                    }

                    if(_scanner->nextToken()==")"){
                      //std::cout << "last token:" << shapeArgument.size() << std::endl;
                      if(shapeArgument.size()==2){
                        _sb->buildRectangle(shapeArgument[0],shapeArgument[1]);
                      }
                    }
                  }
               }
               shapeArgument.clear();
            }
            else if(parseString=="Ellipse"){
              checknum.clear();
              //std::cout << "1" <<std::endl;
              if(_scanner->nextToken()=="("){
                  //std::cout << "2" <<std::endl;
                  parseString = _scanner->nextToken();//
                  checknum << parseString;
                  //std::cout << checknum.str() <<std::endl;
                  if(checknum >> num){
                      shapeArgument.push_back(num);
                  }
                  if(_scanner->nextToken()==","){
                    parseString = _scanner->nextToken();
                    checknum.clear();
                    checknum << parseString;

                    if(checknum >> num){
                      //std::cout << "argu2" << std::endl;
                      shapeArgument.push_back(num);
                    }

                    if(_scanner->nextToken()==")"){
                      //std::cout << "last token:" << shapeArgument.size() << std::endl;
                      if(shapeArgument.size()==2){
                        _sb->buildEllipse(shapeArgument[0],shapeArgument[1]);
                      }
                    }
                  }
               }
               shapeArgument.clear();
            }
            else if(parseString=="Triangle"){
              checknum.clear();
              //std::cout << "1" <<std::endl;
              if(_scanner->nextToken()=="("){
                  //std::cout << "2" <<std::endl;
                  parseString = _scanner->nextToken();//
                  checknum << parseString;
                  //std::cout << checknum.str() <<std::endl;
                  if(checknum >> num){
                      shapeArgument.push_back(num);
                  }
                  if(_scanner->nextToken()==","){
                    parseString = _scanner->nextToken();
                    checknum.clear();
                    checknum << parseString;

                    if(checknum >> num){
                      //std::cout << "argu2" << std::endl;
                      shapeArgument.push_back(num);
                    }
                    if(_scanner->nextToken()==","){
                      parseString = _scanner->nextToken();
                      checknum.clear();
                      checknum << parseString;
                      if(checknum >> num){
                        //std::cout << "argu3" << std::endl;
                        shapeArgument.push_back(num);
                      }
                      if(_scanner->nextToken()==","){
                        parseString = _scanner->nextToken();
                        checknum.clear();
                        checknum << parseString;
                        if(checknum >> num){
                          //std::cout << "argu4" << std::endl;
                          shapeArgument.push_back(num);
                        }
                        if(_scanner->nextToken()==","){
                          parseString = _scanner->nextToken();
                          checknum.clear();
                          checknum << parseString;
                          if(checknum >> num){
                            //std::cout << "argu5" << std::endl;
                            shapeArgument.push_back(num);
                          }
                          if(_scanner->nextToken()==","){
                            parseString = _scanner->nextToken();
                            checknum.clear();
                            checknum << parseString;
                            if(checknum >> num){
                              //std::cout << "argu6" << std::endl;
                              shapeArgument.push_back(num);
                            }
                            if(_scanner->nextToken()==")"){
                              //std::cout << "last token:" << shapeArgument.size() << std::endl;
                              if(shapeArgument.size()==6){
                              _sb->buildTriangle(shapeArgument[0],shapeArgument[1],shapeArgument[2],shapeArgument[3],shapeArgument[4],shapeArgument[5]);
                              }
                            }
                          }
                        }
                      }
                    }
                  }
               }
               shapeArgument.clear();
            }
            else if(parseString=="CompoundShape"){
              _sb->buildCompoundShapeBegin();
            }
            else if(parseString=="}"){
              _sb->buildCompoundShapeEnd();
            }
          }
        }
        //直到沒token會丟例外
        catch(std::string e){

        }

        // using Scanner::nextToken() to get all information to determine what to build,
        // and provide the argument the shape needed.
        // use functions in ShapeBuilder to build out the shape.
        // the shape with invalid argument should be ignored (see example bellow).
    }

    std::deque<Shape*> getResult() {
      return _sb->getResult();
        // return result.
    }
private:
  Scanner * _scanner ;
  std::vector<Shape *> _shapeStr;
  ShapeBuilder * _sb;
};


#endif
