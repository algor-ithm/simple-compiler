#include "TableDrivenFSA.h"
#include <stdexcept>

TableDrivenFSA::TableDrivenFSA()
{
    //initialize stateTable with default value of -1
    for (int row = 0; row < NUM_STATES; row++) {
        for (int col = 0; col < NUM_INPUTS; col++) {
            stateTable[row][col] = -1;
        }
        // initial finalStates to false (non-final) 
        finalStates[row] = false;
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
TableDrivenFSA configJava0FSA() {
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
    fsa.setStateTransition(State::Start, InputType::Less, State::LessThan);
    // TODO: finish other start state transitions

    
    //Error State: No transitions needed final state; logic in lexer
    fsa.setFinalState(State::Error);

    //Transition from Operation State

    //Transition from Digit State

    //Transition from Final Digit state

    //Transition from Identifier

    //Transition from Final Indentifer

    //Transition from 
}
