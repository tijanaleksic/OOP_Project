#ifndef COMPILER_H_
#define COMPILER_H_

#include <string>

#include "Reader.h"
#include "Token.h"

using namespace std;
//klasa koja sluzi da kompajlira i napravi .imf file koji je zapravo redosled operacija
typedef struct imfdata{
    int id;//iw
    string firstop;//prvi operand
    string secondop;//drugi operand
    string op;//operator
    string token;
    bool prepare;
}imfData;

class Compiler{
public:
    Compiler(const string& filepath);
    vector <imfData> getImf(){return imf;}
    ~Compiler();
private:
    vector <Token> tokens;
    vector <imfData> imf;
};

#endif
