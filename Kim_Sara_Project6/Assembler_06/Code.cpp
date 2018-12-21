// Code.cpp
#include "Code.h"
#include <iostream>

using namespace std;
// iterator to go through and find mnemonic in each map
map<string, string>::iterator itCode;

string Code::destCode(string mnemonic) {
    itCode = destMap.find(mnemonic);
    if (itCode != destMap.end()) {
        return destMap[mnemonic];
    }
    else {
        return "";
    }
}

string Code::compCode(string mnemonic) {
    itCode = compMap.find(mnemonic);
    if (itCode != compMap.end()) {
        return compMap[mnemonic];
    }
    else {
        return "";
    }
}

string Code::jumpCode(string mnemonic) {
    itCode = jumpMap.find(mnemonic);
    if (itCode != jumpMap.end()) {
        return jumpMap[mnemonic];
    }
    else {
        return "";
    }
}
