#include "SymbolTableBuilder.h"

SymbolTableBuilder::SymbolTableBuilder() {
    configSymbolTableFSA();
}

void SymbolTableBuilder::configSymbolTableFSA() {
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
    symbolStateTable[PGM_NAME][L_BRACE] = PGM_START;
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
    symbolStateTable[PROC_NAME][L_PAREN] = PGM_START;
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

// map the token list token type to FSA TokenType
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
    if(tokenType == "LEFT_BRACE") return L_BRACE;
    if(tokenType == "LEFT_PAREN") return L_PAREN;
    if(tokenType == "EOF") return END_FILE;
    return OTHER_T;
}

// Add symbol to symbol vecotr
void SymbolTableBuilder::addToSymbolTable(const string& token, const string& type, const string& value, int addr, const string& segment) {
    if (symbolCount < MAX_SYMBOLS){
        symbolList[symbolCount++] = SymbolTableEntry(token, type, value, to_string(addr), segment);
    } else {

    }
    //symbolList.emplace_back(SymbolTableEntry(token, type, value, to_string(addr), segment));
}

// return symbol list
const SymbolTableEntry* SymbolTableBuilder::getSymbolTable() const {
    return symbolList;
}

int SymbolTableBuilder::getSymbolCount() const {
    return symbolCount;
}

// build the symbol table with symbol table FSA
void SymbolTableBuilder::buildSymbolTable(const Token* tokens, int tokenCount){
    SymbolState currentState = START_S;
    string currentToken, currentType, currentValue;
    int codeAddress = 0;
    int dataAddress = 0;

    // Process each token from the token list
    for (int i = 0; i < tokenCount; i++){
        // get the token type
        TokenType tokenType = mapStringTypeToTokenType(tokens[i].type);
        SymbolState nextState = getNextSymbolState(currentState, tokenType);

        // If invalid just continue to next token (error handle later)
        if(nextState == INVALID_STATE)
            continue; 

        switch(nextState) {
            case CLASS_READ:
                break;
            case PGM_NAME:
                currentToken = tokens[i].lexeme;
                currentType = "PROGRAM_NAME";
                addToSymbolTable(currentToken, currentType, "?", codeAddress, "code");
                codeAddress += 2;
                break;
            case PGM_START:
                break;
            case CONST_DEC:
                break;
            case CONST_NAME:
                currentToken = tokens[i].lexeme;
                currentType = "CONSTVAR";
                break;
            case CONST_ASSIGN:
                break;
            case CONST_VAL:
                currentValue = tokens[i].lexeme;
                addToSymbolTable(currentToken, currentType, currentValue, dataAddress, "data");
                dataAddress += 2;
                break;
            case VAR_DEC:
                break;
            case VAR_NAME:
                currentToken = tokens[i].lexeme;
                currentType = tokens[i].type;
                addToSymbolTable(currentToken, currentType, "?", dataAddress, "data");
                dataAddress += 2;
                break;
            case PROC_DEC:
                break;
            case PROC_NAME:
                currentToken = tokens[i].lexeme;
                currentType = "PROCEDURE";
                addToSymbolTable(currentToken, currentType, "?", codeAddress, "code");
                codeAddress += 2;
                break;
            case PGM_BODY:
                break;
            case NUM_LIT:
                currentToken = tokens[i].lexeme;
                currentType = tokens[i].type;
                currentValue = tokens[i].lexeme;
                addToSymbolTable(currentToken, currentType, currentValue, dataAddress, "data");
                dataAddress += 2;
                break;
            case END_STATE:
                // add temp varaibles (3 to start can add more)
                addToSymbolTable("temp1", "INTVAR", "?", dataAddress, "data");
                dataAddress += 2;
                addToSymbolTable("temp2", "INTVAR", "?", dataAddress, "data");
                dataAddress += 2;
                addToSymbolTable("temp3", "INTVAR", "?", dataAddress, "data");
                dataAddress += 2;
                return;
        }
        currentState = nextState;
    }
}