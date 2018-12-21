//  Parser.h
//  CSCI 2940 - nand2tetris Project 10
//  Sara Kim

#ifndef Parser_h
#define Parser_h

#include "Tokenizer.h"
#include <stdio.h>
#include <string>
#include <fstream>


using namespace std;

class Parser {
public:
    Parser(string filename);
    ~Parser();
    void CompileClass();
    void CompileClassVarDec();
    void CompileSubroutine();
    void CompileParameterList();
    void CompileVarDec();
    void CompileStatements();
    void CompileDo();
    void CompileLet();
    void CompileWhile();
    void CompileReturn();
    void CompileIf();
    void CompileExpression();
    void CompileTerm();
    void CompileExpressionList();
private:
    ofstream fileOut;
    string saveName;
};
#endif /* Parser_h */
