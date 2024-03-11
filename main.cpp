#include "Tokenizer.h"
#include "FileHandler.h"
#include "SymbolTableBuilder.h"
#include <iostream>

using namespace std;

// add args to pass program to compiler and output file names?
int main(int argc, char* argv[]) {
    string code;
    vector<Token> tokenList;
    vector<SymbolTableEntry> symbolTable;
    FileHandler fHandler;
    Tokenizer tokenizer;
    SymbolTableBuilder stBuilder;

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
    tokenList = tokenizer.getTokens();
    fHandler.writeTokenList(tokenList);
    // Build the symbol talbe
    stBuilder.buildSymbolTable(tokenList);
    // Write symbol table to a file
    symbolTable = stBuilder.getSymbolTable();
    fHandler.writeSymbolTable(symbolTable);
    // add more to do: syntax, semantics, etc.
    return 0;
}