#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Tokenizer.h"
#include "SymbolTableBuilder.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>

using namespace std; 

class FileHandler
{
private:
    string filePath;

public:
    string readProgram(const string &filePath) const;
    // write token list to file
    void writeTokenList(const vector<Token>& tokens);
    // write symbol table file
    void writeSymbolTable(const vector <SymbolTableEntry>& symbolList);
};

#endif