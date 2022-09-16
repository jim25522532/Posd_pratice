#ifndef SCANNER_H
#define SCANNER_H

#include <deque>
#include <string>
#include <sstream>
#include <vector>
class Scanner {
public:

    Scanner(std::string input): _input(input) {
      //std::cout << "input:" << input << std::endl;
      std::stringstream ss(input);
      std::string token;
      double num = 0.0;
      char c;


        //std::cout<< token << std::endl;
        /*if(token == "Ellipse" || token=="Rectangle" || token=="Triangle" || token =="CompoundShape" || token =="(" ||
        token =="{" || token=="}"){
          _token.push_back(token);
          token = "";
        }*/
        //判斷是不是數字
        if(c==',' || c==')'){
          token.pop_back();
          std::stringstream checknum(token);
          //轉換成功會得到1,則是個token
          if(checknum >> num){
            _token.push_back(token);
            token = "";
            token.push_back(c);
            _token.push_back(token);
          }

          else if((c==',' && _token.back()=="{") || c==',' && _token.back()==")"){
            token= "";
            token.push_back(c);
            _token.push_back(token);
          }
          token = "";
        }
      }


    void skipWhiteSpace() {
      while(_input[pos] == ' ' || _input[pos] == '\n') {
        pos++;
      }
    }

    bool isDone(){
      skipWhiteSpace();
      return pos == _input.length();
    }


    std::string nextToken() {

      std::string result = "";
      skipWhiteSpace();
      for(auto token: tokenList) {
        if(_input.compare(pos, token.length(), token) == 0) {
          pos = pos + token.length();
          result = token;
          break;
        }
      }

      if(result==""){
        result = nextDouble();
      }

      if(result==""){
        if(isDone()){
          std::cout << "test is done" <<std::endl;
          throw std::string("next char doesn't exist.");
        }
      }

      return result;
        // return next token.
        // throw exception std::string "next char doesn't exist." if next token not found.
    }

    std::string nextDouble() {
        std::string s = "";
        skipWhiteSpace();
        while(1){

            if((_input[pos] <= '9' && _input[pos] >= '0') || _input[pos] == '.' || _input[pos]=='-') {
                s = s + _input[pos];
                pos++;
            }
            else{
                break;
            }
        }
        return s;
    }

private:
  std::string _input;
  std::string::size_type pos = 0;
  const std::vector<std::string> tokenList = {"Ellipse", "Rectangle", "Triangle", "CompoundShape", "(" ,"{" , "," , ")","}"};
  std::deque<std::string> _token;
};

#endif
