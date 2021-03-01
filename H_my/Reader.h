#ifndef READER_H_
#define READER_H_ 

#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Reader{
public:
    Reader(const string& filepath);
    int numberOfLines(string filepath);
    string newFileUpdated(string filepath);
    vector <string> toPostfix(vector <string> infix);
    int inputPriority(string op);
    int stackPriority(string op);
    int rang(string op);
    int operandChecker(string op);
    vector <string> getMemNames();
    vector <vector<string>> getPostfixs();
    ~Reader();
private:
    vector <vector <string>> infixs_;
    vector <string> memNames_;
    vector <vector <string>> postfixs_;
};
#endif