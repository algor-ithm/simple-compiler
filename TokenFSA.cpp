#include "TokenFSA.h"


TokenFSA::TokenFSA() {
    // Configure fsa for Java 0
    configJava0FSA();
}

// gets the nextState to transition from the TokenTable
TokenState TokenFSA::getNextState(TokenState currentState, InputType input) {
    // verify state and input are in range
    if (currentState < 0 || currentState >= NUM_STATES || input < 0 || input >= NUM_INPUTS) {
        throw out_of_range("Current state or input is out of range.");
    }
    int nextState = TokenTable[currentState][input];
    return static_cast<TokenState>(nextState);
}

void TokenFSA::configJava0FSA() {
    // Start state transitions
    TokenTable[START][LETTER] = IDENTIFIER_S;
    TokenTable[START][DIGIT] = DIGIT_S;
    TokenTable[START][ASTERISK] = OPERATION;
    TokenTable[START][PLUS] = OPERATION;
    TokenTable[START][MINUS] = OPERATION;
    TokenTable[START][SLASH] = SLASH_S;
    TokenTable[START][NEWLINE] = START;
    TokenTable[START][WHITESPACE] = START;
    TokenTable[START][EQUALS] = EQUALS_S;
    TokenTable[START][LESS] = LESS_S;
    TokenTable[START][GREATER] = GREATER_S;
    TokenTable[START][EXCLAMATION] = EXCLAMATION_S;
    TokenTable[START][COMMA] = DELIMITER;
    TokenTable[START][SEMI] = DELIMITER;
    TokenTable[START][LEFT_BRACE] = BRACE;
    TokenTable[START][RIGHT_BRACE] = BRACE;
    TokenTable[START][LEFT_PAREN] = PAREN;
    TokenTable[START][RIGHT_PAREN] = PAREN;
    TokenTable[START][OTHER] = ERROR;

    //Error State
    for (int i = 0; i < I_COUNT; i++){
        TokenTable[ERROR][i] = START;
    }

    // Digit State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[DIGIT_S][i] = DIGIT_FINAL;
    }
    TokenTable[DIGIT_S][DIGIT] = DIGIT_S;

    // Final Digit State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[DIGIT_FINAL][i] = START;
    }

    // Identifier State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[IDENTIFIER_S][i] = IDENTIFIER_FINAL;
    }
    TokenTable[IDENTIFIER_S][LETTER] = IDENTIFIER_S;
    TokenTable[IDENTIFIER_S][DIGIT] = IDENTIFIER_S;

    // Final Identifier State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[IDENTIFIER_FINAL][i] = START;
    }

    // Slash State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[SLASH_S][i] = DIVISION;
    }
    TokenTable[SLASH_S][ASTERISK] = MULTI_LINE;
    TokenTable[SLASH_S][SLASH] = SINGLE_LINE;

    // Division State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[DIVISION][i] = START;
    }

    // Multi-line State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[MULTI_LINE][i] = MULTI_LINE;
    }
    TokenTable[MULTI_LINE][ASTERISK] = END_MULTI;

    // End Multi-line State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[END_MULTI][i] = MULTI_LINE;
    }
    TokenTable[END_MULTI][SLASH] = START;

    // Single Line State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[SINGLE_LINE][i] = SINGLE_LINE;
    }
    TokenTable[SINGLE_LINE][NEWLINE] = START;

    // Equals State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[EQUALS_S][i] = ASSIGNMENT;
    }
    TokenTable[EQUALS_S][EQUALS] = EQUALITY;

    // Assignment State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[ASSIGNMENT][i] = START;
    }

    // Equality State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[EQUALITY][i] = START;
    }

    // Less State
        for (int i = 0; i < I_COUNT; i++) {
        TokenTable[LESS_S][i] = LESS_THAN;
    }
    TokenTable[LESS_S][EQUALS] = LESS_EQUAL;

    // Less Than State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[LESS_THAN][i] = START;
    }

    // Less Than or Equal State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[LESS_EQUAL][i] = START;
    }

    // Greater State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[GREATER_S][i] = GREATER_THAN;
    }
    TokenTable[GREATER_S][EQUALS] = GREATER_EQUAL;

    // Greater Than State
        for (int i = 0; i < I_COUNT; i++) {
        TokenTable[LESS_THAN][i] = START;
    }

    // Greater Than or Equal State
        for (int i = 0; i < I_COUNT; i++) {
        TokenTable[LESS_THAN][i] = START;
    }

    // Exclamation State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[EXCLAMATION][i] = NOT;
    }
    TokenTable[EXCLAMATION][EQUALS] = NOT_EQUAL;

    // Not State    
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[LESS_THAN][i] = START;
    }

    // Not Equal State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[LESS_THAN][i] = START;
    }

    // Delimiter State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[LESS_THAN][i] = START;
    }

    // Braces  State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[LESS_THAN][i] = START;
    }

    // Parentheses State
    for (int i = 0; i < I_COUNT; i++) {
        TokenTable[LESS_THAN][i] = START;
    }
}

    