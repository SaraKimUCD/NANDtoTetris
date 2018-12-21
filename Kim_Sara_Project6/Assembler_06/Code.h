// Code.h
#include <iostream>
#include <map>

using namespace std;

class Code {
private:
    // destMap: Binary code of the dest mnemonics
    map<string, string> destMap;
    // compMap: Binary code of the comp mnemonics
    map<string, string> compMap;
    // jumpMap: Binary code of the jump mnemonics
    map<string, string> jumpMap;
    
public:
    // constructor that fills the destMap, compMap, jumpMap
    Code(){
         // destMap
        destMap[""] = "000";
        destMap["M"] = "001";
        destMap["D"] = "010";
        destMap["MD"] = "011";
        destMap["DM"] = "011";
        destMap["A"] = "100";
        destMap["AM"] = "101";
        destMap["MA"] = "101";
        destMap["AD"] = "110";
        destMap["DA"] = "110";
        destMap["AMD"] = "111";
        destMap["ADM"] = "111";
        destMap["DAM"] = "111";
        destMap["DMA"] = "111";
        destMap["MAD"] = "111";
        destMap["MDA"] = "111";
    
        // compMap
        // when a = 0
        compMap["0"] = "0101010";
        compMap["1"] = "0111111";
        compMap["-1"] = "0111010";
        compMap["D"] = "0001100";
        compMap["A"] = "0110000";
        compMap["!D"] = "0001101";
        compMap["!A"] = "0110001";
        compMap["-D"] = "0001111";
        compMap["-A"] = "0110011";
        compMap["D+1"] = "0011111";
        compMap["A+1"] = "0110111";
        compMap["D-1"] = "0001110";
        compMap["A-1"] = "0110010";
        compMap["D+A"] = "0000010";
        compMap["D-A"] = "0010011";
        compMap["A-D"] = "0000111";
        compMap["D&A"] = "0000000";
        compMap["D|A"] = "0010101";
        // when a = 1
        compMap["M"] = "1110000";
        compMap["!M"] = "1110001";
        compMap["-M"] = "1110011";
        compMap["M+1"] = "1110111";
        compMap["M-1"] = "1110010";
        compMap["D+M"] = "1000010";
        compMap["D-M"] = "1010011";
        compMap["M-D"] = "1000111";
        compMap["D&M"] = "1000000";
        compMap["D|M"] = "1010101";
        
        //jumpMap
        jumpMap[""] = "000";
        jumpMap["JGT"] = "001";
        jumpMap["JEQ"] = "010";
        jumpMap["JGE"] = "011";
        jumpMap["JLT"] = "100";
        jumpMap["JNE"] = "101";
        jumpMap["JLE"] = "110";
        jumpMap["JMP"] = "111";
    }
    // deconstructor that clears all maps/tables
    ~Code() {
        destMap.clear();
        compMap.clear();
        jumpMap.clear();
    }
    
	// Returns binary code of the dest
	string destCode(string mnemonic);
	// Returns the binary code of the comp
	string compCode(string mnemonic);
	// Returns the binary code of the jump
	string jumpCode(string mnemonic);

};
