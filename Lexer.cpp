#include "Lexer.h"

Lexer::Lexer(const TableDrivenFSA& fsa) : fsa(fsa) {}

/* SetInput Function
Bring entire file into functions
set poisition to 0
clear previous tokens
*/

/* charToInputType
    Convert each character to its input type
    have isaplha and isdigit functions
    convert other types
    return other as default
    maybe switch statement
*/

/* addToken
string lexeme + string token  
input into vector
*/

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

