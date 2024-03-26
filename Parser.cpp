#include "Parser.h"

Parser::Parser()
{
    configOpTable();
}

void Parser::configOpTable()
{
    for (int i = 0; i < PO_COUNT; i++)
    {
        for (int j = 0; j < PO_COUNT; j++)
        {
            opPrecedence[i][j] = '?';
        }
    }
    // semicolon
    opPrecedence[OP_SEMI][OP_ASSIGN] = '<';
    // assignment
    opPrecedence[OP_ASSIGN][OP_SEMI] = '>';
    opPrecedence[OP_ASSIGN][OP_ADD] = '<';
    opPrecedence[OP_ASSIGN][OP_SUB] = '<';
    opPrecedence[OP_ASSIGN][OP_LBRACE] = '<';
    opPrecedence[OP_ASSIGN][OP_MUL] = '<';
    opPrecedence[OP_ASSIGN][OP_DIV] = '<';
    opPrecedence[OP_ASSIGN][OP_RBRACE] = '>';
    // addition
    opPrecedence[OP_ADD][OP_SEMI] = '>';
    opPrecedence[OP_ADD][OP_ADD] = '>';
    opPrecedence[OP_ADD][OP_SUB] = '>';
    opPrecedence[OP_ADD][OP_LBRACE] = '<';
    opPrecedence[OP_ADD][OP_RBRACE] = '>';
    opPrecedence[OP_ADD][OP_MUL] = '<';
    opPrecedence[OP_ADD][OP_DIV] = '<';
    opPrecedence[OP_ADD][OP_THEN] = '>';
    opPrecedence[OP_ADD][OP_DO] = '>';
    opPrecedence[OP_ADD][OP_EQ] = '>';
    opPrecedence[OP_ADD][OP_NE] = '>';
    opPrecedence[OP_ADD][OP_GT] = '>';
    opPrecedence[OP_ADD][OP_LT] = '>';
    opPrecedence[OP_ADD][OP_GTE] = '>';
    opPrecedence[OP_ADD][OP_LTE] = '>';
    opPrecedence[OP_ADD][OP_RBRACE] = '>';
    // subtraction
    opPrecedence[OP_SUB][OP_SEMI] = '>';
    opPrecedence[OP_SUB][OP_ADD] = '>';
    opPrecedence[OP_SUB][OP_SUB] = '>';
    opPrecedence[OP_SUB][OP_LBRACE] = '<';
    opPrecedence[OP_SUB][OP_RBRACE] = '>';
    opPrecedence[OP_SUB][OP_MUL] = '<';
    opPrecedence[OP_SUB][OP_DIV] = '<';
    opPrecedence[OP_SUB][OP_THEN] = '>';
    opPrecedence[OP_SUB][OP_DO] = '>';
    opPrecedence[OP_SUB][OP_EQ] = '>';
    opPrecedence[OP_SUB][OP_NE] = '>';
    opPrecedence[OP_SUB][OP_GT] = '>';
    opPrecedence[OP_SUB][OP_LT] = '>';
    opPrecedence[OP_SUB][OP_GTE] = '>';
    opPrecedence[OP_SUB][OP_LTE] = '>';
    opPrecedence[OP_SUB][OP_RBRACE] = '>';
    // left parentheses
    opPrecedence[OP_LPAREN][OP_ADD] = '<';
    opPrecedence[OP_LPAREN][OP_SUB] = '<';
    opPrecedence[OP_LPAREN][OP_LPAREN] = '<';
    opPrecedence[OP_LPAREN][OP_RPAREN] = '=';
    opPrecedence[OP_LPAREN][OP_MUL] = '<';
    opPrecedence[OP_LPAREN][OP_DIV] = '<';
    // right parentheses
    opPrecedence[OP_RPAREN][OP_SEMI] = '>';
    opPrecedence[OP_RPAREN][OP_ADD] = '>';
    opPrecedence[OP_RPAREN][OP_SUB] = '>';
    opPrecedence[OP_RPAREN][OP_RPAREN] = '>';
    opPrecedence[OP_RPAREN][OP_MUL] = '>';
    opPrecedence[OP_RPAREN][OP_DIV] = '>';
    // multiplication
    opPrecedence[OP_MUL][OP_SEMI] = '>';
    opPrecedence[OP_MUL][OP_ADD] = '>';
    opPrecedence[OP_MUL][OP_SUB] = '>';
    opPrecedence[OP_MUL][OP_LPAREN] = '<';
    opPrecedence[OP_MUL][OP_RPAREN] = '>';
    opPrecedence[OP_MUL][OP_MUL] = '>';
    opPrecedence[OP_MUL][OP_DIV] = '>';
    opPrecedence[OP_MUL][OP_THEN] = '>';
    opPrecedence[OP_MUL][OP_DO] = '>';
    opPrecedence[OP_MUL][OP_EQ] = '>';
    opPrecedence[OP_MUL][OP_NE] = '>';
    opPrecedence[OP_MUL][OP_GT] = '>';
    opPrecedence[OP_MUL][OP_LT] = '>';
    opPrecedence[OP_MUL][OP_GTE] = '>';
    opPrecedence[OP_MUL][OP_LTE] = '>';
    opPrecedence[OP_MUL][OP_RBRACE] = '>';
    // divide
    opPrecedence[OP_DIV][OP_SEMI] = '>';
    opPrecedence[OP_DIV][OP_ADD] = '>';
    opPrecedence[OP_DIV][OP_SUB] = '>';
    opPrecedence[OP_DIV][OP_LPAREN] = '<';
    opPrecedence[OP_DIV][OP_RPAREN] = '>';
    opPrecedence[OP_DIV][OP_MUL] = '>';
    opPrecedence[OP_DIV][OP_DIV] = '>';
    opPrecedence[OP_DIV][OP_THEN] = '>';
    opPrecedence[OP_DIV][OP_DO] = '>';
    opPrecedence[OP_DIV][OP_EQ] = '>';
    opPrecedence[OP_DIV][OP_NE] = '>';
    opPrecedence[OP_DIV][OP_GT] = '>';
    opPrecedence[OP_DIV][OP_LT] = '>';
    opPrecedence[OP_DIV][OP_GTE] = '>';
    opPrecedence[OP_DIV][OP_LTE] = '>';
    opPrecedence[OP_DIV][OP_RBRACE] = '>';
    // if
    opPrecedence[OP_IF][OP_ADD] = '<';
    opPrecedence[OP_IF][OP_SUB] = '<';
    opPrecedence[OP_IF][OP_LPAREN] = '<';
    opPrecedence[OP_IF][OP_MUL] = '<';
    opPrecedence[OP_IF][OP_DIV] = '<';
    opPrecedence[OP_IF][OP_THEN] = '=';
    opPrecedence[OP_IF][OP_ODD] = '<';
    opPrecedence[OP_IF][OP_EQ] = '<';
    opPrecedence[OP_IF][OP_NE] = '<';
    opPrecedence[OP_IF][OP_GT] = '<';
    opPrecedence[OP_IF][OP_LT] = '<';
    opPrecedence[OP_IF][OP_GTE] = '<';
    opPrecedence[OP_IF][OP_LTE] = '<';
    // then
    opPrecedence[OP_THEN][OP_ASSIGN] = '<';
    opPrecedence[OP_THEN][OP_IF] = '<';
    opPrecedence[OP_THEN][OP_WHILE] = '<';
    opPrecedence[OP_THEN][OP_RBRACE] = '<';
    opPrecedence[OP_THEN][OP_CALL] = '<';
    // while (not done)
    opPrecedence[OP_IF][OP_ADD] = '<';
    opPrecedence[OP_IF][OP_SUB] = '<';
    opPrecedence[OP_IF][OP_LPAREN] = '<';
    opPrecedence[OP_IF][OP_MUL] = '<';
    opPrecedence[OP_IF][OP_DIV] = '<';
    opPrecedence[OP_IF][OP_DO] = '=';
    opPrecedence[OP_IF][OP_ODD] = '<';
    opPrecedence[OP_IF][OP_EQ] = '<';
    opPrecedence[OP_IF][OP_NE] = '<';
    opPrecedence[OP_IF][OP_GT] = '<';
    opPrecedence[OP_IF][OP_LT] = '<';
    opPrecedence[OP_IF][OP_GTE] = '<';
    opPrecedence[OP_IF][OP_LTE] = '<';
    // do
    opPrecedence[OP_DO][OP_ASSIGN] = '<';
    opPrecedence[OP_DO][OP_IF] = '<';
    opPrecedence[OP_DO][OP_WHILE] = '<';
    opPrecedence[OP_DO][OP_LBRACE] = '<';
    opPrecedence[OP_DO][OP_CALL] = '<';
    // odd
    opPrecedence[OP_ODD][OP_ADD] = '<';
    opPrecedence[OP_ODD][OP_SUB] = '<';
    opPrecedence[OP_ODD][OP_LPAREN] = '<';
    opPrecedence[OP_ODD][OP_MUL] = '<';
    opPrecedence[OP_ODD][OP_DIV] = '<';
    opPrecedence[OP_ODD][OP_THEN] = '>';
    opPrecedence[OP_ODD][OP_DO] = '>';
    // equals 
    opPrecedence[OP_EQ][OP_ADD] = '<';
    opPrecedence[OP_EQ][OP_SUB] = '<';
    opPrecedence[OP_EQ][OP_LPAREN] = '<';
    opPrecedence[OP_EQ][OP_MUL] = '<';
    opPrecedence[OP_EQ][OP_DIV] = '<';
    opPrecedence[OP_EQ][OP_THEN] = '>';
    opPrecedence[OP_EQ][OP_DO] = '>';
    // not equals
    opPrecedence[OP_NE][OP_ADD] = '<';
    opPrecedence[OP_NE][OP_SUB] = '<';
    opPrecedence[OP_NE][OP_LPAREN] = '<';
    opPrecedence[OP_NE][OP_MUL] = '<';
    opPrecedence[OP_NE][OP_DIV] = '<';
    opPrecedence[OP_NE][OP_THEN] = '>';
    opPrecedence[OP_NE][OP_DO] = '>';
    // greater than
    opPrecedence[OP_GT][OP_ADD] = '<';
    opPrecedence[OP_GT][OP_SUB] = '<';
    opPrecedence[OP_GT][OP_LPAREN] = '<';
    opPrecedence[OP_GT][OP_MUL] = '<';
    opPrecedence[OP_GT][OP_DIV] = '<';
    opPrecedence[OP_GT][OP_THEN] = '>';
    opPrecedence[OP_GT][OP_DO] = '>';
    // less than
    opPrecedence[OP_LT][OP_ADD] = '<';
    opPrecedence[OP_LT][OP_SUB] = '<';
    opPrecedence[OP_LT][OP_LPAREN] = '<';
    opPrecedence[OP_LT][OP_MUL] = '<';
    opPrecedence[OP_LT][OP_DIV] = '<';
    opPrecedence[OP_LT][OP_THEN] = '>';
    opPrecedence[OP_LT][OP_DO] = '>';
    // greather than or equals
    opPrecedence[OP_GTE][OP_ADD] = '<';
    opPrecedence[OP_GTE][OP_SUB] = '<';
    opPrecedence[OP_GTE][OP_LPAREN] = '<';
    opPrecedence[OP_GTE][OP_MUL] = '<';
    opPrecedence[OP_GTE][OP_DIV] = '<';
    opPrecedence[OP_GTE][OP_THEN] = '>';
    opPrecedence[OP_GTE][OP_DO] = '>';
    // less than or equals
    opPrecedence[OP_LTE][OP_ADD] = '<';
    opPrecedence[OP_LTE][OP_SUB] = '<';
    opPrecedence[OP_LTE][OP_LPAREN] = '<';
    opPrecedence[OP_LTE][OP_MUL] = '<';
    opPrecedence[OP_LTE][OP_DIV] = '<';
    opPrecedence[OP_LTE][OP_THEN] = '>';
    opPrecedence[OP_LTE][OP_DO] = '>';
    // left brace
    opPrecedence[OP_LBRACE][OP_ASSIGN] = '<';
    opPrecedence[OP_LBRACE][OP_IF] = '<';
    opPrecedence[OP_LBRACE][OP_WHILE] = '<';
    opPrecedence[OP_LBRACE][OP_RBRACE] = '=';
    opPrecedence[OP_LBRACE][OP_CALL] = '<';
}