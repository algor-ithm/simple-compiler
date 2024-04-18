#ifndef PARSER_H
#define PARSER_H

#include "enumDefinitions.h"
#include "Tokenizer.h"
#include <iostream>
#include <string>

using  namespace std;

const int MAX_LABELS = 15;
const int MAX_QUADS = 100;
struct Quad { 
    string op;
    string leftArg;
    string rightArg;
    string result;

    Quad() : op(""), leftArg(""), rightArg(""), result("") {}

    Quad(const string& o, const string& a1, const string& a2, const string& r)
        : op(o), leftArg(a1), rightArg(a2), result(r) {}
};
class Parser {
private:
    char opPrecedence[OP_COUNT][OP_COUNT];
    void configOpTable();
    Token parseStack[MAX_TOKENS];
    string fixUpStack[MAX_LABELS];
    string whileStack[MAX_LABELS];
    string elseStack[MAX_LABELS];
    Quad quads[MAX_QUADS];
    int pStackSize = 0;
    int fStackSize = 0;
    int wStackSize = 0;
    int eStackSize = 0;
    int quadCount = 0;
    int labelCount = 1;
    int tempCount = 1;
    int whileCount = 1;
    bool isRecursive;
    ParserOps getNextStackOp();
    char getRelation(ParserOps op1, ParserOps op2);
    ParserOps getTokenOpType(const Token& token);
    string generateTemp();
    string generateLabel();
    string generateJump(Quad quad);
    string generateWhileLabel();
    string generateRecursiveLabel();
    void performReduction();
    void handleClosingBrace();
    void handleClosingParen();
    void handleIf();
    void handleThen();
    void handleElse();
    void popIfThen();
    void popIfThenElse();
    void handleWhile();
    void handleDo();
    void popWhileDo();
    void handleIO(Token currentToken, Token nextToken);
    void handleProcedureStart(string procName);
    void handleProcedureEnd(string procName);
    void handleCall(string procName);
    void handleReturn();
    void handleRecursion();
    void handleStart();
    bool isExecutable(Token t);
    // for debugging
    void printStack();
    void printQuads();
 
public:
    Parser();
    void parse(const Token* tokens, int tokenCount);
    const Quad* getQuads();
    int getQuadCount();
};

#endif