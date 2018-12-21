//  main.cpp
//  CSCI 2940- nand2tetris Project 8
//  Sara Kim

#include "Parser.h"
#include "CodeWriter.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    string outFileName;
    unsigned long findDot;
    bool checkFile;
    int lineNum = 1;
    CodeWriter code(outFileName);
    Parser parse(outFileName);
    
    for(int i = 1; i < argc; i++) {
        // find the dot to get only the file name
        outFileName = argv[i];
        findDot = outFileName.find(".", 0);
        outFileName = outFileName.substr(0, findDot);
        parse.setFileName(outFileName);
        
        // For the output file append .asm and write to FILE_NAME.asm
        outFileName = outFileName + ".asm";
        code.setFileName(outFileName);
        
    // while loop to advance through the file and parse each command type
    // depending on the command type, it is translated to asm language using CodeWriter
        while(true) {
            parse.advance();
            
            // This if loop checks to see if the end of the file has been reached
            // If there are no more commands left, break out of loop
            checkFile = parse.hasMoreCommands();
            if(!checkFile){
                break;
            }
            
            if(parse.commandType() == C_ARITHMETIC) {
                code.writeArithmetic(parse.arg1());
            }
            
            else if(parse.commandType() == C_PUSH) {
                code.WritePushPop(C_PUSH, parse.arg1(), parse.arg2());
            }
            
            else if(parse.commandType() == C_POP) {
                code.WritePushPop(C_POP, parse.arg1(), parse.arg2());
            }
            // Project 8: parse and translate for
            // C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL
            else if(parse.commandType() == C_LABEL) {
                code.writeLabel(parse.arg1());
            }
            
            else if(parse.commandType() == C_GOTO){
                code.writeGoto(parse.arg1());
            }
            
            else if(parse.commandType() == C_IF){
                code.writeIf(parse.arg1());
            }
            
            else if(parse.commandType() == C_FUNCTION){
                code.writeFunction(parse.arg1(), parse.arg2());
            }
            
            else if(parse.commandType() == C_RETURN){
                code.writeReturn();
            }
            
            else if(parse.commandType() == C_CALL){
                code.writeCall(parse.arg1(), parse.arg2());
            }
            
            else if(parse.commandType() == VM_NO_COMMAND){
                
            }
            else{
                code.writeError(lineNum);
            }
            lineNum++;
        }           // while loop end
        code.Close();
    }
}

