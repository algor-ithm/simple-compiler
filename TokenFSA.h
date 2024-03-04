// This table driven FSA is specifically intended for the Java 0 language
#ifndef TokenFSA_H
#define TokenFSA_H

#include "enumDefinitions.h"
#include <vector>
#include <tuple>
#include <stdexcept>
using namespace std;

const int NUM_STATES = S_COUNT;
const int NUM_INPUTS = I_COUNT;

class TokenFSA
{
private:
    int TokenTable[NUM_STATES][NUM_INPUTS] = {};
     void configJava0FSA();

public: 
    TokenFSA();
    TokenState getNextState(TokenState currentState, InputType input);
};

#endif 