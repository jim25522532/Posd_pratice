#pragma once
#include <string>
#include <vector>

class NodeScanner {
public:
    NodeScanner(std::string input):_input(input) {

    }

    std::string nextToken() {
         if(isDone()){
             throw std::string("next token doesn't exist.");
         }


        std::string s = "";
        skipWhiteSpace();

        while(1){
            if((_input[pos] >= 'a' && _input[pos] <= 'z') || (_input[pos] >= 'A' && _input[pos] <= 'Z')) {
                s = s + _input[pos];
                pos++;
            }
             else{
                 break;
             }
         }

        if(s.length()==0){
            skipWhiteSpace();
            for(auto token: tokenList) {
                if(_input.compare(pos, token.length(), token) == 0) {
                    pos = pos + token.length();
                    s = token;
                    break;
                }
            }
        }

        if(s.length()==0){
            s = nextDouble();
        }

        //std::cout << "test::"<<s <<std::endl;
        if(s.length()==0){
            throw std::string("next token doesn't exist.");
        }

        return s;
        // return next token.
        // throw exception std::string "next token doesn't exist." if next token not found.
    }

    std::string nextDouble() {
        std::string a = "";

        skipWhiteSpace();
        while(1){
            if((_input[pos] <= '9' && _input[pos] >= '0') || _input[pos] == '.') {
                a = a + _input[pos];
                pos++;
            }
            else{
                break;
            }
        }
      return a;
    }

    void skipWhiteSpace() {

        bool flag =true;

        while(flag)
        {
            if((_input[pos] == ' ' || _input[pos] == '\n')){
              flag = true;

            }
            else if( _input[pos] <= '9' && _input[pos] >= '0'){
              flag = false;
            }
            else if((_input[pos] >= 'a' && _input[pos] <= 'z') || (_input[pos] >= 'A' && _input[pos] <= 'Z')){
              flag = false;
            }
            else{
              for(auto token: tokenList) {
                  if(_input.compare(pos, token.length(), token) == 0) {
                      flag = false;
                      break;
                  }
              }
            }
            if(flag){
              pos++;
              if(pos == _input.length()){
                throw std::string("next token doesn't exist.");
              }
            }

        }

        //!@# $% ?
        //空白跟\n 要ignore , 不是數字 , 不是英文 都要ignore , 但是合法的token不能ignore
        //while( (_input[pos] == ' ' || _input[pos] == '\n'))
        //{
        //    pos++;
        //}

    }


    bool isDone(){
      skipWhiteSpace();
      return pos == _input.length();
    }

    // you can add other public functions if you needed.
private:
    std::string _input;
    std::string::size_type pos = 0;
    const std::vector<std::string> tokenList = {"{","}","(",")",","};

};
