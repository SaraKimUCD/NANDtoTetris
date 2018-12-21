//  main.cpp
//  CSCI 2940 - nand2tetris Project 6
//
//  To compile:
//  go into the Assembler_06 folder from command prompt/terminal
//  g++ *.cpp
//  ./a.out FILE_NAME.asm


#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

int main(int argc, char *argv[]) {
    string fileMain, outFile;
    
    unsigned long findDot;
    fileMain = argv[argc-1];
    //ifstream inputFile(fileMain);
    
    // find the dot to get only the file name and append .hack to it as the output file
    findDot = fileMain.find(".", 0);
    outFile = fileMain.substr(0, findDot) + ".hack";
    ofstream outputFile(outFile.c_str());

    // Start parsing
    Parser parse(fileMain);
    SymbolTable symTable;
    // lineCount to keep track of the position in file
    int lineCount = 0;
    bool checkFile;

    // First deal with the L_COMMAND
    // While loop continuosly checks whether the end of the file has been reached
    // if there are no more commmands, checkFile = false, so break out of loop
    while(true) {
        parse.advance();
        
        // if the command is either A_COMMAND or C_COMMAND
        if(parse.commandType() == 'A' || parse.commandType() == 'C'){
            lineCount++;
            //cout << lineCount << endl;
        }
        else if(parse.commandType() == 'L'){
            // first parse to get rid of all parentheses and only add the symbol
            symTable.addEntry(parse.symbol('L'), lineCount);
        }
        
        // This if loop checks to see if the end of the file has been reached
        // If there are no more commands left, break out of loop
        checkFile = parse.hasMoreCommands();
        if(!checkFile) {
            break;
        }
    }
    parse.closeFile(fileMain);

    // reset the checkFile to true
    checkFile = true;
    Parser parse2(fileMain);
    Code translate;
    
    while(true){
        parse2.advance();
        
        // if it is A_COMMAND...
        if(parse2.commandType() == 'A'){
            //cout << "command A" << endl;
            // all A_COMMAND starts with 0, a=0
            outputFile << '0';
            
            // Check if the symbol of A_COMMAND is a number
            // by using the find_first_not_of function
            unsigned long ifNum;
            ifNum = parse2.symbol('A').find_first_not_of("0123456789");
            if(ifNum == string::npos){
                // Use bitset to store the parsed binary, then convert to string to write out to file
                outputFile << bitset<15>(stoull(parse2.symbol('A'),nullptr)).to_string();
            }
            // else symbol of A_COMMAND is an address variable
            else {
                outputFile << bitset<15>(symTable.GetAddress(parse2.symbol('A')) ).to_string();
            }
            outputFile << endl;
        }

        // else symbol is a C_COMMAND
        // C_COMMAND is pretty simple...
        // Just need to follow the binary pattern and call each function accordingly
        // (1 1 1 a c1 c2 c3 c4 c5 c6 d1 d2 d3 j1 j2 j3)
        else if (parse2.commandType() == 'C'){
            // All C_COMMAND start with 111
            outputFile << "111";
            // Now write the comp (c1 c2 c3 c4 c5 c6) after parsing
            outputFile << translate.compCode(parse2.comp());
            // Next write the dest (d1 d2 d3) after parsing
            outputFile << translate.destCode(parse2.dest());
            // Lastly write to the file the jump (j1 j2 j3) after parsing
            outputFile << translate.jumpCode(parse2.jump());
            outputFile << endl;
        }
        
        // This if loop checks to see if the end of the file has been reached
        // If there are no more commands left, break out of loop
        checkFile = parse2.hasMoreCommands();
        if(!checkFile) {
            break;
        }
        
    }      // while loop end
    parse2.closeFile(fileMain);
}
