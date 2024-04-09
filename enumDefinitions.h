#ifndef ENUM_DEFINITIONS_H
#define ENUM_DEFINITIONS_H

#include <unordered_set>
#include <string>

using namespace std;

// State enum definitions for token list
enum TokenState {
    START,                // Initial state (0)
    ERROR,                // error state (1)
    OPERATION,            // operation state (2)
    DIGIT_S,              // Accumalate digit state (3)
    DIGIT_FINAL,          // Final digit state (4)
    IDENTIFIER_S,         // Identifier state (5)
    IDENTIFIER_FINAL,     // Final identifier state (6)
    SLASH_S,              // Slash state (7)
    DIVISION,             // Division (single slash) state  (8)
    MULTI_LINE,           // Multi-line comment start state (9)
    END_MULTI,            // End of multi-line comment state (10)
    SINGLE_LINE,          // Single line comment state (11)
    EQUALS_S,             // Equals state (12)
    ASSIGNMENT,           // Final assignment state (13)
    EQUALITY,             // Final equality state (14) 
    LESS_S,               // Less than state (15)
    LESS_THAN,            // Final less than state (16)
    LESS_EQUAL,           // Final less than or equal to state (17)
    GREATER_S,            // Greater than state (18)
    GREATER_THAN,         // Final greater than state (19)
    GREATER_EQUAL,        // Final greater than or equal to state (20)
    EXCLAMATION_S,        // Exclamation state (21)
    NOT,                  // Not state (22)
    NOT_EQUAL,            // Final not equals state (23)
    DELIMITER,            // Final delimiter state (24)
    BRACE,                // Final brace state (25)
    PAREN,                // Final Parenthesis state (26)
    S_COUNT               // keeps a count of the number of states
};

// input tye enums for character types
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
    OTHER,                // Anything else (18)
    I_COUNT               // Keeps a count of the number of input types
};

// reserved words set to check if an identifier is actually a reserved word
const unordered_set<string> reservedWords = {
    "CLASS",
    "VAR",
    "CONST",
    "IF",
    "WHILE",
    "THEN",
    "PROCEDURE",
    "CALL",
    "DO",
    "ODD",
    "GET",
    "PUT",
    "ELSE"
};

// states for Symbol Table FSA
enum SymbolState{
    START_S,            // Start State (0)
    CLASS_READ,         // Reading class token state (1)
    PGM_NAME,           // Expecting program name state (2)
    PGM_START,          // Start of program body state (3)
    CONST_DEC,          // Constant variable decleration state (4)
    CONST_NAME,         // Constant variable name state (5)
    CONST_ASSIGN,       // Constant variable = state (6)
    CONST_VAL,          // Constant integer value state (7)
    VAR_DEC,            // Variable decleration state (8)
    VAR_NAME,           // Variable name state (9)
    PROC_DEC,           // Procedure delceration sate (10)
    PROC_NAME,          // Procedure name state (11)
    PGM_BODY,           // Body of the program state (12)
    NUM_LIT,            // Numeric literal state (13)
    END_STATE,          // End of file state (done with pass) (14)
    SS_COUNT            // Count of the number of symbol states
};

// token (fsa input) for Symbol Table FSA
enum TokenType {
    CLASS,              // Class token type (0)
    CONST,              // Const token type (1)
    VAR,                // Var decleration token type (2)
    IDENTIFIER,         // Identifier state (3)
    NUMERIC_LIT,        // Numerical literal token type (4)
    PROCEDURE,          // Procedure decleration token type (5)
    ASSIGN,             // Assignment (=) token type (6)
    SEMICOLON,          // Semicolon (;) token type (7)
    COMMA_T,            // Comma (,) token type (8)
    L_BRACE,            // Left brace ({) token type (9)
    L_PAREN,            // Left parenthesis token type (10)
    END_FILE,           // EOF string (11)
    OTHER_T,            // All other token types (12)
    TT_COUNT            // Count of the number of token types
};

enum ParserOps {
    OP_SEMI,            // [;] semicolon (0)
    OP_ASSIGN,          // [=] assignment (1)
    OP_ADD,             // [+] addition (2)
    OP_SUB,             // [-] subtraction (3)
    OP_LPAREN,          // [(] left parentheses (4)
    OP_RPAREN,          // [)] right parentheses (5)
    OP_MUL,             // [*] multiply (6)
    OP_DIV,             // [/] divide (7)
    OP_IF,              // [if] reserved word (8)
    OP_THEN,            // [then] reserved word (9)
    OP_WHILE,           // [while] reserved word (10)
    OP_DO,              // [do] reserved word (11)
    OP_ODD,             // [odd] reserved word (12) 
    OP_EQ,              // [==] equality relop (13)
    OP_NE,              // [!=] not equal relop (14)    
    OP_GT,              // [>] greater than relop (15)
    OP_LT,              // [<] less than relop (16)
    OP_GTE,             // [>=] greater than or equal relop (17)
    OP_LTE,             // [<=] less than or equal relop (18)
    OP_LBRACE,          // [{] left brace (19)
    OP_RBRACE,          // [}] right brace (20)
    OP_CALL,            // [call] reserved word (20)
    OP_COMMA,
    OP_ELSE,           // [,] comma (21)            
    OP_COUNT,           // Operator count 
    NON_OP              // Used the represent non terminals (not part of table)
};

#endif
