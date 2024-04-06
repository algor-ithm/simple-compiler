#include "Tokenizer.h"
#include "FileHandler.h"
#include "SymbolTableBuilder.h"
#include "Parser.h"
#include <iostream>

using namespace std;

// add args to pass program to compiler and output file names?
int main(int argc, char* argv[]) {
    string code;
    //const SymbolTableEntry symbolTable
    //vector<SymbolTableEntry> symbolTable;
    FileHandler fHandler;
    Tokenizer tokenizer;
    SymbolTableBuilder stBuilder;
    Parser parser;

    // check that a program file was a command line arguement
    if (argc < 2) {
        cerr << "File path required. \n" << "Usage: " << argv[0] << " <filepath>" << endl;
        return 1;
    }
    // Get file path
    string pgmFile = argv[1];
    try {
        code = fHandler.readProgram(pgmFile);
    } catch (const std::exception& e) {
        cerr << "Error reading file: " << e.what() << endl;
        return 1;
    }
    // Set the program as input for the lexer
    //cout << code << endl;
    tokenizer.setInput(code);
    //Tokenize the program and retrieve token list 
    tokenizer.tokenize();
    // Write token list to a file
    const Token* tokenList = tokenizer.getTokens();
    int tokenCount = tokenizer.getTokenCount();
    fHandler.writeTokenList(tokenList, tokenCount);
    // Build the symbol talbe
    stBuilder.buildSymbolTable(tokenList, tokenCount);
    // Write symbol table to a file
    const SymbolTableEntry* symbolTable = stBuilder.getSymbolTable();
    int symbolCount = stBuilder.getSymbolCount();
    fHandler.writeSymbolTable(symbolTable, symbolCount);
    parser.parse(tokenList, tokenCount);
    const Quad* quadList = parser.getQuads();
    int quadCount = parser.getQuadCount();
    fHandler.writeQuads(quadList, quadCount);
    // add more to do: code generation, etc.
    
    return 0;
}