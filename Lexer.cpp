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
            return InputType::RIGHT_PAREN;
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

// maybe a mapchartoinputtype

void Lexer::tokenize() {
    string currentLexeme;
    State currentState = State::START;
    string tokenType;

    while (position < input.length()) {
        // Get the next char and determine its input type
        char currentChar = input[position];
        InputType charType = charToInputType(currentChar);
        // Get the state to transition to passed on the char
        State nextState = fsa.getNextState(currentState, charType);
        // Determine course of action based on nextState
        switch(nextState) {
            case ERROR:
                cout << "Invalid character read in." << endl;
                break;
                position++;
            case OPERATION:
                currentLexeme = currentChar;
                if (currentLexeme == "+") 
                    tokenType = "addop";
                else if (currentLexeme == "-") 
                    tokenType = "subop";
                else 
                    tokenType = "mop";
                addTokens(currentLexeme, tokenType);
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
                addTokens(currentLexeme, "numeric_literal");
                currentLexeme.clear();
                currentState = START;
                break;
            case IDENTIFIER_FINAL:
                // check for keywords here
                addTokens(currentLexeme, "identifier");
                currentLexeme.clear();
                currentState = START;
                break;
            case DIVISION:
                addTokens(currentLexeme, "divop");
                currentLexeme.clear();
                currentState = START;
                break;
            case ASSIGNMENT:
                addTokens(currentLexeme, "assign");
                currentLexeme.clear();
                currentState = START;
                break;
            case EQUALITY:
            case LESS_EQUAL:
            case GREATER_EQUAL:
            case NOT_EQUAL:
                addTokens(currentLexeme, "relop");
                currentLexeme.clear();
                currentState = START;
                position++;               
                break;
            case LESS_THAN:
            case GREATER_THAN:
            case NOT:
                addTokens(currentLexeme, "relop");
                currentLexeme.clear();
                currentState = START;
                break;
            case DELIMITER:
                currentLexeme = currentChar;
                if (currentLexeme == ";") 
                    tokenType = "semi";
                else 
                    tokenType = "comma";
                addTokens(currentLexeme, tokenType);
                currentLexeme.clear();
                currentState = START;
                position++;
                break;
            case BRACE:
                currentLexeme = currentChar;
                if (currentLexeme == "{") 
                    tokenType = "left_brace";
                else 
                    tokenType = "right_brace";
                addTokens(currentLexeme, tokenType);
                currentLexeme.clear();
                currentState = START;
                position++;
                break;
            case PAREN:
                currentLexeme = currentChar;
                if (currentLexeme == "(") 
                    tokenType = "right_paren";
                else 
                    tokenType = "left_paren";
                addTokens(currentLexeme, tokenType);
                currentLexeme.clear();
                currentState = START;
                position++;
                break;
            default:
                cout << "Invalid State" << endl;
                break;
        }    
    }
}

