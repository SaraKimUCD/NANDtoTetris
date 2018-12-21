//  Parser.h
//  Project 7

#ifndef Parser_h
#define Parser_h

#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

enum VM_Command {VM_NO_COMMAND = 0, C_ARITHMETIC, C_PUSH, C_POP};

class Parser {
public:
    Parser(string filename);
    ~Parser();
    
    bool hasMoreCommands();
    void advance();
    VM_Command commandType();
    string arg1();
    int arg2();
    
private:
    string command;             // commands parsed from file
    ifstream fileIn;            // file to parse
};




#endif /* Parser_h */
