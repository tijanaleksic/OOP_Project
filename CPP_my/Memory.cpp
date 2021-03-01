#include "Memory.h"

#include <iostream>
#include <fstream>

using namespace std;

//vectoru nameAndValue_ dodeljuje clan za prosledjenu vrednost
void Memory::setValue(string namenow,double valuenow){
    memVal x;
    x.name=namenow;
    x.value=valuenow;
    cout << "kurac name" << endl;
    nameAndValue_.push_back(x);

    //broj koji predjstavlja koliko se istovremeno upisuje clanova u memoriju dekrementira za jedan jer se upisao jedan elem
    decrementParalel();
}

//pozivanje ispisa memorije u filepath koji se prosledjuje
//podrazumeva se prosledjivanje test.txt pa se oduzima i dodaje .mem
void Memory::writeToMemFile(const string& filepath3){
    ofstream outputFile(filepath3.substr(0,filepath3.size()-4)+".mem");
    for (int i = 0; i < nameAndValue_.size(); i++){
        cout<<"ispiujem u mem file "<<nameAndValue_[i].name<<" = "<<nameAndValue_[i].value<<endl;
        outputFile<<nameAndValue_[i].name<<" = "<<nameAndValue_[i].value<<endl;
        
    }    
    outputFile.close();
}
//inkrementira broj paralelnih trenutnih upisa
void Memory::incrementParalel(){paralelwriting++;}

//proverava da l ima slobodno mesto za pisanje
bool Memory::checkParalel(int Nw){
    if(paralelwriting<Nw){
        return 1;
    }else{
        return 0;
    }
}
//inkrementira broj paralelnih trenutnih upisa
void Memory::decrementParalel(){paralelwriting--;}
Memory::~Memory(){
    

}