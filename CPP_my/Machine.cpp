#include "Machine.h"
#include "Compiler.h"
#include "Memory.h"
#include "Interfaces.h"

#include <fstream>
#include <sstream>
#include <string>
using namespace std;


// execute suzi da pokrene init while done sched ida pokrene processnow;
void Machine::exec(const string& filepath){

    //poziva ucitavanje configa
    readConfig();

    //pokrece inicijalizaciju da bi ucitao imf file i config file
    initialize(filepath);
     
    //sve dok ne obradi sve korake iz imf fajla nek pokrece shed
    while(!doneAll()){        
        sched();
        Scheduler::Instance()->processNow();
    }
    
}

//sched sluzi da proverava da li je nesto spremno i tada pravi dogadjaj tj procesuira ga
void Machine::sched(){
    for(int i=0;i<itelem.size();i++){
        if(itelem[i]->isReady()&& !(itelem[i]->getDone())){//ako je spreman i nije obradjen do sada...
            //cout<<"kreiram event " << i <<endl;
            itelem[i]->setDone();
            Event::create(itelem[i],itelem[i]->getTimeExec());
            if(itelem[i]->isEqual()){//jeste jednako
                Memory::getInstance().incrementParalel();
            }

            //postavlja pocetno vreme izvrsavanja
            itelem[i]->setStartTime(Scheduler::Instance()->getCurTime());               
        }
    }
}

//proverava da li su obradjeni svi elementi vectora itelem ako jesu vraca 1,ako nisu vraca 0
bool Machine::doneAll(){
    for(int i=0;i<itelem.size();i++){
        if(itelem[i]->getDone()==0){return 0;}
    }
    return 1;
}

//sluzi da postavi novu vrednost na sva mesta portova jer kasnije proverava na osnovu toga da li su spremni
void Machine::updateValues(string name,string value){
    for(int i=0;i<itelem.size();i++){
        itelem[i]->updatePorts(name,value);

        //ovo je ispis radi lakse provere sta radi kada
        //cout<<"itelem[i] nakon apdejta "<<itelem[i]->getValue() << " " << itelem[i]->getDone() << endl;
    }
}

//ucitava imf fajl i pokrece ucitavanje config file,na osnovu toga pravi itelem vector sa AritmeticOperation
void Machine::initialize(const string& filepath){

    fstream inputFile(filepath, ios::in);
  
    
    
    //inicijalizuje potrebne promenljive
    string id;
    string op;
    string firstop;
    string secondop;
    string name;
    int i=0;
    string line;

    //ucitava liniju po liniiju,tj operacije i njihov red u .imf
    while (getline(inputFile,line)) {

        std::stringstream ss(line);
        ss >>id;
        ss >> op;

        //proverava koja je operacija
        if(op=="="){
            ss>>firstop;
            ss>>secondop;
            itelem.push_back(new Assignment(firstop,secondop,Tw,Nw,id));
            memPriority me;
            me.name=firstop;
            me.priority=1;
            priority.push_back(me);//KURAC

            
        }else if(op=="+"){
            ss>>name;
            ss>>firstop;
            ss>>secondop;
            itelem.push_back(new Addition(firstop,secondop,Ta,id,name));
            //kurac
            //ako je prvi element abc vrednost
            if(!checkInput(firstop)){incrementPriorityByName(firstop);}
            if(!checkInput(secondop)){incrementPriorityByName(secondop);}
        }else if(op=="*"){
            ss>>name;
            ss>>firstop;
            ss>>secondop;
            //kurac
            //ako je prvi element abc vrednost
            if(!checkInput(firstop)){incrementPriorityByName(firstop);}
            if(!checkInput(secondop)){incrementPriorityByName(secondop);}
            //kurac kraj
            //ako je ukljuceno advanced smanjuje vreme izvrsavanja
            /*if((Ta<Tm)&&(compilation=="advanced")){
                itelem.push_back(new Multiplication(firstop,secondop,Ta,id,name));
            }else{*/
                itelem.push_back(new Multiplication(firstop,secondop,Tm,id,name));
            //}   
        }else if(op=="^"){
            ss>>name;
            ss>>firstop;
            ss>>secondop;
            //kurac
            //ako je prvi element abc vrednost
            if(!checkInput(firstop)){incrementPriorityByName(firstop);}
            if(!checkInput(secondop)){incrementPriorityByName(secondop);}
            //kurac kraj
            //ako je ukljuceno advanced smanjuje vreme izvrsavanja
            /*if((compilation=="advanced")&&(Ta<Te)&&(Ta<Tm)){
                itelem.push_back(new Pow(firstop,secondop,Ta,id,name));
            }else if((compilation=="advanced")&&(Tm<Te)&&(Tm<Ta)){
                itelem.push_back(new Pow(firstop,secondop,Tm,id,name));
            }else{*/
                itelem.push_back(new Pow(firstop,secondop,Te,id,name));
            //}   
        }
    }
    //kurac
    if(compilation =="advanced"){
        getImfForAdvanced();//zameni mesta po prioritetu
    }
}

//cita config.txt fajl i upisuje u privatne promenljive Ta,Tm,Tw,Te,Nw i compilation
void Machine::readConfig(){
    fstream inputFile("../config.txt", ios::in);
    string input,equal,value;
    while(inputFile.peek()!=EOF){
        inputFile>>input;
        if(input=="Ta"){
            inputFile>>equal;
            inputFile>>value;
            Ta = stoi(value);
            cout<<"Ta je "<<Ta<<endl;
        }else if(input=="Tw"){
            inputFile>>equal;
            inputFile>>value;
            Tw = stoi(value);
            cout<<"Tw je "<<Tw<<endl;
        }else if(input=="Te"){
            inputFile>>equal;
            inputFile>>value;
            Te = stoi(value);
            cout<<"Te je "<<Te<<endl;
        }else if(input=="Tm"){
            inputFile>>equal;
            inputFile>>value;
            Tm = stoi(value);
            cout<<"Tm je "<<Tm<<endl;
        }else if(input=="Nw"){
            inputFile>>equal;
            inputFile>>value;
            Nw = stoi(value);
            cout<<"Nw je "<<Nw<<endl;
        }else if(input=="compilation"){
            inputFile>>equal;
            inputFile>>value;
            compilation= value;
            cout<<value<<endl;
        }
    }
}

//proverava da l je element spreman da se prosledi na scheduler
int Machine::isReady(imfData x){
    if(checkInput(x.firstop)&&checkInput(x.secondop)&& (x.op!="=")){
        return 1;
    }else if(checkInput(x.secondop) && (x.op=="=")){
        return 2;
    }else{
        return 0;
    }
}



//funkcija koja proverava da l je stavljen broj na mesto ili je jos uvek 
bool Machine:: checkInput(string input) {
    bool ok= false;
    int result;
    try {
        result = stof(input);
        ok = true;
    }
    // Catch stof errors
    catch (const std::invalid_argument & e) {ok=false;}
    catch (const std::out_of_range & e) {ok = false;}
    return ok;
}

//kurac dve funkcije je ispod
//inkrementira kada se pojavi negde u fajlu ime promenljive koje se cuva
void Machine::incrementPriorityByName(string name){
    for (int i = 0; i < priority.size(); i++)
    {
        if(priority[i].name==name){
            priority[i].priority++;
        }
    }
    
}
//kurac 
int Machine::PriorityByName(string name){
    for (int i = 0; i < priority.size(); i++)
    {
        if(priority[i].name==name){
            return priority[i].priority;
        }
    }
    
}
//kurac
void Machine::getImfForAdvanced(){
    for (int i = 0; i < itelem.size(); i++){
        if(itelem[i]->isEqual()){//ako je jednako tj dodela
            for (int j = 0; j < itelem.size(); j++){
                if((j!=i)&&(itelem[j]->isEqual())){
                    if(PriorityByName(itelem[i]->getName())>PriorityByName(itelem[j]->getName())){
                        //ako je veci prioritet swapuj ako ne ostavi tako
                        swap(itelem[i],itelem[j]);
                        cout<<"swapujem elemente i :"<<i<<" i j :"<<j<<endl;
                    }
                }
            }
        }
    }
    

    
}

Machine::~Machine(){


}
