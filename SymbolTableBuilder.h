#ifndef SYMBOLTABLEBUILDER_H
#define SYMBOLTABLEBUILDER_H

#include "enumDefinitions.h"
#include "Tokenizer.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct SymbolTableEntry {
    string token;
    string type;
    string value;
    string address;
    string segment;

    SymbolTableEntry(const string& t, const string& tt, const string& val, const string& addr, const string& seg)
        : token(t), type(tt), value(val), address(addr), segment(seg) {}
};

class SymbolTableBuilder
{

private:
    int symbolStateTable[SS_COUNT][TT_COUNT] = {};
    vector<SymbolTableEntry> symbolList;
    void configSymbolTableFSA();
    SymbolState getNextSymbolState(SymbolState currState, TokenType token);
    TokenType mapStringTypeToTokenType(const string& tokenType);
    void addToSymbolTable(const string& token, const string& type, const string& value, int addr, const string& segment);

public:
    SymbolTableBuilder();
    void buildSymbolTable(const vector<Token>& tokens);
    vector<SymbolTableEntry> getSymbolTable();



};

#endif