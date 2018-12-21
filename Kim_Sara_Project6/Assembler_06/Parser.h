// Parser.h
#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

class Parser {
public:
	// Constructor that opens input file
    Parser(const string& fileName);
	// Deconstructor that closes input file
    ~Parser();
    // Close the file to clear and eof flags
    void closeFile(const string& fileName);
	// Boolean to check if there are more commands
	bool hasMoreCommands();
	// Reads next command from input to make current.
	// Only called when hasMoreCommands is true
	void advance();
	// Returns type of the current command
	char commandType();

	// Returns string of current command
	// Only called when commandType() is A_COMMAND or L_COMMAND
	string symbol(char commandT);
	// Returns dest mnemonic
	// Only called when commandType() is C_COMMAND
	string dest();
	// Returns comp mnemonic
	// Only called when commandType() is C_COMMAND
	string comp();
	// Returns jump mnemonic
	// Only called when commandType() is C_COMMAND
	string jump();
};
