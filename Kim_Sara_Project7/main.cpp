//  main.cpp
//  CSCI 2940- nand2tetris Project 7
//  Sara Kim

// *** NOTE ***
//  Function details and program instructions taken from Virtual Machine Part 1 ppt
//  and The Elements of Computing Systems

#include "Parser.h"
#include "CodeWriter.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    string outFileName;
    unsigned long findDot;
    CodeWriter code(outFileName);
    bool checkFile;
    
     // find the dot to get only the file name
        outFileName = argv[argc-1];
        findDot = outFileName.find(".", 0);
        outFileName = outFileName.substr(0, findDot);
        Parser parse(outFileName);
    // For the output file append .asm and write to FILE_NAME.asm
        outFileName = outFileName + ".asm";
        code.setFileName(outFileName);
    
    // while loop to advance through the file and parse each command type
    // depending on the command type, it is translated to asm language using CodeWriter
    while(true) {
        parse.advance();
        if(parse.commandType() == C_ARITHMETIC) {
            code.writeArithmetic(parse.arg1());
        }
        
        else if(parse.commandType() == C_PUSH) {
            code.WritePushPop(C_PUSH, parse.arg1(), parse.arg2());
        }
        
        else if(parse.commandType() == C_POP) {
            code.WritePushPop(C_POP, parse.arg1(), parse.arg2());
        }
        
        // This if loop checks to see if the end of the file has been reached
        // If there are no more commands left, break out of loop
        checkFile = parse.hasMoreCommands();
        if(!checkFile){
            break;
        }
    }           // while loop end
    code.Close();
}
