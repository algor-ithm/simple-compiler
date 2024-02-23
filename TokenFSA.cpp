#include "TokenFSA.h"


TokenFSA::TokenFSA() {
    // Configure fsa for Java 0
    configJava0FSA();
}

// gets the nextState to transition from the stateTable
State TokenFSA::getNextState(State currentState, InputType input) {
    // verify state and input are in range
    if (currentState < 0 || currentState >= NUM_STATES || input < 0 || input >= NUM_INPUTS) {
        throw out_of_range("Current state or input is out of range.");
    }
    int nextState = stateTable[currentState][input];
    return static_cast<State>(nextState);
}

void TokenFSA::configJava0FSA() {
    // Start state transitions
    stateTable[START][LETTER] = IDENTIFIER_S;
    stateTable[START][DIGIT] = DIGIT_S;
    stateTable[START][ASTERISK] = OPERATION;
    stateTable[START][PLUS] = OPERATION;
    stateTable[START][MINUS] = OPERATION;
    stateTable[START][SLASH] = SLASH_S;
    stateTable[START][NEWLINE] = START;
    stateTable[START][WHITESPACE] = START;
    stateTable[START][EQUALS] = EQUALS_S;
    stateTable[START][LESS] = LESS_S;
    stateTable[START][GREATER] = GREATER_S;
    stateTable[START][EXCLAMATION] = EXCLAMATION_S;
    stateTable[START][COMMA] = DELIMITER;
    stateTable[START][SEMI] = DELIMITER;
    stateTable[START][LEFT_BRACE] = BRACE;
    stateTable[START][RIGHT_BRACE] = BRACE;
    stateTable[START][LEFT_PAREN] = PAREN;
    stateTable[START][RIGHT_PAREN] = PAREN;
    stateTable[START][OTHER] = ERROR;

    //Error State
    for (int i = 0; i < I_COUNT; i++){
        stateTable[ERROR][i] = START;
    }

    // Digit State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[DIGIT_S][i] = DIGIT_FINAL;
    }
    stateTable[DIGIT_S][DIGIT] = DIGIT_S;

    // Final Digit State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[State::DIGIT_FINAL][i] = START;
    }

    // Identifier State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[IDENTIFIER_S][i] = IDENTIFIER_FINAL;
    }
    stateTable[IDENTIFIER_S][LETTER] = IDENTIFIER_S;
    stateTable[IDENTIFIER_S][DIGIT] = IDENTIFIER_S;

    // Final Identifier State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[IDENTIFIER_FINAL][i] = START;
    }

    // Slash State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[SLASH_S][i] = State::DIVISION;
    }
    stateTable[SLASH_S][ASTERISK] = MULTI_LINE;
    stateTable[SLASH_S][SLASH] = SINGLE_LINE;

    // Division State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[DIVISION][i] = START;
    }

    // Multi-line State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[MULTI_LINE][i] = MULTI_LINE;
    }
    stateTable[MULTI_LINE][ASTERISK] = END_MULTI;

    // End Multi-line State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[END_MULTI][i] = MULTI_LINE;
    }
    stateTable[MULTI_LINE][SLASH] = START;

    // Single Line State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[SINGLE_LINE][i] = SINGLE_LINE;
    }
    stateTable[SINGLE_LINE][NEWLINE] = START;

    // Equals State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[EQUALS_S][i] = ASSIGNMENT;
    }
    stateTable[EQUALS_S][EQUALS] = EQUALITY;

    // Assignment State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[ASSIGNMENT][i] = START;
    }

    // Equality State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[EQUALITY][i] = START;
    }

    // Less State
        for (int i = 0; i < I_COUNT; i++) {
        stateTable[LESS_S][i] = LESS_THAN;
    }
    stateTable[LESS_S][EQUALS] = LESS_EQUAL;

    // Less Than State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[LESS_THAN][i] = START;
    }

    // Less Than or Equal State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[LESS_EQUAL][i] = START;
    }

    // Greater State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[GREATER_S][i] = GREATER_THAN;
    }
    stateTable[GREATER_S][EQUALS] = GREATER_EQUAL;

    // Greater Than State
        for (int i = 0; i < I_COUNT; i++) {
        stateTable[LESS_THAN][i] = START;
    }

    // Greater Than or Equal State
        for (int i = 0; i < I_COUNT; i++) {
        stateTable[LESS_THAN][i] = START;
    }

    // Exclamation State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[EXCLAMATION][i] = NOT;
    }
    stateTable[EXCLAMATION][EQUALS] = NOT_EQUAL;

    // Not State    
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[LESS_THAN][i] = START;
    }

    // Not Equal State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[LESS_THAN][i] = START;
    }

    // Delimiter State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[LESS_THAN][i] = START;
    }

    // Braces  State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[LESS_THAN][i] = START;
    }

    // Parentheses State
    for (int i = 0; i < I_COUNT; i++) {
        stateTable[LESS_THAN][i] = START;
    }
}

    