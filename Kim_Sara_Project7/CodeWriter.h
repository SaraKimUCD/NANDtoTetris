//  CodeWriter.h
//  Project 7

#ifndef CodeWriter_h
#define CodeWriter_h

#include "Parser.h"
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

class CodeWriter {
public:
    CodeWriter(string filename);
    ~CodeWriter();
    
    void setFileName(string fileName);
    void writeArithmetic(string commandTest);
    void WritePushPop(VM_Command commandTest, string segment, int index);
    void Close();
private:
    int label;
    ofstream outFile;
};

#endif /* CodeWriter_h */
