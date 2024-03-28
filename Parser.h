#ifndef PARSER_H
#define PARSER_H

#include "enumDefinitions.h"
#include "Tokenizer.h"
#include <iostream>
#include <string>

using  namespace std;

const int MAX_LABELS = 25;
const int MAX_QUADS = 500;
struct Quad {
    string op;
    string arg1;
    string arg2;
    string result;

    Quad() : op(""), arg1(""), arg2(""), result("") {}

    Quad(const string& o, const string& a1, const string& a2, const string& r)
        : op(o), arg1(a1), arg2(a2), result(r) {}
};
class Parser
{
private:
    char opPrecedence[OP_COUNT][OP_COUNT];
    void configOpTable();
    Token parseStack[MAX_TOKENS];
    string loopStack[MAX_LABELS];
    string fixUpStack[MAX_LABELS];
    int pStackSize = 0;
    int lStackSize = 0;
    int fStackSize = 0;
    int labelCount = 1;
    Quad quads[MAX_QUADS];
    char getRelation(ParserOps op1, ParserOps op2);
    ParserOps getTokenOp(const Token& token);
    string generateLabel();
    // handle / complete if
    // handle / complete while
    // reduction functions?
    // void addQuad(op, arg1, arg2, results);
 
public:
    Parser();
    void parse(const Token* tokens, int tokenCount);
    // const Quad* getQuads();
};

#endif