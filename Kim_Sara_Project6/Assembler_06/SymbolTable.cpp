// SymbolTable.cpp
#include "SymbolTable.h"

using namespace std;
// iterator to go through and find symbol in symbol table
map<string, int>::iterator itSym;

void SymbolTable::addEntry(string symbol, int address) {
    symbolTable[symbol] = address;
}

bool SymbolTable::contains(string symbol) {
    itSym = symbolTable.find(symbol);
    return (itSym != symbolTable.end());
}

int SymbolTable::GetAddress(string symbol) {
    return (symbolTable[symbol]);
}
