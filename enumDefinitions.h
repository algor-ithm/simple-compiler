#ifndef ENUM_DEFINITIONS_H
#define ENUM_DEFINITIONS_H

enum class State {
    START,                // Initial state (0)
    ERROR,                // error state (1)
    OPERATION,            // operation state (2)
    DIGIT,                // Accumalate digit state (3)
    DIGIT_FINAL,          // Final digit state (4)
    IDENTIFIER,           // Identifier state (5)
    IDENTIFER_FINAL,      // Final identifier state (6)
    SLASH,                // Slash state (7)
    DIVISION,             // Division (single slash) state  (8)
    MULTI_LINE,           // Multi-line comment start state (9)
    END_MULTI,            // End of multi-line comment state (10)
    SINGLE_LINE,          // Single line comment state (11)
    EQUALS,               // Equals state (12)
    ASSIGNMENT,           // Final assignment state (13)
    EQUALITY,             // Final equality state (14) 
    LESS,                 // Less than state (15)
    LESS_THAN,            // Final less than state (16)
    LESS_EQUAL,           // Final less than or equal to state (17)
    GREATER,              // Greater than state (18)
    GREATER_THAN,         // Final greater than state (19)
    GREATER_EQUAL,        // Final greater than or equal to state (20)
    EXCLAMATION,          // Exclamation state (21)
    NOT,                  // Not state (22)
    NOT_EQUAL,            // Final not equals state (23)
    DELIMITER,            // Final delimiter state (24)
    LEFT_BRACE,           // Final left brace state (25)
    RIGHT_BRACE,          // Right brace state (26)
    END_FILE,             // End of file state (27)
    RIGHT_BRACE_FINAL,    // final right brace state (28)
    PARENTHESIS,          // Final Parenthesis state (29)
    COUNT                 // keeps a count of the number of states
};

enum InputType {
    LETTER,               // Letter a..z, A..Z (0)
    DIGIT,                // Digits 0..9 (1)
    ASTERISK,             // * (2)
    PLUS,                 // + (3)
    MINUS,                // - (4)
    SLASH,                // / (5)
    NEWLINE,              // /n (6)
    WHITESPACE,           // (7)
    EQUALS,               // = (8)
    LESS,                 // < (9)
    GREATER,              // > (10)
    EXCLAMATION,          // ! (11)
    COMMA,                // , (12)
    SEMI,                 // ; (13)
    LEFT_BRACE,           // { (14)
    RIGHT_BRACE,          // } (15)
    LEFT_PAREN,           // ( (16)
    RIGHT_PAREN,          // ) (17)
    END_FILE,              // EOF (18)
    OTHER,                // Anything else (19)
    COUNT                 // Keeps a count of the number of input types
};

// add reserved words?
#endif 
