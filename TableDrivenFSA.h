#ifndef TABLEDRIVENFSA_H
#define TABLEDRIVENFSA_H

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
    void setStateTransition(int state, int input, int nextState);
    int getNextState(int currentState, int inputType);
    void setFinalState(int state);
    bool isFinalState(int state);

};

#endif 