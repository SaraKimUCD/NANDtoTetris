// Parser.cpp

#include "Parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

ifstream fileIn;
string command;

Parser::Parser(const string& fileName){
    //cout << "Inside parser" << endl;
    fileIn.open(fileName);
}

Parser::~Parser(){
    fileIn.close();
}

void Parser::closeFile(const string& fileName) {
    fileIn.close();
}

// returns true if file has more commands
bool Parser::hasMoreCommands() {
    
	return !fileIn.eof();
}

void Parser::advance() {
    string line;
    bool isCommand = false;
    unsigned long position;
    
    // While the line is not a command...
    while(!isCommand){
        // Get next line from file while discarding whitespace
        getline(fileIn >> ws, line);
        // erase from the line any whitespace
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        // Now need to remove any comments from the file line
        // Look for the position "//" and erase from line if found
        position = line.find("//");
        if(position != string::npos){
            line.erase(position, line.length()-position);
        }
        
        // After finding all whitespace and comments and is not empty,
        // remaining strings in line is the command
        isCommand = !line.empty();
    }
    command = line;
}

// Check what the command type is
char Parser::commandType() {
    // if the command starts with @, it is an A_COMMAND
    if (command.front() == '@')
        return 'A';
    // if the command starts with a opening parenthesis '(', it is a L_COMMAND
    else if (command.front() == '(')
        return 'L';
    // if the command starts with anything else it is a C_COMMAND
    else
        return 'C';
}

string Parser::symbol(char commandT) {
    // When it is A_COMMAND, get all symbol/decimal after the @
    // A_COMMAND for @xxx where xxx=symbol or decimal
    if (commandT == 'A') {
        size_t position = command.find("@");
        string tempString = command.substr(position+1);
        return tempString;
    }
    
    // When it is a L_COMMAND, get all symbols/decimal between the parentheses
    // L_COMMAND for (xxx) where xxx=symbol
    else {
        size_t openParen = command.find('(');
        size_t closeParen = command.find(')');
        string tempString1 = command.substr(openParen+1, closeParen-openParen-1);
        return tempString1;
    }
}

// *********************************************************************
// All functions within block is for when it is a C_COMMAND

string Parser::dest() {
    // Only need to parse the dest mnemonic so find up to the '='
    // C_COMMAND for dest=comp; jump
    size_t findEqual = command.find('=');
    if(findEqual != string::npos) {
        string destString = command.substr(0, findEqual);
        return destString;
    }
    return "";
}

string Parser::comp() {
    // Only need to parse the comp mnemonic so find from the '='
    // up until the ';'
    // C_COMMAND for dest=comp; jump
    size_t findEq = command.find('=');
    size_t findSemi = command.find(';');
    
    // dest=comp
    if(findSemi == string::npos) {
        string compNoJmp = command.substr(findEq+1);
        return compNoJmp;
    }
    // comp; jump
    else if(findEq == string::npos) {
        string compNoDest = command.substr(0, findSemi);
        return compNoDest;
    }
    // dest=comp; jump
    else {
        string compTemp = command.substr(findEq+1, findSemi);
        return compTemp;
    }
}

string Parser::jump() {
    // dest=comp; jump
    // Find everything after the semicolon to return only the jump
    size_t findSemic = command.find(';');
    
    if(findSemic != string::npos) {
        //, commandLength-findSemic-1
        string jumpCommand = command.substr(findSemic+1);
        return jumpCommand;
    }
    return "";
}
// *********************************************************************
