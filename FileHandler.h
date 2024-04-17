#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Tokenizer.h"
#include "SymbolTableBuilder.h"
#include "Parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std; 

class FileHandler
{
public:
    string readProgram(const string &filePath) const;
    void writeTokenList(const Token* tokens, int tokenCount);
    void writeSymbolTable(const Symbol* symbolList, int symbolCount);
    void writeQuads(const Quad* quadList, int quadCount);
    void writeAsmFile(const string& assemblyCode, const string& filename);
};

#endif