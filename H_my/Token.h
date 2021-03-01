#ifndef TOKEN_H_
#define TOKEN_H_
//Token ima jedinstveno ime, realnu vrednost i identifikator operacije koja je proizvela vrednost.
#include <string>

using namespace std;
class Token{
public:
    Token():name_("fault"),value_(0){};
    Token(string name,float value,string first,string operationId,string second):name_(name),first_(first),second_(second),value_(value),operationId_(operationId){};
    //~Token();
private:
    string name_;
    string first_;
    string second_;
    float value_;
    string operationId_;
};
#endif