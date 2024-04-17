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
    int dataSize = 0;
    Symbol bssSymbols[MAX_SYMBOLS];
    int bssSize = 0;
    Quad optimizedQuads[MAX_QUADS];
    int optimizedCount = 0; 
    void optimizeQuads();
    void processSymbolTable();
    void processQuads();
    void genLinuxDefs();
    void genDataSection();
    void genBssSection();
    void genTextSection();
    void genPrintString();
    void genGetInterger();
    void genConvertIntToString();
 
public:
    CodeGenerator(const Quad* quadList, int quadSize, const Symbol* symbolTable, int symbolSize); 
    void generateAssembly();
    string getAssemblyCode();
    string getFileName();
};

#endif