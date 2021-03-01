 #ifndef MACHINE_H_
 #define MACHINE_H_
 #include <string>
 #include <vector>
 #include "Compiler.h"
 #include "Event.h"
 #include "Myinterface.h"
 #include "Sched.h"
class AritmeticOperation;
 using namespace std;

 typedef struct mempriority{
   string name;
   int priority;

 }memPriority;
 class Machine
 {
 public:
    Machine(const Machine&)=delete;
    Machine& operator=(const Machine&)=delete;
    static Machine& getInstance(){
        static Machine instance;
        return instance;
    }     
    int isReady(imfData x);
    bool doneAll();
    void initialize(const string& filepath);
    bool  checkInput(string input);
    void readConfig();
    void sched();
    void exec(const string& filepath);
    void updateValues(string name,string value);
    //advanced dodato
    void getImfForAdvanced();//kurac
    void incrementPriorityByName(string name);//kuracc
    int PriorityByName(string name);//kurac
    ~Machine();
 private:
    Machine()=default;
    vector <imfData> imf;
    vector <memPriority> priority;
    vector <AritmeticOperation*> itelem;
    double Ta=0;
    double Tm=0;
    double Tw=0;
    int Nw=0;
    double Te=0;
    string compilation="simple";
 };
 
 
 #endif
 