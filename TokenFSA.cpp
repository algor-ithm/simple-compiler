#include "TokenFSA.h";
#include <stdexcept>

TokenFSA::TokenFSA() {
    // initialize stateTable with default value of -1
    for (int state = 0; state < NUM_STATES; state++) {
        for (int col = 0; col < NUM_INPUTS; col++) {
            stateTable[state][col] = -1;
        }
        // initial finalStates to false (non-final)
        finalStates[state] = false;
    }
    // Configure fsa for Java 0
    configJava0FSA();
}

// sets a transition state for each state and input recieved
void TokenFSA::setStateTransition(State state, InputType input, State nextState) {
    // cast enums to ints
    int stateIndex = static_cast<int>(state);
    int inputIndex = static_cast<int>(input);
    int nextStateEntry = static_cast<int>(nextState);

    // verify state and input are in range
    if (stateIndex < 0 || stateIndex >= NUM_STATES || inputIndex < 0 || inputIndex >= NUM_INPUTS) {
        throw out_of_range("Current state or input is out of range.");
    }
    // add transition to stateTable
    stateTable[stateIndex][inputIndex] = nextStateEntry;
}

// gets the nextState to transition to from the stateTable
int TokenFSA::getNextState(State currentState, InputType inputType) {
    // cast enums to ints
    int stateIndex = static_cast<int>(currentState);
    int inputIndex = static_cast<int>(inputType);

    // verify state and input are in range
    if (stateIndex < 0 || stateIndex >= NUM_STATES || inputIndex < 0 || inputIndex >= NUM_INPUTS) {
        throw out_of_range("Current state or input is out of range.");
    }
    return stateTable[stateIndex][inputIndex];
}

// set final states of stateTable
void TokenFSA::setFinalState(State state) {
    // cast state to int
    int stateIndex = static_cast<int>(state);
    // verify state is in range
    if (stateIndex < 0 || stateIndex >= NUM_STATES) {
        throw out_of_range("State out of range.");
    }
    finalStates[stateIndex] = true;
}

bool TokenFSA::isFinalState(State state) {
    // cast state to int
    int stateIndex = static_cast<int>(state);
    // verify state is in range
    if (stateIndex < 0 || stateIndex >= NUM_STATES) {
        throw out_of_range("State out of range.");
    }
    return finalStates[stateIndex];
}

void TokenFSA::configureFinalStates() {
    // Final token states: no transition needed
    setFinalState(State::ERROR);
    setFinalState(State::OPERATION);
    setFinalState(State::DIGIT_FINAL);
    setFinalState(State::IDENTIFIER_FINAL);
    setFinalState(State::DIVISION);
    setFinalState(State::ASSIGNMENT);
    setFinalState(State::EQUALITY);
    setFinalState(State::LESS_THAN);
    setFinalState(State::LESS_EQUAL);
    setFinalState(State::GREATER_THAN);
    setFinalState(State::GREATER_EQUAL);
    setFinalState(State::NOT);
    setFinalState(State::NOT_EQUAL);
    setFinalState(State::DELIMITER);
    setFinalState(State::BRACE);
    setFinalState(State::PARENTHESIS);
}

//TODO: Add transition to Error state for other on all states
void TokenFSA::configureTransitions() {
    // START State
    setStateTransition(State::START, InputType::LETTER, State::IDENTIFIER);
    setStateTransition(State::START, InputType::DIGIT, State::DIGIT);
    setStateTransition(State::START, InputType::ASTERISK, State::OPERATION);
    setStateTransition(State::START, InputType::PLUS, State::OPERATION);
    setStateTransition(State::START, InputType::MINUS, State::OPERATION);
    setStateTransition(State::START, InputType::SLASH, State::SLASH);
    setStateTransition(State::START, InputType::NEWLINE, State::START);
    setStateTransition(State::START, InputType::WHITESPACE, State::START);
    setStateTransition(State::START, InputType::EQUALS, State::EQUALS);
    setStateTransition(State::START, InputType::LESS, State::LESS);
    setStateTransition(State::START, InputType::GREATER, State::GREATER);
    setStateTransition(State::START, InputType::EXCLAMATION, State::EXCLAMATION);
    setStateTransition(State::START, InputType::COMMA, State::DELIMITER);
    setStateTransition(State::START, InputType::SEMI, State::DELIMITER);
    setStateTransition(State::START, InputType::LEFT_BRACE, State::BRACE);
    setStateTransition(State::START, InputType::RIGHT_BRACE, State::BRACE);
    setStateTransition(State::START, InputType::LEFT_PAREN, State::PARENTHESIS);
    setStateTransition(State::START, InputType::RIGHT_PAREN, State::PARENTHESIS);
    setStateTransition(State::START, InputType::OTHER, State::ERROR);
    
    // Digit State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::DIGIT, static_cast<InputType>(input), State::DIGIT_FINAL);
    }
    setStateTransition(State::DIGIT, InputType::DIGIT, State::DIGIT);

    // Identifier State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::IDENTIFIER, static_cast<InputType>(input), State::IDENTIFIER_FINAL);
    }
    setStateTransition(State::IDENTIFIER, InputType::LETTER, State::IDENTIFIER);
    setStateTransition(State::IDENTIFIER, InputType::DIGIT, State::IDENTIFIER);

    // Slash State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::SLASH, static_cast<InputType>(input), State::DIVISION);
    }
    setStateTransition(State::SLASH, InputType::ASTERISK, State::MULTI_LINE);
    setStateTransition(State::SLASH, InputType::SLASH, State::SINGLE_LINE);

    // Multi-line Comment State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::MULTI_LINE, static_cast<InputType>(input), State::MULTI_LINE);
    }
    setStateTransition(State::MULTI_LINE, InputType::ASTERISK, State::END_MULTI);

    // End Multi-line Comment State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::END_MULTI, static_cast<InputType>(input), State::MULTI_LINE);
    }
    setStateTransition(State::END_MULTI, InputType::SLASH, State::START);

    // Single Line Comment State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::SINGLE_LINE, static_cast<InputType>(input), State::SINGLE_LINE);
    }
    setStateTransition(State::END_MULTI, InputType::SLASH, State::START);

    // Equal State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::EQUALS, static_cast<InputType>(input), State::ASSIGNMENT);
    }
    setStateTransition(State::EQUALS, InputType::EQUALS, State::EQUALITY);

    // Less State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::LESS, static_cast<InputType>(input), State::LESS_THAN);
    }
    setStateTransition(State::LESS, InputType::EQUALS, State::LESS_EQUAL);

    // Greater State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::GREATER, static_cast<InputType>(input), State::GREATER_THAN);
    }
    setStateTransition(State::GREATER, InputType::EQUALS, State::GREATER_EQUAL);

    // Exclamation State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::EXCLAMATION, static_cast<InputType>(input), State::NOT);
    }
    setStateTransition(State::EXCLAMATION, InputType::EQUALS, State::NOT_EQUAL);

    // Right Brace State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::RIGHT_BRACE, static_cast<InputType>(input), State::RIGHT_BRACE_FINAL);
    }
    setStateTransition(State::RIGHT_BRACE, InputType::END_FILE, State::END_FILE);
}

// construct FSA for Java 0 function
void TokenFSA::configJava0FSA() {
    configureFinalStates();
    configureTransitions();
}