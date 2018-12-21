//  SymbolTable.cpp
//  CSCI 2940 - nand2tetris Project 11
//  Sara Kim

#include "SymbolTable.h"

/************************************************************
 *                      SymbolTable()
 * Creates new empty symbol table
 *************************************************************/
SymbolTable::SymbolTable(){
    staticIndex = 0;
    fieldIndex = 0;
    argIndex = 0;
    varIndex = 0;
}

/************************************************************
 *                      ~SymbolTable()
 * clears all symbol table
 *************************************************************/
SymbolTable::~SymbolTable() {
    classScope.clear();
    subroutineScope.clear();
}

/************************************************************
 *                      startSubroutine()
 * Starts new subroutine scope
 *************************************************************/
void SymbolTable::startSubroutine() {
    argIndex = 0;
    varIndex = 0;
    subroutineScope.clear();
}

/************************************************************
 *                      startClass()
 * Starts new subroutine scope
 *************************************************************/
void SymbolTable::startClass() {
    staticIndex = 0;
    fieldIndex = 0;
    classScope.clear();
}

/************************************************************
 *                      Define()
 * Defines new identifier of given name, type, and king, and
 * assigns it a running index.
 * STATIC and FIELD identifiers have class scope
 * ARG and VAR identifiers have subroutine scope
 *************************************************************/
void SymbolTable::Define(string name, string type, ST_KIND kind) {
    switch(kind) {
        case sSTATIC:
            classScope[name].type = type;
            classScope[name].kind = kind;
            classScope[name].index = staticIndex;
            staticIndex++;
            break;
            
        case sFIELD:
            classScope[name].type = type;
            classScope[name].kind = kind;
            classScope[name].index = fieldIndex;
            fieldIndex++;
            break;
            
        case sARG:
            subroutineScope[name].type = type;
            subroutineScope[name].kind = kind;
            subroutineScope[name].index = argIndex;
            argIndex++;
            break;
            
        case sVAR:
            subroutineScope[name].type = type;
            subroutineScope[name].kind = kind;
            subroutineScope[name].index = varIndex;
            varIndex++;
            break;
            
        case NONE:
            break;
    }
}

/************************************************************
 *                      VarCount()
 * Returns number of variables of given kind already defined
 * in the current scope
 *************************************************************/
int SymbolTable::VarCount(ST_KIND kind) {
    switch(kind) {
        case sSTATIC:
            return staticIndex;
            break;
        case sFIELD:
            return fieldIndex;
            break;
        case sARG:
            return argIndex;
            break;
        case sVAR:
            return varIndex;
            break;
        case NONE:
            return -1;
            break;
    }
}

/************************************************************
 *                      KindOf()
 * Returns kind of the named identifier in the current scope.
 * If identifier is unknown, returns NONE
 *************************************************************/
enum ST_KIND SymbolTable::KindOf(string name) {
    if(!(classScope.find(name) == classScope.end())) {
        return classScope[name].kind;
    }
    else if(!(subroutineScope.find(name) == subroutineScope.end())) {
        return subroutineScope[name].kind;
    }
    return NONE;
}

/************************************************************
 *                      TypeOf()
 * Returns type of named identifier in current scope
 *************************************************************/
string SymbolTable::TypeOf(string name) {
    string temp = "";
    if(!(classScope.find(name) == classScope.end())) {
        return classScope[name].type;
    }
    else if(!(subroutineScope.find(name) == subroutineScope.end())) {
        return subroutineScope[name].type;
    }
    return temp;
}

/************************************************************
 *                      IndexOf()
 * Returns index assigned to the named identifier
 *************************************************************/
int SymbolTable::IndexOf(string name) {
    if(!(classScope.find(name) == classScope.end())) {
        return classScope[name].index;
    }
    else if(!(subroutineScope.find(name) == subroutineScope.end())) {
        return subroutineScope[name].index;
    }
    return -1;
}


