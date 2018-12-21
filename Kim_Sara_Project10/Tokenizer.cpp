//  Tokenizer.cpp
//  CSCI 2940 - nand2tetris Project 10
//  Sara Kim

//  Jack Tokenizer: removes all comments/white space from input stream
//  and breaks it into Jack language tokens

#include "Tokenizer.h"


using namespace std;

/************************************************************
 *                   Tokenizer(string filename)
 * Opens input file to tokenize
 *************************************************************/
Tokenizer::Tokenizer(string filename) {
    saveFile = filename;
    
}

/************************************************************
 *                   ~Tokenizer()
 * Close all files
 *************************************************************/
Tokenizer::~Tokenizer() {
    fileIn.close();
}

void Tokenizer::setFilename(string filename) {
    fileIn.open(filename);
}

/************************************************************
 *                      hasMoreTokens()
 * Checks if input has more tokens
 *************************************************************/
bool Tokenizer::hasMoreTokens() {
    return !fileIn.eof();
}

/************************************************************
 *                      advance()
 *  Gets next token from input and makes it current token.
 *  Only called if hasMoreTokens is true.
 *************************************************************/
void Tokenizer::advance() {
    if(hasMoreTokens()) {
        getline(fileIn >> ws, current);
        // Erase any comments from the file line by finding "//", "/*" or "/**"
        // after erasing, current will hold token string
        if(current.find("//") != string::npos){
         current.erase(current.find("//"));
            //cout << current << endl;
         }
         else if(current.find("/*") != string::npos) {
         current.erase(current.find("/*"));
             //cout << current << endl;
         }
         else if(current.find("/**") != string::npos) {
         current.erase(current.find("/**"));
             //cout << current << endl;
         }
    }
    //cout << current << endl;
}

/************************************************************
 bool checkInt()
 * Check if token is an integer for the integer Constant
 *************************************************************/
bool Tokenizer::checkInt(string check) {
    if(check.empty() || check != "0" || check != "1" || check != "2"
       || check != "3" || check != "4" || check != "5" || check != "6"
       || check != "7" || check != "8" || check != "9") {
        return false;
    }
    bool range = false;
    int integer = stoi(check);
    if (integer >= 0 && integer <=32767) {range = true;}
    return range;
}

/************************************************************
 *                      tokenType()
 * Returns the type of the current token
 *  KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST
 * Reference Lexical elements from book, pg. 208
 *************************************************************/
token Tokenizer::tokenType() {
    string oneLetter = current.substr(0, 1);
    string twoLetters = current.substr(0, 2);
    string threeLetters = current.substr(0, 3);
    string fourLetters = current.substr(0, 4);
    string fiveLetters = current.substr(0, 5);
    string sixLetters = current.substr(0, 6);
    string sevenLetters = current.substr(0, 7);
    string eightLetters = current.substr(0 ,10);
    string elevenLetters = current.substr(0, 11);
    
    if(fiveLetters == "class" || elevenLetters == "constructor" || eightLetters == "function"
       || sixLetters == "method" || fiveLetters == "field" || sixLetters == "static"
       || threeLetters == "var" || threeLetters == "int" || fourLetters == "char"
       || sevenLetters == "boolean" || fourLetters == "void" || fourLetters == "true"
       || fiveLetters == "false" || fourLetters == "null" || fourLetters == "this"
       || threeLetters == "let" || twoLetters == "do" || twoLetters == "if"
       || fourLetters == "else" || fiveLetters == "while" || sixLetters == "return") {
        return KEYWORD;
    }
    else if(oneLetter == "{" || oneLetter == "}" || oneLetter == "(" || oneLetter == ")"
            || oneLetter == "[" || oneLetter == "]" || oneLetter == "." || oneLetter == ","
            || oneLetter == ";" || oneLetter == "+" || oneLetter == "-" || oneLetter == "*"
            || oneLetter == "/" || oneLetter == "&" || oneLetter == "|" || oneLetter == "<"
            || oneLetter == ">" || oneLetter == "=" || oneLetter == "~") {
        return SYMBOL;
    }
    // integerConstant: decimal number in the range 0-32767
    else if(checkInt(oneLetter)) {
        return INT_CONST;
    }
    // stringConstant: sequence of characters not inluding double quote or newline
    else if(oneLetter[0] == '"') {
        return STRING_CONST;
    }
    // identifier: sequence not starting with integer
    else if(!checkInt(oneLetter)){
        return IDENTIFIER;
    }
    return TNONE;
}

/************************************************************
 *                      keyWord()
 *  Returns the keyword of the current token.
 *  Only called when tokenType is KEYWORD
 *  CLASS, METHOD, FUNCTION, CONSTRUCTOR, INT, BOOLEAN,
 *  CHAR, VOID, VAR, STATIC, FIELD, LET, DO, IF, ELSE, WHILE,
 *  RETURN, KTRUE, KFALSE, KNULL, KTHIS
 *************************************************************/
key Tokenizer::keyWord() {
    string twoLetters = current.substr(0, 2);
    string threeLetters = current.substr(0, 3);
    string fourLetters = current.substr(0, 4);
    string fiveLetters = current.substr(0, 5);
    string sixLetters = current.substr(0, 6);
    string sevenLetters = current.substr(0, 7);
    string eightLetters = current.substr(0, 8);
    string elevenLetters = current.substr(0, 11);
    
    if(fiveLetters == "class") {return CLASS;}
    else if(sixLetters == "method") {return METHOD;}
    else if(eightLetters == "function") {return FUNCTION;}
    else if(elevenLetters == "constructor") {return CONSTRUCTOR;}
    else if(threeLetters == "int") {return INT;}
    else if(sevenLetters == "boolean") {return BOOLEAN;}
    else if(fourLetters == "char") {return CHAR;}
    else if(fourLetters == "void") {return VOID;}
    else if(threeLetters == "var") {return VAR;}
    else if(sixLetters == "static") {return STATIC;}
    else if(fiveLetters == "field") {return FIELD;}
    else if(threeLetters == "let") {return LET;}
    else if(twoLetters == "do") {return DO;}
    else if(twoLetters == "if") {return IF;}
    else if(fourLetters == "else") {return ELSE;}
    else if(fiveLetters == "while") {return WHILE;}
    else if(sixLetters == "return") {return RETURN;}
    else if(fourLetters == "true") {return KTRUE;}
    else if(fiveLetters == "false") {return KFALSE;}
    else if(fourLetters == "null") {return KNULL;}
    else if(fourLetters == "this") {return KTHIS;}
    return KNONE;
}

/************************************************************
 *                      symbol()
 *  Returns charcter of the current token.
 *  Only called when tokenType is SYMBOL
 *************************************************************/
char Tokenizer::symbol() {
    assert(tokenType() == SYMBOL);
    return current[0];
}

/************************************************************
 *                      identifier()
 *  Returns identifier of the current token.
 *  Only called when tokenType is IDENTIFIER
 *************************************************************/
string Tokenizer::identifier() {
    if (tokenType() == IDENTIFIER)
        return current;
    return "";
}

/************************************************************
 *                      intVal()
 *  Returns integer value of the current token.
 *  Only called when tokenType is INT_CONST
 *************************************************************/
int Tokenizer::intVal() {
    assert(tokenType() == INT_CONST);
    return stoi(current);
}

/************************************************************
 *                      stringVal()
 *  Returns string value of the current token.
 *  Only called when tokenType is STRING_CONST
 *************************************************************/
string Tokenizer::stringVal() {
    assert(tokenType() == STRING_CONST);
    return current;
}

