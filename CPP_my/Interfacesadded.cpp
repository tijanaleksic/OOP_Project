#include "Myinterface.h"
#include "Memory.h"
#include "Logfile.h"


//proverava da l je element spreman da se prosledi na scheduler
bool AritmeticOperation::isReady(){
    bool x=Memory::getInstance().checkParalel(Nw_);
    if((!equal) && checkInput(port_[0])&&checkInput(port_[1])){
        return 1;
    }else if(checkInput(port_[1]) && (equal)&&x){
        return 1;
    }else{
        return 0;
    }
}

//vraca vrednost da li je operacija gotova
bool AritmeticOperation::getDone(){
      return done;
}
void AritmeticOperation::setDone() {
     done=1;
}

//poziva se da bi se izracunalo,i postavilo da se operacija izvrsila, interaguje sa TSS
void AritmeticOperation::notify (ID id) {
      done = 1;
      end = to_string((int) Scheduler::Instance()->getCurTime());
      cout << "aaaaa" << endl;
      string starttime=to_string((int)start);
      calculate();

      Machine::getInstance().updateValues(getName(),to_string((double)result));
      Logfile::getInstance().addLogelem(starttime,end,ID_);
}

//vraca ime promenljive,potrebno da bi se svuda promenila sa brojem
string AritmeticOperation::getName(){
      string nm;
      if(equal){nm=port_[0];}else{nm=name;}
      return nm;
}

//vraca string vrednost rezultata
string AritmeticOperation::getValue(){
      return to_string((double)result);

}

//postavlja pocetno vreme operacije.potrebno za ispis u log file
void AritmeticOperation::setStartTime(double startTime){
      start=startTime;
}

// poziva se unutar updateValue i interaguje da bi moglo da se na svim portovima aritmeticke operacije azurira
void AritmeticOperation::updatePorts(string name, string value){
    for(int i=0;i<port_.size();i++){
        if(port_[i]==name){
            port_[i]=value;
        }
    }
}

//funkcija koja proverava da l je stavljen broj na mesto ili je jos uvek 
bool AritmeticOperation:: checkInput(string input) {
    bool ok= false;
    int result;
    try {
        result = stof(input);
        //throw (stof(input));
        //result = stof(input);

        ok = true;
    }
    // Catch stoi errors
    catch (const std::invalid_argument & e) {/*ok=false;*/ return false;}
    catch (const std::out_of_range & e) {/*ok=false;*/ return false;}
    return true;//return ok;
}
//konstruktor za Addition,postavlja podrazumevane i prosledjene vrednosti
Addition::Addition(string first,string second,double Ta,string ID,string tokenname):Ta_(Ta){
    port_.push_back(first);
    port_.push_back(second);
    done=0;
    equal=0;
    ID_=ID;
    name=tokenname;    
}

//izracunavanje rezultata sa portova za Add
void Addition:: calculate(){
    firstnum=stof(port_[0]);
    secondnum=stof(port_[1]);
    result = (double)firstnum+secondnum;
}

//vraca postavljeno vreme za izracunavanje
double Addition::getTimeExec(){
    return Ta_;
}

//konstruktor za Multiplication,postavlja podrazumevane i prosledjene vrednosti
Multiplication::Multiplication(string first,string second,double Tm,string ID,string tokenname):Tm_(Tm){
    port_.push_back(first);
    port_.push_back(second);
    done=0;
    equal=0;
    ID_=ID;
    name=tokenname;
}

//izracunavanje rezultata sa portova za Mul
void Multiplication::calculate(){
    firstnum=stof(port_[0]);
    secondnum=stof(port_[1]);
    result = (double)firstnum*secondnum;
    
    
}

//vraca postavljeno vreme za izracunavanje
double Multiplication::getTimeExec(){
    return Tm_;
}


//konstruktor za Pow,postavlja podrazumevane i prosledjene vrednosti
Pow::Pow(string first,string second,double Te,string ID,string tokenname):Te_(Te){
    port_.push_back(first);
    port_.push_back(second);
    done=0;
    equal=0;
    ID_=ID;
    name=tokenname;
}
//izracunavanje rezultata sa portova za Pow
void Pow::calculate(){
    firstnum=stof(port_[0]);
    secondnum=stof(port_[1]);
    result = (double)pow(firstnum,secondnum);
    
}

//vraca postavljeno vreme za izracunavanje
double Pow::getTimeExec(){
    return Te_;
}

//konstruktor za Assignment,postavlja podrazumevane i prosledjene vrednosti
Assignment::Assignment(string first,string second,double Tw,int Nw,string ID):Tw_(Tw){
    Nw_=Nw;
    port_.push_back(first);
    port_.push_back(second);
    equal=1;
    ID_=ID;
    done = false;
}

//izracunavanje rezultata sa portova za Equal
void Assignment::calculate(){
    result=(double)stof(port_[1]);
    if(!checkInput(port_[0])){
    Memory::getInstance().setValue(port_[0],result);//ubacivanje u memoriju
    }
}

//vraca postavljeno vreme za izracunavanje
double Assignment::getTimeExec(){
    return Tw_;
}