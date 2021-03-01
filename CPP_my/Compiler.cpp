#include "Compiler.h"


#include <stack>
#include <fstream>

using namespace std;
Compiler::Compiler(const string& filepath){
    
    //pravljenje redera koji ce dati sve infixe postfixe i srediti fajl
    Reader* reader = new Reader(filepath);
    vector <vector<string>> posfixs;

    //otvaranje fajla za upis
    ofstream outputFile(filepath.substr(0,filepath.size()-4)+".imf");

    //uzimanje napravljenog postfixa
    posfixs=reader->getPostfixs();
    stack <string> queue; 
    string a,b;
    int itok=1;
    int iw=1;     
    for (int it = 0.; it < posfixs.size(); it++) {// za svaki red
        for(int it2=0;it2<posfixs[it].size();it2++){//za svaku jednacinu
            string a= posfixs[it][it2];
            if(a=="="){
                b=queue.top();
                queue.pop();
                a=queue.top();
                queue.pop();
                cout<<"["<<iw<<"] "<<"= "<<b<<" "<<a<<endl;
                outputFile<<"["<<iw<<"] "<<"= "<<b<<" "<<a<<endl;
                iw++;
                string tname2="t"+to_string(iw);
                imfData imfx;
                imfx.firstop=b;
                imfx.id=iw;
                imfx.secondop=a;
                imfx.op="=";
                imfx.token="none";
                imfx.prepare="0";
                imf.push_back(imfx);

            }else if(a=="+"){
                b=queue.top();
                queue.pop();
                a=queue.top();
                queue.pop();
                string tname="t"+to_string(itok);
                tokens.push_back (Token(tname,0,a,"+",b));
                queue.push(tname);
                cout<<"["<<iw<<"] "<<"+ "<<"t"<<itok<<" "<<a<<" "<<b<<endl;
                outputFile<<"["<<iw<<"] "<<"+ "<<"t"<<itok<<" "<<a<<" "<<b<<endl;
                itok++;
                iw++;
                imfData imfx;
                imfx.firstop=a;
                imfx.id=iw;
                imfx.secondop=b;
                imfx.op="+";
                imfx.token=tname;
                imfx.prepare="0";
                imf.push_back(imfx);       
            }else if(a=="-"){
                b=queue.top();
                queue.pop();
                queue.push("-"+b);
                cout<<"["<<iw<<"] "<<"- "<<"t"<<itok<<" "<<a<<" "<<b<<endl;
                imfData imfx;
                imfx.firstop="0";
                imfx.id=iw;
                imfx.secondop=b;
                imfx.op="-";
                imfx.token="-"+b;
                imfx.prepare="0";
                
            }else if(a=="*"){
                b=queue.top();
                queue.pop();
                a=queue.top();
                queue.pop();
                string tname="t"+to_string(itok);
                tokens.push_back(Token(tname,0,a,"*",b));
                queue.push(tname);
                cout<<"["<<iw<<"] "<<"* "<<"t"<<itok<<" "<<a<<" "<<b<<endl;
                outputFile<<"["<<iw<<"] "<<"* "<<"t"<<itok<<" "<<a<<" "<<b<<endl;
                itok++;iw++;
                imfData imfx;
                imfx.firstop=a;
                imfx.id=iw;
                imfx.secondop=b;
                imfx.op="*";
                imfx.token=tname;
                imfx.prepare="0";
                imf.push_back(imfx);

            }else if(a=="^"){
                b=queue.top();
                queue.pop();
                a=queue.top();
                queue.pop();
                string tname="t"+to_string(itok);
                tokens.push_back(Token(tname,0,a,"^",b));
                queue.push(tname);
                cout<<"["<<iw<<"] "<<"^ "<<"t"<<itok<<" "<<a<<" "<<b<<endl;
                outputFile<<"["<<iw<<"] "<<"^ "<<"t"<<itok<<" "<<a<<" "<<b<<endl;
                itok++;iw++;
                imfData imfx;
                imfx.firstop=a;
                imfx.id=iw;
                imfx.secondop=b;
                imfx.op="^";
                imfx.token=tname;
                imfx.prepare="0";
                imf.push_back(imfx);
            }else if(a=="/"){
                b=queue.top();
                queue.pop();
                a=queue.top();
                queue.pop();
                string tname="t"+to_string(itok);
                tokens.push_back(Token(tname,0,a,"/",b));
                queue.push(tname);
                cout<<"["<<iw<<"] "<<"/ "<<"t"<<itok<<" "<<a<<" "<<b<<endl;
                outputFile <<"["<<iw<<"] "<<"/ "<<"t"<<itok<<" "<<a<<" "<<b<<endl;
                itok++;iw++;
                imfData imfx;
                imfx.firstop=a;
                imfx.id=iw;
                imfx.secondop=b;
                imfx.op="/";
                imfx.token=tname;
                imfx.prepare="0";
                imf.push_back(imfx);
            }else{
                queue.push(a);            
            }
        }
    }     
    outputFile.close();
}

//destruktor
Compiler::~Compiler()
{
}