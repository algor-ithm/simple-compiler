#ifndef ENUM_DEFINITIONS_H
#define ENUM_DEFINITIONS_H

enum class State {
    Start,                // Initial state (0)
    Error,                // Error state (1)
    Operation,            // Operation state (2)
    Digit,                // Accumalate digit state (3)
    DigitFinal,           // Final digit state (4)
    Identifier,           // Identifier state (5)
    IdentifierFinal,      // Final identifier state (6)
    Slash,                // Slash state (7)
    DivisionFinal,        //  Division (single slash) state  (8)
    MultiLine,            // Multi-line comment start state (9)
    EndMulti,             // End of multi-line comment state (10)
    SingleLine,           // Single line comment state (11)
    Equals,               // Equals state (12)
    AssignFinal,          // Final assignment state (13)
    EqualityFinal,        // Final equality state (14) 
    LessThan,             // Less than state (15)
    LessFinal,            // Final less than state (16)
    LessEqualFinal,       // Final less than or equal to state (17)
    Greater,              // Greater than state (18)
    GreaterFinal,         // Final greater than state (19)
    GreaterEqualFinal,    // Final greater than or equal to state (20)
    DelimiterFinal,       // Final delimiter state (21)
    Exclamation,          // Exclamation state (22)
    NotEqualFinal,        // Final not equals state (23)
    LeftBraceFinal,       // Final left brace state (24)
    RightBrace,           // Right brace state (25)
    EOF,                  // End of file state (26)
    RightBraceFinal,      // final right brace state (27) 
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
    Comma,                // , (11)
    Semi,                 // ; (12)
    Exclamation,          // ! (13)
    LeftBrace,            // { (14)
    RightBrace,           // } (15)
    EOF,                  // EOF (16)
    Other,                // Anything else (17)
    COUNT                 // Keeps a count of the number of input types
};
#endif 
