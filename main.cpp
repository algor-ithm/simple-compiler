#include "Tokenizer.h"
#include "FileHandler.h"
#include <iostream>

using namespace std;

// read file function

// add args to pass program to compiler and output file names?
int main(int argc, char* argv[]) {
    string code;
    vector<Token> tokenList;
    FileHandler fHandler;
    Tokenizer tokenizer;

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
    tokenList = tokenizer.getTokens();
    // Write token list to a file
    fHandler.writeTokenList(tokenList);


    // add more to do symbol table, parse etc.
    return 0;
}