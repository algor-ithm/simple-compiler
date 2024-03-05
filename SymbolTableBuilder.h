#ifndef SYMBOLTABLEBUILDER_H
#define SYMBOLTABLEBUILDER_H

#include "enumDefinitions.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct SymbolTableEntry {
    string token;
    string type;
    string value;
    size_t address;
    string segment;

    SymbolTableEntry(const string& t, const string& tt, const string& val, size_t addr, const string& seg)
        : token(t), type(tt), value(val), address(addr), segment(seg) {}
};

class SymbolTableBuilder
{

private:
    int symbolStateTable[SS_COUNT][TT_COUNT] = {};
    void configSymbolTableFSA();
    SymbolState getNextSymbolState(SymbolState currState, TokenType token);

public:
    SymbolTableBuilder();



};

#endif