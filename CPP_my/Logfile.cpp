#include "Logfile.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <string>

using namespace std;

//dodaje element za ispis na vector logdata
void Logfile::addLogelem(string startx,string endx,string idx){
    logElem x;
    x.start=startx;
    x.end=endx;
    x.ID=idx;
    logdata.push_back(x);

}

//poziva se da bi se ispisalo sve iz vectora u log file ,podrazumeva se da mu se prosledjuje test.log
void Logfile::writeLogData(string file){
    //file1=file.substr(0,filepath3.size()-4)+".log"; // u slucaju da mu se prosledjuje test.txt
    ofstream outputFile(file);
    sortLogdatastarting();
    for (int i = 0; i < logdata.size(); i++){
        cout<<"ispiujem u log  file "<<logdata[i].ID<<" ("<<logdata[i].start<<"-"<<logdata[i].end<<")ns"<<endl;
        outputFile<<logdata[i].ID<<" ("<<logdata[i].start<<"-"<<logdata[i].end<<")ns"<<endl;   
    }
    outputFile.close(); 
}
void Logfile::sortLogdatastarting() {
    for (int i = 0; i < logdata.size(); i++) {
        for (int j = 0; j < logdata.size(); j++) {
            if (stoi(logdata[j].start) > stoi(logdata[i].start)) {
                logElem a=logdata[j];
                logElem b=logdata[i];
                logdata[i] = a;
                logdata[j] = b;

            }
            if ((stoi(logdata[j].start) == stoi(logdata[i].start)) && (stoi(logdata[i].end) < stoi(logdata[j].end))) {
                logElem a = logdata[j];
                logElem b = logdata[i];
                logdata[i] = a;
                logdata[j] = b;
            }
            else if (stoi(logdata[j].start) == stoi(logdata[i].start) && (stoi(logdata[j].end) == stoi(logdata[i].end))) {
                int k1 =logdata[j].ID.size() - 1;
                int k2= logdata[i].ID.size() - 1;
                int x = stoi(logdata[j].ID.substr(1, k1));
                int y = stoi(logdata[i].ID.substr( 1, k2));
                if (x > y) {
                    logElem a = logdata[j];
                    logElem b = logdata[i];
                    logdata[i] = a;
                    logdata[j] = b;
                    
                }
            }
        }
    }

}


//destruktor
Logfile::~Logfile()
{
}
