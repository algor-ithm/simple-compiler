#include "Tokenizer.h"

Tokenizer::Tokenizer()
{
    configJava0FSA();
}

void Tokenizer::configJava0FSA() {
    // Start state transitions
    tokenStateTable[START][LETTER] = IDENTIFIER_S;
    tokenStateTable[START][DIGIT] = DIGIT_S;
    tokenStateTable[START][ASTERISK] = OPERATION;
    tokenStateTable[START][PLUS] = OPERATION;
    tokenStateTable[START][MINUS] = OPERATION;
    tokenStateTable[START][SLASH] = SLASH_S;
    tokenStateTable[START][NEWLINE] = START;
    tokenStateTable[START][WHITESPACE] = START;
    tokenStateTable[START][EQUALS] = EQUALS_S;
    tokenStateTable[START][LESS] = LESS_S;
    tokenStateTable[START][GREATER] = GREATER_S;
    tokenStateTable[START][EXCLAMATION] = EXCLAMATION_S;
    tokenStateTable[START][COMMA] = DELIMITER;
    tokenStateTable[START][SEMI] = DELIMITER;
    tokenStateTable[START][LEFT_BRACE] = BRACE;
    tokenStateTable[START][RIGHT_BRACE] = BRACE;
    tokenStateTable[START][LEFT_PAREN] = PAREN;
    tokenStateTable[START][RIGHT_PAREN] = PAREN;
    tokenStateTable[START][OTHER] = ERROR;
    //Error State
    for(int i = 0; i < I_COUNT; i++){
        tokenStateTable[ERROR][i] = START;
    }
    // Digit State
    for(int i = 0; i < I_COUNT; i++) {
        tokenStateTable[DIGIT_S][i] = DIGIT_FINAL;
    }
    tokenStateTable[DIGIT_S][DIGIT] = DIGIT_S;
    // Final Digit State
    for(int i = 0; i < I_COUNT; i++) {
        tokenStateTable[DIGIT_FINAL][i] = START;
    }
    // Identifier State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[IDENTIFIER_S][i] = IDENTIFIER_FINAL;
    }
    tokenStateTable[IDENTIFIER_S][LETTER] = IDENTIFIER_S;
    tokenStateTable[IDENTIFIER_S][DIGIT] = IDENTIFIER_S;
    // Final Identifier State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[IDENTIFIER_FINAL][i] = START;
    }
    // Slash State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[SLASH_S][i] = DIVISION;
    }
    tokenStateTable[SLASH_S][ASTERISK] = MULTI_LINE;
    tokenStateTable[SLASH_S][SLASH] = SINGLE_LINE;
    // Division State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[DIVISION][i] = START;
    }
    // Multi-line State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[MULTI_LINE][i] = MULTI_LINE;
    }
    tokenStateTable[MULTI_LINE][ASTERISK] = END_MULTI;
    // End Multi-line State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[END_MULTI][i] = MULTI_LINE;
    }
    tokenStateTable[END_MULTI][SLASH] = START;
    // Single Line State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[SINGLE_LINE][i] = SINGLE_LINE;
    }
    tokenStateTable[SINGLE_LINE][NEWLINE] = START;
    // Equals State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[EQUALS_S][i] = ASSIGNMENT;
    }
    tokenStateTable[EQUALS_S][EQUALS] = EQUALITY;
    // Assignment State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[ASSIGNMENT][i] = START;
    }
    // Equality State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[EQUALITY][i] = START;
    }
    // Less State
        for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[LESS_S][i] = LESS_THAN;
    }
    tokenStateTable[LESS_S][EQUALS] = LESS_EQUAL;
    // Less Than State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[LESS_THAN][i] = START;
    }
    // Less Than or Equal State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[LESS_EQUAL][i] = START;
    }
    // Greater State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[GREATER_S][i] = GREATER_THAN;
    }
    tokenStateTable[GREATER_S][EQUALS] = GREATER_EQUAL;
    // Greater Than State
        for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[LESS_THAN][i] = START;
    }
    // Greater Than or Equal State
        for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[LESS_THAN][i] = START;
    }
    // Exclamation State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[EXCLAMATION][i] = NOT;
    }
    tokenStateTable[EXCLAMATION][EQUALS] = NOT_EQUAL;
    // Not State    
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[LESS_THAN][i] = START;
    }
    // Not Equal State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[LESS_THAN][i] = START;
    }
    // Delimiter State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[LESS_THAN][i] = START;
    }
    // Braces  State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[LESS_THAN][i] = START;
    }
    // Parentheses State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[LESS_THAN][i] = START;
    }
}

// gets the nextState to transition from the tokenStateTable
TokenState Tokenizer::getNextTokenState(TokenState currentState, InputType input) {
    // verify state and input are in range
    if (currentState < 0 || currentState >= S_COUNT || input < 0 || input >= I_COUNT) {
        throw out_of_range("Current state or input is out of range.");
    }
    int nextState = tokenStateTable[currentState][input];
    return static_cast<TokenState>(nextState);
}

// Set the input string for the lexer
void Tokenizer::setInput(const string& newInput) {
    input = newInput;
    position = 0;
    tokens.clear(); // Clear previous tokens
}

// Get the vector of tokens
const vector<Token>& Tokenizer::getTokens() const {
    return tokens;
}

// Add a new token to the token vector
void Tokenizer::addTokens(const string& lexeme, const string& type) {
    tokens.emplace_back(Token(lexeme, type));
}

// Converts a character to its corresponding input
InputType Tokenizer::charToInputType(char ch) {
    switch (ch) {
        case '*':
            return ASTERISK;
        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '/':
            return SLASH;
        case '\n':
            return NEWLINE;
        case ' ':
        case '\t':
            return WHITESPACE;
        case '=':
            return EQUALS;
        case '<':
            return LESS;
        case '>':
            return GREATER;
        case '!':
            return EXCLAMATION;
        case ',':
            return COMMA;
        case ';':
            return SEMI;
        case '{':
            return LEFT_BRACE;
        case '}':
            return RIGHT_BRACE;
        case '(':
            return LEFT_PAREN;
        case ')':
            return RIGHT_PAREN;
        default:
            if (isalpha(ch)) return InputType::LETTER;
            else if(isdigit(ch)) return InputType::DIGIT;
            else return InputType::OTHER;
    }
}

// Maps each final state to its corresponding token type
string Tokenizer::mapStateToTokenType(TokenState state, const string& lexeme) const {
    switch(state){
        case OPERATION:
            if (lexeme == "+") return "ADDOP";
            if (lexeme == "-") return "SUBOP";
            if (lexeme == "*") return "MULOP";
            break;
        case IDENTIFIER_FINAL:
            // deal with keywords
            if (reservedWords.find(lexeme) != reservedWords.end()) {
                return lexeme; // It is a reserved word return as token type
            } else {
                return "IDENTIFIER"; // Not reserved treat as identifier
            }   
        case DIGIT_FINAL:
            return "NUMERIC_LITERAL";
        case DIVISION:
            return "DIVOP";
        case ASSIGNMENT:
            return "ASSIGN";
        case EQUALITY:
        case LESS_THAN:
        case LESS_EQUAL:
        case GREATER_THAN:
        case GREATER_EQUAL:
        case NOT:
        case NOT_EQUAL:
            return "RELOP";
        case DELIMITER:
            if (lexeme == ",") return "COMMA";
            if (lexeme == ";") return "SEMI";
            break;
        case BRACE:
            if (lexeme == "{") return "LEFT_BRACE";
            if (lexeme == "}") return "RIGHT_BRACE";
            return "RIGHT_BRACE";
        case PAREN:
            if (lexeme == "(") return "LEFT_PAREN";
            if (lexeme == ")") return "RIGHT_PAREN";
            break;
        default:
            return "OTHER";
    }
    return "UNKNOWN";
}


void Tokenizer::tokenize() {
    string currentLexeme;
    TokenState currentState = TokenState::START;

    while (position < input.length()) {
        // Get the next char and determine its input type
        char currentChar = input[position];
        InputType charType = charToInputType(currentChar);
        // Get the state to transition to passed on the char
        TokenState nextState = getNextTokenState(currentState, charType);
        // Determine course of action based on nextState
        switch(nextState) {
            case START:
                currentLexeme.clear();
                currentState = nextState;
                position++;
                break;
            case ERROR:
                cout << "Invalid character read in: " << currentChar << endl;
                position++;
                break;
            case OPERATION:
            case DELIMITER:
            case BRACE:
            case PAREN:
                currentLexeme = currentChar;
                addTokens(currentLexeme, mapStateToTokenType(nextState, currentLexeme));
                currentLexeme.clear();
                currentState = START;
                position++;
                break;
            case DIGIT_S:
            case IDENTIFIER_S:
            case SLASH_S:
            case EQUALS_S:
            case LESS_S:
            case GREATER_S:
            case EXCLAMATION_S:
                currentLexeme += currentChar;
                currentState = nextState;
                position++;
                break;
            case DIGIT_FINAL: 
            case IDENTIFIER_FINAL:
            case DIVISION:
            case ASSIGNMENT:
            case LESS_THAN:
            case GREATER_THAN:
            case NOT:
                addTokens(currentLexeme, mapStateToTokenType(nextState, currentLexeme));
                currentLexeme.clear();
                currentState = START;
                break;
            case EQUALITY:
            case LESS_EQUAL:
            case GREATER_EQUAL:
            case NOT_EQUAL:
                currentLexeme += currentChar;
                addTokens(currentLexeme, mapStateToTokenType(nextState, currentLexeme));
                currentLexeme.clear();
                currentState = START;
                position++;               
                break;
            case MULTI_LINE:
            case SINGLE_LINE:
            case END_MULTI:
                position++;
                currentState = nextState;
                break;
            default:
                cout << "Invalid State" << endl;
                break;
        }    
    }
    // Handle any left over characters in lexeme
    if (!currentLexeme.empty()) {
        //cout << "Current State: " << currentState << ", Lexeme: " << currentLexeme;
        addTokens(currentLexeme, mapStateToTokenType(currentState, currentLexeme));
    }
    // add EOF character?
    addTokens("EOF", "EOF");
}