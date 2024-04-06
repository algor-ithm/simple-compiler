#ifndef PARSER_H
#define PARSER_H

#include "enumDefinitions.h"
#include "Tokenizer.h"
#include <iostream>
#include <string>

using  namespace std;

const int MAX_LABELS = 15;
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
class Parser {
private:
    char opPrecedence[OP_COUNT][OP_COUNT];
    void configOpTable();
    Token parseStack[MAX_TOKENS];
    string fixUpStack[MAX_LABELS];
    string whileStack[MAX_LABELS];
    Quad quads[MAX_QUADS];
    int pStackSize = 0;
    int fStackSize = 0;
    int wStackSize = 0;
    int quadCount = 0;
    int labelCount = 1;
    int tempCount = 1;
    int whileCount = 1;
    ParserOps getNextStackOp();
    char getRelation(ParserOps op1, ParserOps op2);
    ParserOps getTokenOpType(const Token& token);
    string generateTemp();
    string generateLabel();
    string generateWhileLabel();
    // handle / complete if
    // handle / complete while
    bool isStructural(Token& token);
    void performReduction();
    bool tryReduceArithmetic();
    bool tryReduceBooleanExp();
    bool tryReduceAssignment();
    void handleClosingBrace();
    void handleClosingParen();
    void handleIf();
    void handleThen();
    void popIfThen();
    void handleWhile();
    void handleDo();
    void popWhileDo();
    void printStack();
    void printQuads();
 
public:
    Parser();
    void parse(const Token* tokens, int tokenCount);
    const Quad* getQuads();
    int getQuadCount();
};

#endif