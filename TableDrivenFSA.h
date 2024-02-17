#ifndef TABLEDRIVENFSA_H
#define TABLEDRIVENFSA_H

#include "enumDefinitions.h"
using namespace std;

const int NUM_STATES = 28;
const int NUM_INPUTS = 17;

class TableDrivenFSA
{
private:
    int stateTable[NUM_STATES][NUM_INPUTS];
    bool finalStates[NUM_STATES];

public: 
    TableDrivenFSA();
    void setStateTransition(State state, InputType input, State nextState);
    int getNextState(State currentState, InputType inputType);
    void setFinalState(State state);
    bool isFinalState(State state);

};

#endif 