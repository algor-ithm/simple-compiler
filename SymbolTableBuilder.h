#ifndef SYMBOLTABLEBUILDER_H
#define SYMBOLTABLEBUILDER_H

#include "enumDefinitions.h"
#include "Tokenizer.h"
#include <iostream>
#include <string>

using namespace std;

const int MAX_SYMBOLS = 500;
struct SymbolTableEntry {
    string token;
    string type;
    string value;
    string address;
    string segment;

    SymbolTableEntry() : token(""), type(""), value(""), address(""), segment("") {}

    SymbolTableEntry(const string& t, const string& tt, const string& val, const string& addr, const string& seg)
        : token(t), type(tt), value(val), address(addr), segment(seg) {}
};

class SymbolTableBuilder {
private:
    // Use -1 to denote invalid state transitions (error handling later?)
    const int INVALID_STATE = -1;
    int symbolStateTable[SS_COUNT][TT_COUNT];
    SymbolTableEntry symbolList[MAX_SYMBOLS];
    int symbolCount = 0;
    void configSymbolTableFSA();
    SymbolState getNextSymbolState(SymbolState currState, TokenType token);
    TokenType mapStringTypeToTokenType(const string& tokenType);
    void addToSymbolTable(const string& token, const string& type, const string& value, int addr, const string& segment);

public:
    SymbolTableBuilder();
    void buildSymbolTable(const Token* tokens, int tokenCount);
    const SymbolTableEntry* getSymbolTable() const;
    int getSymbolCount() const;
};

#endif