#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "enumDefinitions.h"
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

// Define the token Struct
const int MAX_TOKENS = 1000;
struct Token {
    string lexeme;
    string type;

    // Default constructor
    Token() : lexeme(""), type("") {}

    // Token constructor
    Token(const string& lex, const string& lexType) 
        : lexeme(lex), type(lexType) {}
};

class Tokenizer {
private:
    int tokenStateTable[S_COUNT][I_COUNT] = {};
    Token tokens[MAX_TOKENS];
    int tokenCount = 0;
    //vector<Token> tokens;
    string input;
    size_t position = 0;
    void configJava0FSA();
    InputType charToInputType(char ch);
    void addTokens(const string& lexeme, const string& type);
    string mapStateToTokenType(TokenState state, const string& lexeme) const;
    TokenState getNextTokenState(TokenState currentState, InputType input);

public:
    Tokenizer();
    void setInput(const string& newInput);
    void tokenize();
    const Token* getTokens() const;
    int getTokenCount() const;
};

#endif