#include "TableDrivenFSA.h"
#include <stdexcept>


TableDrivenFSA::TableDrivenFSA()
{
    //initialize stateTable with default value of -1
    for (int state = 0; state < NUM_STATES; state++) {
        for (int col = 0; col < NUM_INPUTS; col++) {
            stateTable[state][col] = -1;
        }
        // initial finalStates to false (non-final) 
        finalStates[state] = false;
    }
}

// sets a transition state for each state and input recieved
void TableDrivenFSA::setStateTransition(State state, InputType input, State nextState) {
    // cast enums to ints
    int stateIndex = static_cast<int>(state);
    int inputIndex = static_cast<int>(input);
    int nextStateEntry = static_cast<int> (nextState);

    // verify state and input are in range
    if(stateIndex < 0 || stateIndex >= NUM_STATES || inputIndex < 0 || inputIndex >= NUM_INPUTS) {
        throw out_of_range("Current state or input is out of range.");
    }
    // add transition to stateTable
    stateTable[stateIndex][inputIndex] = nextStateEntry;
}

// gets the nextState to transition to from the stateTable
int TableDrivenFSA::getNextState(State currentState, InputType inputType){
   // cast enums to ints
    int stateIndex = static_cast<int>(currentState);
    int inputIndex = static_cast<int>(inputType);

    // verify state and input are in range
    if(stateIndex < 0 || stateIndex >= NUM_STATES || inputIndex < 0 || inputIndex >= NUM_INPUTS) {
        throw out_of_range("Current state or input is out of range.");
    }
    return stateTable[stateIndex][inputIndex];
}

// set final states of stateTable
void TableDrivenFSA::setFinalState(State state) {
    // cast state to int
    int stateIndex = static_cast<int>(state);
    // verify state is in range
    if (stateIndex < 0 || stateIndex >= NUM_STATES) {
        throw out_of_range("State out of range.");
    }
    finalStates[stateIndex] = true;
}

bool TableDrivenFSA::isFinalState(State state) {
    //cast state to int
    int stateIndex = static_cast<int>(state);
    // verify state is in range
    if (stateIndex < 0 || stateIndex >= NUM_STATES) {
        throw out_of_range("State out of range.");
    }
    return finalStates[stateIndex];
}

// construct FSA for Java 0 function
TableDrivenFSA TableDrivenFSA::configJava0FSA() {
    TableDrivenFSA fsa; 

    //Start State
    fsa.setStateTransition(State::Start, InputType::Letter, State::Identifier);
    fsa.setStateTransition(State::Start, InputType::Digit, State::Digit);
    fsa.setStateTransition(State::Start, InputType::Asterisk, State::Operation);
    fsa.setStateTransition(State::Start, InputType::Plus, State::Operation);
    fsa.setStateTransition(State::Start, InputType::Minus, State::Operation);
    fsa.setStateTransition(State::Start, InputType::Slash, State::Slash);
    fsa.setStateTransition(State::Start, InputType::Newline, State::Start);
    fsa.setStateTransition(State::Start, InputType::Whitespace, State::Start);
    fsa.setStateTransition(State::Start, InputType::Equals, State::Equals);
    fsa.setStateTransition(State::Start, InputType::Less, State::Less);
    fsa.setStateTransition(State::Start, InputType::Greater, State::Greater);
    fsa.setStateTransition(State::Start, InputType::Exclamation, State::Exclamation);
    fsa.setStateTransition(State::Start, InputType::Comma, State::Delimiter);
    fsa.setStateTransition(State::Start, InputType::Semi, State::Delimiter);
    fsa.setStateTransition(State::Start, InputType::LeftBrace, State::LeftBrace);
    fsa.setStateTransition(State::Start, InputType::RightBrace, State::RightBrace);
    fsa.setStateTransition(State::Start, InputType::LeftParen, State::Parentheses);
    fsa.setStateTransition(State::Start, InputType::RightParen, State::Parentheses);
    fsa.setStateTransition(State::Start, InputType::EndFile, State::EndFile);
    fsa.setStateTransition(State::Start, InputType::Other, State::Error);

    
    //Error state: No transitions needed final state; logic in lexer
    fsa.setFinalState(State::Error);

    //Final operation state
    fsa.setFinalState(State::Operation);

    //Transition from digit state

    //Final digit state
    fsa.setFinalState(State::DigitFinal);

    //Transition from identifier

    //Final indentifier state
    fsa.setFinalState(State::IdentifierFinal);

    //Transition from slash state

    //Final division state
    fsa.setFinalState(State::Division);

    // Transitions multiLine comment state

    // Transitions from end multiline comment state

    // Transitions fron single line comment state

    // Transitions from equal state

    // Final assignment state
    fsa.setFinalState(State::Assignment);

    // Final equality state
    fsa.setFinalState(State::Equality);

    // Transitions from less state

    // Final less than State
    fsa.setFinalState(State::LessThan);

    // Final lessEqual state
    fsa.setFinalState(State::LessEqual);

    // Transitions from greater state

    // Final greater than state
    fsa.setFinalState(State::GreaterThan);

    // Final greater than or equal state
    fsa.setFinalState(State::GreaterEqual);

    // Transitions from exclamation state

    // Final not state
    fsa.setFinalState(State::Not);

    // Final not equal to state
    fsa.setFinalState(State::NotEqual);

    // final delimiter state
    fsa.setFinalState(State::Delimiter);

    // final left brace state
    fsa.setFinalState(State::LeftBrace);

    // Transitions from right brace state

    // Final end file state
    fsa.setFinalState(State::EndFile);

    // Final right brace state
    fsa.setFinalState(State::RightBrace);

    // Final parentheses state
    fsa.setFinalState(State::Parentheses);

    return fsa;
}
