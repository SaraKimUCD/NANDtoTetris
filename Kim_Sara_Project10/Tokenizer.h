//  Tokenizer.h
//  CSCI 2940 - nand2tetris Project 10
//  Sara Kim

#ifndef Tokenizer_h
#define Tokenizer_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum token {KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST, TNONE};
enum key {CLASS, METHOD, FUNCTION, CONSTRUCTOR, INT, BOOLEAN, CHAR, VOID, VAR, STATIC, FIELD, LET, DO, IF, ELSE, WHILE, RETURN, KTRUE, KFALSE, KNULL, KTHIS, KNONE};

class Tokenizer {
public:
    Tokenizer(string filename);
    ~Tokenizer();
    void setFilename(string filename);
    bool hasMoreTokens();
    void advance();
    bool checkInt(string check);
    token tokenType();
    key keyWord();
    char symbol();
    string identifier();
    int intVal();
    string stringVal();
private:
    ifstream fileIn;
    string saveFile;
    string current;
    
};

#endif /* Tokenizer_h */
