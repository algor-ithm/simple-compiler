# include "TokenFSA.h"
#include "Lexer.h"


// token constructor
Token::Token(const string& lex, const string& lType) : 
    lexeme(lex), type(lType) {}

// Lexer Constrcutor
Lexer::Lexer(const TokenFSA& fsa) : fsa(fsa) {}

// Set the input string for the lexer
void Lexer::setInput(const string& newInput) {
    input = newInput;
    position = 0;
    tokens.clear(); // Clear previous tokens
}

// Get the vector of tokens
const vector<Token>& Lexer::getTokens() const {
    return tokens;
}

// Converts a character to its corresponding input
InputType Lexer::charToInputType(char ch) {
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

// Add a new token to the token vector
void Lexer::addTokens(const string& lexeme, const string& type) {
    tokens.push_back(Token(lexeme, type));
}

// Maps each final state to its corresponding token type
string Lexer::mapStateToTokenType(TokenState state, const string& lexeme) const {
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


void Lexer::tokenize() {
    string currentLexeme;
    TokenState currentState = TokenState::START;

    while (position < input.length()) {
        // Get the next char and determine its input type
        char currentChar = input[position];
        InputType charType = charToInputType(currentChar);
        // Get the state to transition to passed on the char
        TokenState nextState = fsa.getNextState(currentState, charType);
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
}

