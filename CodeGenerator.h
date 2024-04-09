#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "Parser.h"
#include "SymbolTableBuilder.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;

class CodeGenerator {
private:
    const Quad* quads;
    const Symbol* symbols;
    int qSize, sSize;
    stringstream asmCode;
    string programName;
    Symbol dataSymbols[MAX_SYMBOLS];
    Symbol bssSymbols[MAX_SYMBOLS];
    int dataSize = 0;
    int bssSize = 0;
    void processSymbolTable();
    void processQuads();
    void genLinuxDefs();
    void genDataSection();
    void genBssSection();
    void genTextSection();
    void genPrintString();
    void genGetInterger();
    void genConvertIntToString();
    void writeAsmFile();
  
public:
    CodeGenerator(const Quad* quadList, int quadSize, const Symbol* symbolTable, int symbolSize); 
    void generateAssembly();
};

#endif