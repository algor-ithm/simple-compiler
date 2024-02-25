#include "TokenFSA.h"
#include "Lexer.h"
#include "FileHandler.h"
#include <iostream>

using namespace std;

// read file function

// add args to pass program to compiler and output file names?
int main(int argc, char* argv[]) {
    string code;
    vector<Token> tokenList;
    TokenFSA fsa;
    Lexer lexer(fsa);
    FileHandler fHandler;

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
    lexer.setInput(code);
    //Tokenize the program and retrieve token list 
    lexer.tokenize();
    tokenList = lexer.getTokens();
    // Write token list to a file
    fHandler.writeTokenList(tokenList);


    // add more to do symbol table, parse etc.
    return 0;
}