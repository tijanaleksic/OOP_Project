#include "Reader.h"
#include "Compiler.h"
#include "Memory.h"
#include "Machine.h"
#include "Logfile.h"
//#include "Sched.h"
int main(){
    //Machine machine= Machine("../test.txt");
    Machine::getInstance();
 
    Compiler compiler = Compiler ("../test.txt");
    Machine::getInstance().exec("../test.imf");
    Memory::getInstance().writeToMemFile("../test.txt");
    Logfile::getInstance().writeLogData("../test.log");
    //Reader reader= Reader("../test.txt");
}
