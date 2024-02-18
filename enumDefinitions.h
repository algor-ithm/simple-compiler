#ifndef ENUM_DEFINITIONS_H
#define ENUM_DEFINITIONS_H

enum class State {
    START,                // Initial state (0)
    ERROR,                // error state (1)
    OPERATION,            // operation state (2)
    DIGIT,                // Accumalate digit state (3)
    DIGIT_FINAL,           // Final digit state (4)
    IDENTIFIER,           // Identifier state (5)
    IDENTIFER_FINAL,      // Final identifier state (6)
    SLASH,                // Slash state (7)
    DIVISION,             // Division (single slash) state  (8)
    MULTI_LINE,            // Multi-line comment start state (9)
    END_MULTI,             // End of multi-line comment state (10)
    SingleLine,           // Single line comment state (11)
    Equals,               // Equals state (12)
    Assignment,           // Final assignment state (13)
    Equality,             // Final equality state (14) 
    Less,                 // Less than state (15)
    LessThan,             // Final less than state (16)
    LessEqual,            // Final less than or equal to state (17)
    Greater,              // Greater than state (18)
    GreaterThan,          // Final greater than state (19)
    GreaterEqual,         // Final greater than or equal to state (20)
    Exclamation,          // Exclamation state (21)
    Not,                  // Not state (22)
    NotEqual,             // Final not equals state (23)
    Delimiter,            // Final delimiter state (24)
    LeftBrace,            // Final left brace state (25)
    RightBrace,           // Right brace state (26)
    EndFile,              // End of file state (27)
    RightBraceFinal,      // final right brace state (28)
    Parentheses,          // Final Parentheses state (29)
    COUNT                 // keeps a count of the number of states
};

enum InputType {
    Letter,               // Letter a..z, A..Z (0)
    Digit,                // Digits 0..9 (1)
    Asterisk,             // * (2)
    Plus,                 // + (3)
    Minus,                // - (4)
    Slash,                // / (5)
    Newline,              // /n (6)
    Whitespace,           // (7)
    Equals,               // = (8)
    Less,                 // < (9)
    Greater,              // > (10)
    Exclamation,          // ! (11)
    Comma,                // , (12)
    Semi,                 // ; (13)
    LeftBrace,            // { (14)
    RightBrace,           // } (15)
    LeftParen,            // ( (16)
    RightParen,           // ) (17)
    EndFile,              // EOF (18)
    Other,                // Anything else (19)
    COUNT                 // Keeps a count of the number of input types
};

// add reserved words?
#endif 
