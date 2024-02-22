#include "Lexer.h"
#include <cctype>

Lexer::Lexer(const TokenFSA& fsa) : fsa(fsa) {}

// Set the input string for the lexer
void Lexer::setInput(const string& newInput) {
    input = newInput;
    position = 0;
    tokens.clear(); // Clear previous tokens
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
        case State::PARENTHESIS:
            if (lexeme == "(") return "LEFT_PAREN";
            if (lexeme == ")") return "RIGHT_PAREN";
            break;
        default:
            return "OTHER";
    }
}

void Lexer::tokenize() {
    string currentLexeme;
    State currentState = State::START;

    

    while (position < input.length()) {
        char currentChar = input[position];
        InputType inputType = charToInputType(currentChar);


    }
}
/* tokenize
current lexeme, current state
while input to read
    get current char
    get its input type
    get next state
    if invalid -> deal with error
    else
        use switch statement with current state to determine next move
    set current to nextstate
    if final state 
        add token and clear lexeme reset to start
    increase position
    finalize and token still being processed when input ends
*/

