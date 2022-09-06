#pragma once
#include "app.h"
#include "visitor.h"
#include "folder.h"


class FindVisitor : public Visitor {
public:
    FindVisitor(std::string name):_name(name) {
        
    }
    
    void visitApp(App* app) {
        //std::cout << "test:"app->name() <<std::endl;
        if(app->name()==_name){
            this->_result = app->route();
        }
        // find app when app's name matches given name,
        // add app's route as result.
    }
    
    void visitFolder(Folder* folder) {

        if(folder->name()==_name){
            this->_result = folder->route();
        }
  
        //event1 folder內有app
        //std::cout << "test:"app->name() <<std::endl;
        Iterator* it = folder->createIterator();
        for(it->first();!it->isDone();it->next()){
            
            FindVisitor * fv = new FindVisitor(_name);
            it->currentItem()->accept(fv);
            if(fv->getResult().length()>0){
                if(_result.length()>0){
                    _result +="\n";
                }
                _result += fv->getResult();
            }
        }
        
       
        // find folder when folder's name matches given name,
        // add folder's route as result.
        // And find the tree structure bellow,
        // add the other match result with `\n`.
    }
    
    std::string getResult() const {
        // return result.
        return this->_result;
    }
private:
    std::string _name;
    std::string _result;
};
