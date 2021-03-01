#ifndef LOGFILE_H_
#define LOGFILE_H_
#include <string>
#include <vector>
using namespace std;

typedef struct Logelem{
    string start;
    string end;
    string ID;
}logElem;

class Logfile{
public:
    Logfile(const Logfile&)=delete;
    Logfile& operator=(const Logfile&)=delete;
    void sortLogdatastarting();
    static Logfile& getInstance(){
        static Logfile instance;
        return instance;
    } 
    void addLogelem(string startx,string endx,string idx);
    void writeLogData(string file);
    ~Logfile();
private:
    vector <logElem> logdata;
    Logfile()=default;
};



#endif