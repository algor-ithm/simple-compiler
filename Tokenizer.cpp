#include "Tokenizer.h"

Tokenizer::Tokenizer() {
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
    // Digit State
    for(int i = 0; i < I_COUNT; i++) {
        tokenStateTable[DIGIT_S][i] = DIGIT_FINAL;
    }
    tokenStateTable[DIGIT_S][DIGIT] = DIGIT_S;
    tokenStateTable[DIGIT_S][OTHER] = ERROR;
    // Identifier State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[IDENTIFIER_S][i] = IDENTIFIER_FINAL;
    }
    tokenStateTable[IDENTIFIER_S][LETTER] = IDENTIFIER_S;
    tokenStateTable[IDENTIFIER_S][DIGIT] = IDENTIFIER_S;
    tokenStateTable[IDENTIFIER_S][OTHER] = ERROR;
    // Slash State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[SLASH_S][i] = DIVISION;
    }
    tokenStateTable[SLASH_S][ASTERISK] = MULTI_LINE;
    tokenStateTable[SLASH_S][SLASH] = SINGLE_LINE;
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
    // Less State
        for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[LESS_S][i] = LESS_THAN;
    }
    tokenStateTable[LESS_S][EQUALS] = LESS_EQUAL;
    // Greater State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[GREATER_S][i] = GREATER_THAN;
    }
    tokenStateTable[GREATER_S][EQUALS] = GREATER_EQUAL;
    // Exclamation State
    for (int i = 0; i < I_COUNT; i++) {
        tokenStateTable[EXCLAMATION][i] = NOT;
    }
    tokenStateTable[EXCLAMATION][EQUALS] = NOT_EQUAL;
    //Error State - already initialize to 0 (START)
    // Final Digit State - already initialize to 0 (START)
    // Final Identifier State - already initialize to 0 (START)
    // Division State - already initialize to 0 (START)
    // Assignment State -- already initialize to 0 (START)
    // Equality State - already initialize to 0 (START)
    // Less Than State - already initialize to 0 (START)
    // Less Than or Equal State - already initialize to 0 (START)
    // Greater Than State - already initialize to 0 (START)
    // Greater Than or Equal State - already initialize to 0 (START)
    // Not State - already initialize to 0 (START)
    // Not Equal State - already initialize to 0 (START)
    // Delimiter State - already initialize to 0 (START)
    // Braces  State - already initialize to 0 (START)
    // Parentheses State - already initialize to 0 (START)
}

// gets the nextState to transition from the tokenStateTable
TokenState Tokenizer::getNextTokenState(TokenState currentState, InputType input) {
    // verify state and input are in range
    if (currentState < 0 || currentState >= S_COUNT || input < 0 || input >= I_COUNT) 
        throw out_of_range("Current state or input is out of range.");
    return static_cast<TokenState>(tokenStateTable[currentState][input]);
}

// Set the input string for the lexer
void Tokenizer::setInput(const string& newInput) {
    input = newInput;
    position = 0;
    tokenCount = 0; // Clear previous tokens
}

// Get the vector of tokens
const Token* Tokenizer::getTokens() const {
    return tokens;
}

int Tokenizer::getTokenCount() const {
    return tokenCount;
}

// Add a new token to the token vector
void Tokenizer::addTokens(const string& lexeme, const string& type) {
    if (tokenCount < MAX_TOKENS)
        tokens[tokenCount++] = Token(lexeme, type);
    else 
        cerr << "Token array is full, cannot add more tokens." << endl;
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
            if (isalpha(ch)) return LETTER;
            else if(isdigit(ch)) return DIGIT;
            else return OTHER;
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
            if (reservedWords.find(lexeme) != reservedWords.end()) 
                return lexeme; // It is a reserved word return as token type
            else
                return "IDENTIFIER"; // Not reserved treat as identifier 
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
            break;
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
    string error;

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
                error = "ERROR: Invalid character read in: ";
                error += currentChar;
                cerr << error << endl;
                exit(EXIT_FAILURE);
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
                currentLexeme = "Lit" + currentLexeme;
                addTokens(currentLexeme, mapStateToTokenType(nextState, currentLexeme));
                currentLexeme.clear();
                currentState = START;
                break;
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
                cerr << "Invalid State" << endl;
                break;
        }    
    }
    // Handle any left over characters in lexeme
    if (!currentLexeme.empty()) 
        addTokens(currentLexeme, mapStateToTokenType(currentState, currentLexeme));
    // add EOF character?
    addTokens("EndFile", "EndFile");
}