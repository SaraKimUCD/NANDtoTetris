//  Parser.cpp
//  CSCI 2940 - nand2tetris Project 10
//  Sara Kim & Grace Kang

//  Compilation Engine: gets input from Tokenizer and writes
//  parsed structure into output filestream

#include "Parser.h"
#include "Tokenizer.h"

using namespace std;
string test;

Tokenizer jackT(test);

/************************************************************
 *                   Parser(string filename)
 * Creates compilation engine with given input/output.
 *************************************************************/
Parser::Parser(string filename) {
    saveName = filename;
    jackT.setFilename(filename);
    filename = filename + ".xml";
    fileOut.open(filename.c_str());
    CompileClass();
}

/************************************************************
 *                   ~Parser(string filename)
 * Close all files
 *************************************************************/
Parser::~Parser() {
    fileOut.close();
}

/************************************************************
 *                      CompileClass()
 *  Compiles a complete class
 *************************************************************/
void Parser::CompileClass() {
    // start with the class header
    fileOut << "<class>" << endl;
    jackT.advance();
    // Use .xml files to know the layout structure of how each
    // keyword, identifier, symbol.. etc. are written
    //while (jackT.keyWord() == CLASS) {
        fileOut << "<keyword> " << "class" << " </keyword>" << endl;
        jackT.advance();
    //}
    //while (jackT.tokenType() == IDENTIFIER) {
        fileOut << "<identifier> " << jackT.identifier() << " </identifier>" << endl;
        jackT.advance();
    //}
    //while (jackT.symbol() == '{'){
        fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
        jackT.advance();
    //}
    while ( jackT.tokenType() == KEYWORD && (jackT.keyWord() == STATIC || jackT.keyWord() == FIELD) ) {
        CompileClassVarDec();
    }
    while ( jackT.tokenType() == KEYWORD && (jackT.keyWord() == CONSTRUCTOR || jackT.keyWord() == FUNCTION || jackT.keyWord() == METHOD) ) {
        CompileSubroutine();
    }
    // all class is within { }
    fileOut << "<symbol> } </symbol>" << endl;
    fileOut << "</class>" << endl;
}

/************************************************************
 *                      CompileClassVarDec()
 *  Compiles a static declaration or a field declaration
 *************************************************************/
void Parser::CompileClassVarDec() {
    // start with the classVarDec header
    fileOut << "<classVarDec>" << endl;
    fileOut << "<keyword>" << jackT.keyWord() << "</keyword>" << endl;
    jackT.advance();
    if(jackT.tokenType() == KEYWORD) {
        fileOut << "<keyword" << jackT.keyWord() << "</keyword>" << endl;
        jackT.advance();
    }
    else {
        fileOut << "<identifier>" << jackT.identifier() << "</identifier>" << endl;
        jackT.advance();
    }
    while(jackT.symbol() != ';') {
        fileOut << "<symbol>"<< jackT.symbol() << "</symbol>" << endl;
        fileOut << "<identifier>" << jackT.identifier() << "</identifier>" << endl;
        jackT.advance();
    }
    
    fileOut << "<symbol> ; </symbol>" << endl;
    fileOut << "</classVarDec" << endl;
}

/************************************************************
 *                      CompileSubroutine()
 *  Compiles a complete method, function, or constructor
 *************************************************************/
void Parser::CompileSubroutine() {
    fileOut << "<subroutineDec>" << endl;
    fileOut << "<keyword>" << jackT.keyWord() << "</keyword>" << endl;
    jackT.advance();
    if(jackT.tokenType() == KEYWORD) {
        fileOut << "<keyword>" << jackT.keyWord() << "</keyword>" << endl;
        jackT.advance();
    }
    else if(jackT.tokenType() == IDENTIFIER) {
        fileOut << "<identifier>" << jackT.identifier() << "</identifier>" << endl;
        jackT.advance();
    }
    else {
        fileOut << "<identifier> " << jackT.identifier() << " </identifier>" << endl;
        if(jackT.tokenType() == TNONE) {
            jackT.advance();
        }
        else if(jackT.symbol() == '(') {
            fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
            jackT.advance();
            CompileParameterList();
        }
        if(jackT.symbol() == ')') {
            fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
            jackT.advance();
        }
        if(jackT.symbol() == '{') {
            fileOut << "<subroutineBody>" << endl;
            fileOut << "<symbol>" << "{" << "</symbol>" << endl;
            if(jackT.tokenType() == TNONE) {
                    jackT.advance();
                }
            else if(jackT.keyWord() == LET || jackT.keyWord() == IF || jackT.keyWord() == WHILE || jackT.keyWord() == DO || jackT.keyWord() == RETURN) {
                    CompileStatements();
                }
                else if(jackT.symbol() == '}') {
                    fileOut << "<symbol> } </symbol>" << endl;
                }
                else {
                    CompileVarDec();
                }
            fileOut << "</subroutineBody>" << endl;
        }
    }
    fileOut << "</subroutineDec>" << endl;
}

/************************************************************
 *                      CompileParameterList()
 *  Compiles (possibly empty) parameter list,
 *  not inlcluding the enclosing "()"
 *************************************************************/
void Parser::CompileParameterList() {
    fileOut << "<parameterList>" << endl;
    while(jackT.symbol() != ')'){
        if(jackT.tokenType() == KEYWORD) {
            fileOut << "<keyword>" << jackT.keyWord() << "</keyword>" << endl;
            jackT.advance();
        }
        else if(jackT.tokenType() == IDENTIFIER) {
            fileOut << "<identifier>" << jackT.identifier() << "</identifier" << endl;
        }
        else if(jackT.tokenType() == SYMBOL) {
            fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
        }
        else {
            jackT.advance();
        }
    }
    fileOut << "</parameterList>" << endl;
}

/************************************************************
 *                      CompileVarDec()
 *  Compiles a var declaration
 *************************************************************/
void Parser::CompileVarDec() {
    fileOut << "<classVarDec>" << endl;
    fileOut << "<keyword>" << jackT.keyWord() << "</keyword>" << endl;
    jackT.advance();

    while(jackT.symbol() != ';'){
        if(jackT.tokenType() == KEYWORD) {
            fileOut << "<keyword>" << jackT.keyWord() << "</keyword>" << endl;
            jackT.advance();
        }
        else if(jackT.tokenType() == IDENTIFIER) {
            fileOut << "<identifier>" << jackT.identifier() << "</identifier" << endl;
        }
        else if(jackT.tokenType() == SYMBOL) {
            fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
        }
        else {
            jackT.advance();
        }
    }
    if(jackT.symbol() == ';'){
        fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
        jackT.advance();
    }
    fileOut << "</classVarDec>" << endl;
}

/************************************************************
 *                      CompileStatements()
 *  Compiles sequence of statements, not including
 *  the enclosing "{}"
 *************************************************************/
void Parser::CompileStatements() {
    fileOut << "<statements>" << endl;
    while(true) {
        if(jackT.keyWord() == LET)
            CompileLet();
        else if(jackT.keyWord() == IF)
            CompileIf();
        else if(jackT.keyWord() == WHILE)
            CompileWhile();
        else if(jackT.keyWord() == DO)
            CompileDo();
        else if(jackT.keyWord() == RETURN)
            CompileReturn();
        else
            break;
    }
    fileOut << "</statements>" << endl;
}

/************************************************************
 *                      CompileDo()
 *  Compiles a do statement
 *************************************************************/
void Parser::CompileDo() {
    fileOut << "<doStatement>" << endl;
    fileOut << "<keyword> do </keyword>" << endl;
    jackT.advance();
    fileOut << "<identifier>" << jackT.identifier() << "</identifier>" << endl;
    if(jackT.symbol() == '(') {
        fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
        if(jackT.symbol() == ')') {
            fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
            jackT.advance();
        }
        else {
            jackT.advance();
            CompileExpressionList();
        }
    }
    else if(jackT.symbol() == '.') {
        fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
        jackT.advance();
        fileOut << "<identifier>" << jackT.identifier() << "</identifier>" << endl;
        if(jackT.symbol() == ')') {
            fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
            jackT.advance();
        }
        else {
            jackT.advance();
            CompileExpressionList();
        }
    }
    fileOut << "<symbol> ; </symbol>" << endl;
    jackT.advance();
    fileOut << "</doStatement>" << endl;
}

/************************************************************
 *                      CompileLet()
 *  Compiles a let statement
 *************************************************************/
void Parser::CompileLet() {
    fileOut << "<letStatement>" << endl;
    fileOut << "<keyword> let </keyword>" << endl;
    jackT.advance();
    fileOut << "<identifier>" << jackT.identifier() << "</identifier>" << endl;
    if(jackT.symbol() == '[') {
        fileOut << "<symbol> [ </symbol>" << endl;
        jackT.advance();
        CompileExpression();
        if(jackT.symbol() == ']') {
            fileOut << "<symbol> ] </symbol>" << endl;
            jackT.advance();
        }
    }
    else {
        fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
        jackT.advance();
        CompileExpression();
    }
    if(jackT.symbol() == ';')
        fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
    jackT.advance();
    fileOut << "</letStatement>" << endl;
}

/************************************************************
 *                      CompileWhile()
 *  Compiles a while statement
 *************************************************************/
void Parser::CompileWhile() {
    fileOut << "<whileStatement>" << endl;
    fileOut << "<keyword> while </keyword>" << endl;
    jackT.advance();
    if(jackT.symbol() == '('){
        fileOut << "<symbol> ( </symbol>" << endl;
        jackT.advance();
    }
    else {
        jackT.advance();
    }
    CompileExpression();
    fileOut << "<symbol> ) </symbol>" << endl;
    
    if(jackT.symbol() == '{') {
        fileOut << "<symbol> { </symbol>" << endl;
        jackT.advance();
    }
    else {
        jackT.advance();
    }
    CompileStatements();
    fileOut << "<symbol> } </symbol>" << endl;
    jackT.advance();
    fileOut << "</whileStatement>" << endl;

}

/************************************************************
 *                      CompileReturn()
 *  Compiles a return statement
 *************************************************************/
void Parser::CompileReturn() {
    fileOut << "<returnStatement>" << endl;
    fileOut << "<keyword> return </keyword>" << endl;
    jackT.advance();
    if(jackT.keyWord() == RETURN) {
        jackT.advance();
        CompileExpression();
        jackT.advance();
    }
    else {
        fileOut << "<symbol> ; </symbol>" << endl;
        jackT.advance();
    }
    fileOut << "</returnStatement>" << endl;
}

/************************************************************
 *                      CompileIf()
 *  Compiles an if statement-could have trailing else
 *************************************************************/
void Parser::CompileIf() {
    fileOut << "<ifStatement>" << endl;
    fileOut << "<keyword> if </keyword>" << endl;
    jackT.advance();
    fileOut << "<symbol> ( </symbol>" << endl;
    jackT.advance();
    CompileExpression();
    fileOut << "<symbol> ) </symbol>" << endl;
    jackT.advance();
    fileOut << "<symbol> { </symbol>" << endl;
    jackT.advance();
    CompileStatements();
    fileOut << "<symbol> } </symbol>" << endl;
    jackT.advance();
    
    if(jackT.keyWord() == ELSE){
        fileOut << "<keyword> else </keyword>" << endl;
        jackT.advance();
        fileOut << "<symbol> { </symbol>" << endl;
        jackT.advance();
        CompileStatements();
        fileOut << "<symbol> } </symbol>" << endl;
        jackT.advance();
    }
    
    fileOut << "</ifStatement>" << endl;
}

/************************************************************
 *                      CompileExpression()
 *  Compiles an expression
 *************************************************************/
void Parser::CompileExpression() {
    fileOut << "<expression>" << endl;
    CompileTerm();
    while(jackT.symbol() == '+' || jackT.symbol() == '-' || jackT.symbol() == '|'
          || jackT.symbol() == '&' || jackT.symbol() == '<' || jackT.symbol() == '>'
          || jackT.symbol() == '='){
        fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
        CompileTerm();
        jackT.advance();
    }
    fileOut << "</expression>" << endl;
}

/************************************************************
 *                      CompileTerm()
 *  Compiles a term. If token is an identifier, must distinguish
 *  between variable, array, and subroutine call.
 *************************************************************/
void Parser::CompileTerm() {
    fileOut << "<term>" << endl;
    if(jackT.tokenType() == IDENTIFIER) {
        fileOut << "<identifier>" << jackT.identifier() << "</identifier>" << endl;
        jackT.advance();
        if(jackT.symbol() == '(') {
            fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
            jackT.advance();
            CompileExpressionList();
            if(jackT.symbol() == ')'){
                fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
                jackT.advance();
            }
        }
        else if(jackT.symbol() == '.') {
            fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
            jackT.advance();
            fileOut << "<identifier>" << jackT.identifier() << "</identifier>" << endl;
            CompileExpressionList();
        }
        else if(jackT.symbol() == '[') {
            fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
            jackT.advance();
            CompileExpression();
            if(jackT.symbol() == ']'){
                fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
                jackT.advance();
            }
        }
        else{
            jackT.advance();
        }
    }
    else if(jackT.tokenType() == INT_CONST) {
        fileOut << "<integerConstant>" << jackT.intVal() << "</integerConstant>" << endl;
    }
    else if(jackT.tokenType() == STRING_CONST) {
        fileOut << "<stringConstant>" << jackT.stringVal() << "</stringConstant>" << endl;
    }
    else if(jackT.tokenType() == KEYWORD) {
        fileOut << "<keyword>" << jackT.keyWord() << "</keyword>" << endl;
    }
    else if(jackT.tokenType() == SYMBOL) {
        if(jackT.symbol() == '('){
            fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
            jackT.advance();
            CompileExpression();
            fileOut << "<symbol> ) </symbol>" << endl;
        }
        else{
            fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
            jackT.advance();
            CompileTerm();
        }
    }
    else{
        jackT.advance();
    }
    fileOut << "</term>" << endl;
}

/************************************************************
 *                      CompileExpressionList()
 *  Compiles (possibly empty) comma separated list of
 *  expressions
 *************************************************************/
void Parser::CompileExpressionList() {
    fileOut << "<expressionList>" << endl;
    if(jackT.symbol() != ')') {
        CompileExpression();
        jackT.advance();
        while(jackT.symbol() == ',') {
            fileOut << "<symbol>" << jackT.symbol() << "</symbol>" << endl;
            CompileExpression();
        }
    }
    jackT.advance();
    fileOut << "</expressionList>" << endl;
}
