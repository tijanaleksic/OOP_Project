#include "Reader.h"
//#include "../include/Postfix.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;
/* 
7.napraviti exceptione tamo gde pise greska
*/

//konstruktor kojem prosledjujem filepath koji treba da ucita
Reader::Reader(const string& filepath){
    //inicijalizacija potrebnih promenljivih.
    string filepath2;

    //kreira test1.txt koji je laksi za ucitavanje
    filepath2= newFileUpdated(filepath);

    //otvaranje fajla za citanje(test1.txt)
    fstream inputFile(filepath2, ios::in);

    //potrebne promenljive
    int n=0;
    int numOfLines=numberOfLines(filepath)+1;

    // inicijalizacija sirine vectora
    infixs_.resize(numOfLines);
    postfixs_.resize(numOfLines);

    //while(inputFile.peek() != EOF) {
    //fstream inputFile(filepath, ios::in);
    string line;
    while (getline(inputFile, line)) {

        std::stringstream ss(line);
     
        // n vazi za red u kome smo i toliko ima ukupno promenljivih dodela i izraza!
        n+=1;
        cout<<"n  je "<<n<<endl;

        //zbog problema sa SigSegom sledeca linija sprecava da cita red koji ne postoji i nije alociran!
        if(n==numOfLines){break;}

        //citanje imena promenljivih u koje se smestaju vrednosti
        string memName;     
        string jednako;
        ss >> memName;
        ss >> jednako;
        //dodatnoinputFile>>memName;
        //char ni;
        //inputFile>> ni;//not important =!
        cout<< "mem Name je "<<memName<<endl;
        cout << "jednako je" << jednako<<endl;

        //vadjenje izraza iz fajla x= a+b daje a+b
        string x;//bilo char
        vector <string> pomocno;
        int item=0;
        //int duzina=line.
        while (ss>>x) {
            //ss>>x;
            if(x!=" "){    
                item+=1;
                //pomocno.resize(item);        
                pomocno.push_back(x);          
                cout<<"x je "<<x<<endl;
            }           
        }

        //dodeljivanje reda u infix i njegov postfix u postfixs_ 
        infixs_[n]=pomocno;
        item=0;
        postfixs_[n]=toPostfix(pomocno);
        postfixs_[n].push_back(memName);
        postfixs_[n].push_back("=");
        cout<<"gotov postfix ";
        for(int i =0 ;i < postfixs_[n].size();i++){
            cout<<postfixs_[n][i];
        }
        cout<<endl;
    }
    inputFile.close();
}

//funkcija vraca broj linija u fajlu zbog problema sa alokacijom memorije
int Reader::numberOfLines(string filepath){
    int num = 0;
    string line;
    ifstream myfile(filepath);
   
    while (getline(myfile, line)){
        ++num;
    }
    return num;
    myfile.close();
    

}

//ispravlja sranja u opstem slucaju da bi fajl bio prilagodjen i citljiv programu
string Reader::newFileUpdated(string filepath){
    string filepath2;
    filepath2=filepath.substr(0,filepath.size()-4)+"1.txt";
    ofstream outputFile(filepath2);
    
    ifstream myfile(filepath);
    char x;
    while(myfile.peek() != EOF){
        if(myfile.peek()=='\n'){
            outputFile<< '\n';

        }
        myfile>>x;
        //if(myfile.peek()==EOF){break;}
        if(x=='^' || x=='+' ||x=='-' ||x=='*' ||x=='=' ||x=='/'){
            outputFile << ' ';
            outputFile << x;
            outputFile << ' ';
        }else{
            outputFile<<x;

        }
    }

    myfile.close();
    outputFile.close();
    return filepath2;
}

//destruktor napisi
Reader::~Reader()
{
}

// pravi postfix izraza
vector <string> Reader::toPostfix(vector <string> infix){
    //inicijalizacija stvari koje su potrebne,po uzoru na asp 72 str
    stack <string> stack;
    vector <string> postfix_;
    string x;
    int rank=0;
    string next=infix.at(0);
    int i=0;
     while(true) {
        if(i<infix.size()){
            i+=1;
        }else{
            break;
        }

        //ako je operand ubacuj prvo na stek to
        if(operandChecker(next)){
            postfix_.push_back(next);
            rank+=1;
            cout<<next;
        }else{
            while (!stack.empty()&&(inputPriority(next)<=stackPriority(stack.top()))){
                if(!(!stack.empty()&&(inputPriority(next)<=stackPriority(stack.top())))){break;}
                x=stack.top();
                cout<<"na steku je x sa vrednosti ="<<x<<endl;
                stack.pop();
                postfix_.push_back(x);
                rank=rank+rang(x);
                if(rank<1){
                    cout<<"neispravan ulaz while stek i prioritet"<<endl;
                }
            }
            if(next!=")"){
                stack.push(next);
            }else{
                x=stack.top();
                stack.pop();
            }
        }
        if(i!=infix.size()){
        next=infix.at(i);}
    }
    
    while (!stack.empty()){
        x=stack.top();
        stack.pop();
        postfix_.push_back(x);
        rank=rank+rang(x);
    }
    if(rank!=1){
        cout<<"Doslo je do greske: Neispravan ulaz";
    }
    return postfix_;

}

//proverava da l je operand ili operator
int Reader::operandChecker(string op){
    if(op=="+" || op=="*"|| op=="^" || op==")"|| op=="("|| op=="-"|| op=="."){
        return 0;
    }else{
        return 1;
    }
}

//vraca vrednost za inputPriority tj prioriteta ulaza
int Reader::inputPriority(string op){
   if(op == "+" /*|| op == '-'*/) {
      return 2;              
   }else if(op == "*" /*|| op == '/'*/) {
      return 3;           
   }else if(op == "^") {
      return 5;            
   }else if(op == "("){
      return 6;
   }else if(op == ")"){
      return 1;
   }else if(op == "."){
      return 7;
   }else{
      return -1;
      cout<<"doslo je do greske: znak koji nema inputPriority";
   }
}

//vraca prioritet na steku za izlaz
int Reader::stackPriority(string op){
   if(op == "+" /*|| op == '-'*/) {
      return 2;              
   }else if(op == "*" /*|| op == '/'*/) {
      return 3;           
   }else if(op == "^") {
      return 4;            
   }else if(op == "("){
      return 0;
   }else{
      return -1;
      cout<<"doslo je do greske: znak koji nema stackPriority";
   }
}

//vraca rang koji treba oduzeti pirlikom skidanja sa steka
int Reader::rang(string op){
    if(op == "+" /*|| op == '-'*/ || op == "^" || op == "*" /*|| op == '/'*/) {
        return -1;              
    }else{
        return 0;    
        cout<<"doslo je do greske: nema ranga datog operatora";       
   }

}

//vraca vektor imena
vector <string> Reader::getMemNames(){
    return memNames_;
}

//vraza postfixe
vector <vector<string>> Reader::getPostfixs(){ 
    return postfixs_;
}