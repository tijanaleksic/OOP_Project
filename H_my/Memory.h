#ifndef MEMORY_H_
#define MEMORY_H_

#include <string>
#include <vector>
#include <iostream>


using namespace std;
//definisanje strukture za lakse pamcenje
typedef struct MemVal{
    string name;
    double value;
}memVal;

class Memory{
public:
    Memory(const Memory&)=delete;
    Memory& operator=(const Memory&)=delete;
    static Memory& getInstance(){
        static Memory instance;
        return instance;
    } 
    void writeToMemFile(const string& filepath3);
    void incrementParalel();
    bool checkParalel(int Nw);
    void decrementParalel();
    void setValue(string namenow,double valuenow);
    ~Memory();
private:
    Memory()=default;
    int paralelwriting=0;
    vector <memVal> nameAndValue_;
};




#endif