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
            return InputType::ASTERISK;
        case '+':
            return InputType::PLUS;
        case '-':
            return InputType::MINUS;
        case '/':
            return InputType::SLASH;
        case '\n':
            return InputType::NEWLINE;
        case ' ':
        case '\t':
            return InputType::WHITESPACE;
        case '=':
            return InputType::EQUALS;
        case '<':
            return InputType::LESS;
        case '>':
            return InputType::GREATER;
        case '!':
            return InputType::EXCLAMATION;
        case ',':
            return InputType::COMMA;
        case ';':
            return InputType::SEMI;
        case '{':
            return InputType::LEFT_BRACE;
        case '}':
            return InputType::RIGHT_BRACE;
        case '(':
            return InputType::LEFT_PAREN;
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
string Lexer::mapStateToTokenType(State state, const string& lexeme) const {
    switch(state){
        case State::OPERATION:
            if (lexeme == "+") return "ADDOP";
            if (lexeme == "-") return "SUBOP";
            if (lexeme == "*") return "MULOP";
            break;
        case State::IDENTIFIER_FINAL:
            // deal with keywords?
            return "IDENTIFIER";
        case State::DIGIT_FINAL:
            return "NUMERIC_LITERAL";
        case State::DIVISION:
            return "DIVOP";
        case State::ASSIGNMENT:
            return "ASSIGN";
        case State::EQUALITY:
        case State::LESS_THAN:
        case State::LESS_EQUAL:
        case State::GREATER_THAN:
        case State::GREATER_EQUAL:
        case State::NOT:
        case State::NOT_EQUAL:
            return "RELOP";
        case State::DELIMITER:
            if (lexeme == ",") return "COMMA";
            if (lexeme == ";") return "SEMI";
            break;
        case State::BRACE:
            if (lexeme == "{") return "LEFT_BRACE";
            if (lexeme == "}") return "RIGHT_BRACE";
            return "RIGHT_BRACE";
        case State::PAREN:
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
    State currentState = State::START;

    while (position < input.length()) {
        // Get the next char and determine its input type
        char currentChar = input[position];
        InputType charType = charToInputType(currentChar);
        // Get the state to transition to passed on the char
        State nextState = fsa.getNextState(currentState, charType);
        // Determine course of action based on nextState
        switch(nextState) {
            case START:
                currentLexeme.clear();
                currentState = nextState;
                position++;
                break;
            case ERROR:
                cout << "Invalid character read in." << endl;
                break;
                position++;
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
            case MULTI_LINE:
            case END_MULTI:
            case SINGLE_LINE:
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
            default:
                cout << "Invalid State" << endl;
                break;
        }    
    }
    // Handle any left over characters in lexeme
    if (!currentLexeme.empty()) {
        addTokens(currentLexeme, "UNKNOWN");
    }
}

