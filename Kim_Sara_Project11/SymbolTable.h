//  SymbolTable.h
//  CSCI 2940 - nand2tetris Project 11
//  Sara Kim

#ifndef SymbolTable_h
#define SymbolTable_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;

enum ST_KIND {sSTATIC, sFIELD, sARG, sVAR, NONE};
struct ST{
    string type;
    ST_KIND kind;
    int index;
};

class SymbolTable {
private:
    map<string, ST> classScope;     // table for class scope
    map<string, ST> subroutineScope;        // table for subroutinne scope
    
public:
    int staticIndex;
    int fieldIndex;
    int argIndex;
    int varIndex;

    SymbolTable();
    ~SymbolTable();
    
    void startSubroutine();
    void startClass();
    void Define(string name, string type, ST_KIND kind);
    int VarCount(ST_KIND kind);
    enum ST_KIND KindOf(string name);
    string TypeOf(string name);
    int IndexOf(string name);
};


#endif /* SymbolTable_h */
