//  main.cpp
//  CSCI 2940 - nand2tetris Project 10
//  Sara Kim

#include "Parser.h"
#include "Tokenizer.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    string outFile;
    unsigned long findDot;
    //bool checkFile;

    for(int i = 1; i < argc; i++) {
        outFile = argv[i];
        findDot = outFile.find(".", 0);
        outFile = outFile.substr(0, findDot);
    }
    Parser parser(outFile);
    return 0;
}
