#include "TokenFSA.h"
#include "Lexer.h"
#include "FileHandler.h"
#include <iostream>

using namespace std;

// read file function

// add args to pass program to compiler and output file names?
int main(int argc, char* argv[]) {
    // check that a program file was a command line arguement
    if (argc < 2) {
        cerr << "File path required. \n" << "Usage: " << argv[0] << " <filepath>" << endl;
        return 1;
    }
    // Get file path
    string pgmFile = argv[1];
    string code;

    TokenFSA fsa;
    Lexer lexer(fsa);
    FileHandler fHandler;

    // read the program file 
    code = fHandler.readProgram(pgmFile);

    // Set the program as input for the lexer
    lexer.setInput(code);
 


    // tokenize it

    // retrieve tokens and add to token list

    // add more to do symbol table, parse etc.
    return 0;
}