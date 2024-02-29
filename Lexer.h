#ifndef LEXER_H
#define LEXER_H

#include "enumDefinitions.h"
#include "TokenFSA.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// Define the token Struct
struct Token {
    string lexeme;
    string type;

    // Token constructor
    Token(const string& lexeme, const string& type);
};

class Lexer
{
private:
    // variables
    TokenFSA fsa;
    string input;
    size_t position = 0;
    vector<Token> tokens;
    // functions
    InputType charToInputType(char ch);
    void addTokens(const string& lexeme, const string& type);
    string mapStateToTokenType(TokenState state, const string& lexeme) const;

public:
    explicit Lexer(const TokenFSA& fsa);
    void setInput(const string& newInput);
    void tokenize();
    const vector<Token>& getTokens() const;
};

#endif