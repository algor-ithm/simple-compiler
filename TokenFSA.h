// This table driven FSA is specifically intended for the Java 0 language
#ifndef TOKENFSA_H
#define TOKENFSA_H

#include "enumDefinitions.h"
#include <vector>
#include <tuple>
#include <stdexcept>
using namespace std;

const int NUM_STATES = static_cast<int>(State::S_COUNT);
const int NUM_INPUTS = static_cast<int>(InputType::I_COUNT);

class TokenFSA
{
private:
    int stateTable[NUM_STATES][NUM_INPUTS] = {};
     void configJava0FSA();

public: 
    TokenFSA();
    State getNextState(State currentState, InputType input);
};

#endif 