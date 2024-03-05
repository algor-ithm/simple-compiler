#include "SymbolTableBuilder.h"

SymbolTableBuilder::SymbolTableBuilder()
{
    configSymbolTableFSA();
}

void SymbolTableBuilder::configSymbolTableFSA() {
    // Use -1 to denote invalid state transitions (error handling later?)
    const int INVALID_STATE = -1;
    // Fill entire table with -1 initially
    for(int i = 0; i < SS_COUNT; i++) {
        for (int j = 0; j < TT_COUNT; j++) {
            symbolStateTable[i][j] = INVALID_STATE;
        }
    }
    // define all valid transitions
    // Start state
    symbolStateTable[START_S][CLASS] = CLASS_READ;
    // Read class state
    symbolStateTable[CLASS_READ][IDENTIFIER] = PGM_NAME;
    // Read program name state
    symbolStateTable[PGM_NAME][R_BRACE] = PGM_START;
    // Start of program body
    for (int i = 0; i < TT_COUNT; i++){
        symbolStateTable[PGM_START][i] = PGM_BODY;
    }
    symbolStateTable[PGM_START][CONST] = CONST_DEC;
    symbolStateTable[PGM_START][VAR] = VAR_DEC;
    symbolStateTable[PGM_START][PROCEDURE] = PROC_DEC;
    symbolStateTable[PGM_START][END_FILE] = INVALID_STATE;
    // Constant decleration state
    symbolStateTable[CONST_DEC][IDENTIFIER] = CONST_NAME;
    // Constant variable name state
    symbolStateTable[CONST_NAME][ASSIGN] = CONST_ASSIGN;
    // Constant assignemnt state
    symbolStateTable[CONST_ASSIGN][NUMERIC_LIT] = CONST_VAL;
    // Constant value state
    symbolStateTable[CONST_VAL][SEMICOLON] = PGM_START;
    symbolStateTable[CONST_VAL][COMMA_T] = CONST_DEC;
    // Variable decleration state
    symbolStateTable[VAR_DEC][IDENTIFIER] = VAR_NAME;
    // Variable name state
    symbolStateTable[VAR_NAME][SEMICOLON] = PGM_START;
    symbolStateTable[VAR_NAME][COMMA_T] = VAR_DEC;
    // Procedure decleration state
    symbolStateTable[PROC_DEC][IDENTIFIER] = PROC_NAME;
    // Procedure name state
    symbolStateTable[PROC_NAME][R_PAREN] = PGM_START;
    // Program body state
    for (int i = 0; i < TT_COUNT; i++) {
        symbolStateTable[PGM_BODY][i] = PGM_BODY;
    }
    symbolStateTable[PGM_BODY][CONST] = CONST_DEC;
    symbolStateTable[PGM_BODY][VAR] = VAR_DEC;
    symbolStateTable[PGM_BODY][PROCEDURE] = PROC_DEC;
    symbolStateTable[PGM_BODY][NUMERIC_LIT] = NUM_LIT;
    symbolStateTable[PGM_BODY][END_FILE] = END_STATE;
    // Numerical literal state
    for (int i = 0; i < TT_COUNT; i++) {
        symbolStateTable[NUM_LIT][i] = PGM_BODY;
    }
    symbolStateTable[NUM_LIT][END_FILE] = END_STATE;
    // End of File state (done with pass)
    for(int i = 0; i < TT_COUNT; i++){
        symbolStateTable[END_STATE][i] = START_S;
    }
}

// gets the nextState to transition from the symbolStateTable
SymbolState SymbolTableBuilder::getNextSymbolState(SymbolState currState, TokenType token) {
    if (currState < 0 || currState >= SS_COUNT || token < 0 || token >= TT_COUNT) {
        throw out_of_range("Current state or token is out of range.");
    }
    int nextState = symbolStateTable[currState][token];
    return static_cast<SymbolState>(nextState);
}

TokenType SymbolTableBuilder::mapStringTypeToTokenType(const string& tokenType){
    if(tokenType == "CLASS") return CLASS;
    if(tokenType == "CONST") return CONST;
    if(tokenType == "VAR") return VAR;
    if(tokenType == "IDENTIFIER") return IDENTIFIER;
    if(tokenType == "NUMERIC_LITERAL") return NUMERIC_LIT;
    if(tokenType == "PROCEDURE") return PROCEDURE;
    if(tokenType == "ASSIGN") return ASSIGN;
    if(tokenType == "SEMI") return SEMICOLON;
    if(tokenType == "COMMA") return COMMA_T;
    if(tokenType == "RIGHT_BRACE") return R_BRACE;
    if(tokenType == "RIGHT_PAREN") return R_PAREN;
    if(tokenType == "EOF") return END_FILE;
    return OTHER_T;
}