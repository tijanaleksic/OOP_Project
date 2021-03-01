#ifndef MYINTERFACE_H_
#define MYINTERFACE_H_

#include <string>
#include <math.h>

#include "Machine.h"
using namespace std;
class Machine;

class AritmeticOperation : public ITimedElement{
public:
    virtual void calculate() = 0;
    bool isReady();
    void updatePorts(string name,string value);
    bool checkInput(string input) ;
    bool getDone();
    void setDone();
    void notify (ID id) override;
    string getName();
    string getValue();
    bool isEqual(){return equal;}
    virtual double getTimeExec() = 0;
    void setStartTime(double startTime);
protected:
    string ID_;
    double result;
    string name;
    vector<string> port_;
    double firstnum;
    double secondnum;
    bool done;
    string end;
    double start;
    bool equal;
    int Nw_;
};

//sabiranje dva broja
class  Addition: public AritmeticOperation{
public:
    Addition(string first,string second,double Ta,string ID,string tokenname);
    void calculate() override;
    double getTimeExec()override;
    ~Addition();
private:
    double Ta_;//kasnjenje
    
};

// mnozenje dva broja
class  Multiplication: public AritmeticOperation{
public:
    Multiplication(string first,string second,double Tm,string ID,string tokenname);
    void calculate() override;
    double getTimeExec()override;
    ~Multiplication();
private:
    double Tm_;//kasnjenje

};

//stepenovanje brojeva
class  Pow: public AritmeticOperation{
public:
    Pow(string first,string second,double Te,string ID,string tokenname);
    void calculate() override;
    double getTimeExec()override;
    ~Pow();
private:
    double Te_;//kasnjenje
};

//dodela vrednosti tokenu
class  Assignment: public AritmeticOperation{
public:
    Assignment(string first,string second,double Tw,int Nw,string ID);
    void calculate()override;
    double getTimeExec()override;
    ~Assignment();
private:
    
    double Tw_;//kasnjenje
};
#endif
