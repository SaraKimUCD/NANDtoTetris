//  CodeWriter.h
//  Project 8

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
    // Project 8
    void writeInit();
    void writeLabel(string sLabel);
    void writeGoto(string sLabel);
    void writeIf(string sLabel);
    void writeCall(string functionName, int numArgs);
    void writeReturn();
    void writeFunction(string functionName, int numArgs);
    void writeError(int lineNum);
    void Close();
private:
    int label;
    ofstream outFile;
};

#endif /* CodeWriter_h */

