#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Lexer.h"
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
    // read token list file
    void readTokenList();
    // write symbol table file
    void writeSymbolTable();
};

#endif