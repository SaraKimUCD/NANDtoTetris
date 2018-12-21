//  Parser.cpp
//  Project 7

#include "Parser.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

/************************************************************
*                   Parser(string filename)
* Opens the input file/stream and gets ready to parse it.
*************************************************************/
Parser::Parser(string filename) {
    filename = filename + ".vm";
    fileIn.open(filename.c_str());
}
/************************************************************
*                   ~Parser()
* Closes the output file/stream that was parsed
*************************************************************/
Parser::~Parser() {
    fileIn.close();
}

/************************************************************
 *               bool hasMoreCommands()
 * Returns true only if file has more commands
 *************************************************************/
bool Parser::hasMoreCommands() {
    return !fileIn.eof();
}

/************************************************************
*                   void advance()
* Reads the next command from the input
* and makes it the current command.
* Should be called only if hasMoreCommands is true.
* Initially there is no current command.
*************************************************************/
void Parser::advance() {
    if(hasMoreCommands()){
        getline(fileIn >> ws, command);
        // Erase any comments from the file line by finding "//"
        if(command.find("//") != string::npos){
            command.erase(command.find("//"));
        }
    }
}

/************************************************************
*                   VM_Command commandType()
* Returns the type of the current VM command.
*************************************************************/
VM_Command Parser::commandType() {
    // All commands will have their command type written first on each line
    // So to test the command type, only need to compare the type and not whole command line
    string twoLetters = command.substr(0,2);
    string threeLetters = command.substr(0,3);
    string fourLetters = command.substr(0,4);
    
        // C_ARITHMETIC is returned for all arithmetic commands:
        // add, sub, neg, eq, gt, lt, and, or, not
        if(threeLetters == "add" || threeLetters == "sub" || threeLetters == "neg"
           || twoLetters == "eq" || twoLetters == "gt" || twoLetters == "lt"
           || threeLetters == "and" || twoLetters == "or" || threeLetters == "not") {
            return C_ARITHMETIC;
        }
    
        // C_PUSH or C_POP is returned for all memory access commands:
        // pop x, push y
        else if(threeLetters == "pop"){
            return C_POP;
        }
        else if(fourLetters == "push"){
            return C_PUSH;
        }
    return VM_NO_COMMAND;
}

/************************************************************
*                   string arg1()
* Returns the first arg. of the current command.
* In the case of C_ARITHMETIC, the command itself
* (add, sub, etc.) is returned.
*************************************************************/
string Parser::arg1() {
    unsigned long afterCommand;
    unsigned long afterArg2;
    unsigned long argLength;
    string onlyArg1;
    
    // if the command is C_ARITHMETIC, it will be the whole command line
    if(commandType() == C_ARITHMETIC){
        return command;
    }
    
    // else the argument will be whatever comes after the command in the line
    else {
        // typical command line follow format similar to COMMAND_TYPE ARG1 ARG2
        // so we want to only get the arg1 string between the command and arg2 integer
        // can use spaces, " ", to differentiate the words as ARG2
        afterCommand = command.find(" ");
        afterArg2 = command.find(" ", afterCommand+1);
        
        argLength = afterArg2-afterCommand-1;
        onlyArg1 = command.substr(afterCommand+1, argLength);
        return onlyArg1;
    }
}

/************************************************************
 *                  int arg2()
 * Returns the second argument of the current command.
 * Called only if the current command is C_PUSH/C_POP
 *************************************************************/
int Parser::arg2() {
    if(commandType() == C_PUSH || commandType() == C_POP){
        unsigned long afterCommand;
        unsigned long afterArg1;
        unsigned long lineEnd;
        unsigned long argLength;
        string temp;
        int intTemp;
        
        // command line format is COMMAND_TYPE ARG1 ARG2
        // so we want to only get the integer after the ARG1 string
        afterCommand = command.find(" ");
        afterArg1 = command.find(" ", afterCommand+1);
        lineEnd = command.find(" ", afterArg1+1);
        
        argLength = lineEnd-afterArg1-1;
        temp = command.substr(afterArg1+1, argLength);
        
        // need to convert the found string into integer to return
        intTemp = stoi(temp);
        return intTemp;
    }
    return 0;
}
