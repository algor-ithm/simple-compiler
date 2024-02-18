// This table driven FSA is specifically intended for the Java 0 language
#ifndef TABLEDRIVENFSA_H
#define TABLEDRIVENFSA_H

#include "enumDefinitions.h"
using namespace std;

const int NUM_STATES = static_cast<int>(State::COUNT);
const int NUM_INPUTS = static_cast<int>(InputType::COUNT);

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
    TableDrivenFSA configJava0FSA();

};

#endif 