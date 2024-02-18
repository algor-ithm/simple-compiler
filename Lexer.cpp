#include "Lexer.h"
#include <cctype>

Lexer::Lexer(const TableDrivenFSA& fsa) : fsa(fsa) {}

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
            return InputType::Asterisk;
        case '+':
            return InputType::Plus;
        case '-':
            return InputType::Minus;
        case '/':
            return InputType::Slash;
        case '\n':
            return InputType::Newline;
        case ' ':
        case '\t':
            return InputType::Whitespace;
        case '=':
            return InputType::Equals;
        case '<':
            return InputType::Less;
        case '>':
            return InputType::Greater;
        case '!':
            return InputType::Exclamation;
        case ',':
            return InputType::Comma;
        case ';':
            return InputType::Semi;
        case '{':
            return InputType::LeftBrace;
        case '}':
            return InputType::RightBrace;
        case '(':
        case ')':
        default:
            if (isalpha(ch)) return InputType::Letter;
            else if(isdigit(ch)) return InputType::Digit;
            else return InputType::Other;
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
        case State::IDENTIFER_FINAL:
            // deal with keywords?
            return "INDENTIFIER";
        case State::DIGIT_FINAL:
            return "NUMERIC_LITERAL";
        default:
            return "OTHER";
    }

}
/* mapStateToTokenType
    map each final state to its token type for token list
    use switch state and pass the state return token type
*/

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

