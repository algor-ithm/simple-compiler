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
void TableDrivenFSA::setStateTransition(int state, int input, int nextState) {
    // verify state and input are in range
    if(state < 0 || state >= NUM_STATES || input < 0 || input >= NUM_INPUTS) {
        throw out_of_range("Current state or input is out of range.");
    }
    // add transition to stateTable
    stateTable[state][input] = nextState;
}

// gets the nextState to transition to from the stateTable
int TableDrivenFSA::getNextState(int currentState, int inputType){
    // verify state and input are in range
    if (currentState < 0 || currentState >= NUM_STATES || inputType < 0 || inputType >= NUM_INPUTS) {
        throw out_of_range("Current state or input is out of range.");
    }
    // return nextState from stateTable
    return stateTable[currentState][inputType];
}

// set final states of stateTable
void TableDrivenFSA::setFinalState(int state) {
    // verify state is in range
    if (state < 0 || state >= NUM_STATES) {
        throw out_of_range("State out of range.");
    }
    finalStates[state] = true;
}

bool TableDrivenFSA::isFinalState(int state) {
    if (state < 0 || state >= NUM_STATES) {
        throw out_of_range("State out of range.");
    }
    return finalStates[state];
}


