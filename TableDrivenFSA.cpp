#include "TableDrivenFSA.h";
#include <stdexcept>

TableDrivenFSA::TableDrivenFSA() {
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
void TableDrivenFSA::setStateTransition(State state, InputType input, State nextState) {
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
int TableDrivenFSA::getNextState(State currentState, InputType inputType) {
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
    // cast state to int
    int stateIndex = static_cast<int>(state);
    // verify state is in range
    if (stateIndex < 0 || stateIndex >= NUM_STATES) {
        throw out_of_range("State out of range.");
    }
    return finalStates[stateIndex];
}

void TableDrivenFSA::configureFinalStates() {
    // Final token states: no transition needed
    setFinalState(State::ERROR);
    setFinalState(State::OPERATION);
    setFinalState(State::DIGIT_FINAL);
    setFinalState(State::IDENTIFER_FINAL);
    setFinalState(State::DIVISION);
    setFinalState(State::Assignment);
    setFinalState(State::Equality);
    setFinalState(State::LessThan);
    setFinalState(State::LessEqual);
    setFinalState(State::GreaterThan);
    setFinalState(State::GreaterEqual);
    setFinalState(State::Not);
    setFinalState(State::NotEqual);
    setFinalState(State::Delimiter);
    setFinalState(State::LeftBrace);
    setFinalState(State::EndFile);
    setFinalState(State::RightBrace);
    setFinalState(State::Parentheses);
}

void TableDrivenFSA::configureTransitions() {
    // START State
    setStateTransition(State::START, InputType::Letter, State::IDENTIFIER);
    setStateTransition(State::START, InputType::Digit, State::DIGIT);
    setStateTransition(State::START, InputType::Asterisk, State::OPERATION);
    setStateTransition(State::START, InputType::Plus, State::OPERATION);
    setStateTransition(State::START, InputType::Minus, State::OPERATION);
    setStateTransition(State::START, InputType::Slash, State::SLASH);
    setStateTransition(State::START, InputType::Newline, State::START);
    setStateTransition(State::START, InputType::Whitespace, State::START);
    setStateTransition(State::START, InputType::Equals, State::Equals);
    setStateTransition(State::START, InputType::Less, State::Less);
    setStateTransition(State::START, InputType::Greater, State::Greater);
    setStateTransition(State::START, InputType::Exclamation, State::Exclamation);
    setStateTransition(State::START, InputType::Comma, State::Delimiter);
    setStateTransition(State::START, InputType::Semi, State::Delimiter);
    setStateTransition(State::START, InputType::LeftBrace, State::LeftBrace);
    setStateTransition(State::START, InputType::RightBrace, State::RightBrace);
    setStateTransition(State::START, InputType::LeftParen, State::Parentheses);
    setStateTransition(State::START, InputType::RightParen, State::Parentheses);
    setStateTransition(State::START, InputType::EndFile, State::EndFile);
    setStateTransition(State::START, InputType::Other, State::ERROR);
    
    // Digit State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::DIGIT, static_cast<InputType>(input), State::DIGIT_FINAL);
    }
    setStateTransition(State::DIGIT, InputType::Digit, State::DIGIT);

    // Identifier State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::IDENTIFIER, static_cast<InputType>(input), State::IDENTIFER_FINAL);
    }
    setStateTransition(State::IDENTIFIER, InputType::Letter, State::IDENTIFIER);
    setStateTransition(State::IDENTIFIER, InputType::Digit, State::IDENTIFIER);

    // Slash State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::SLASH, static_cast<InputType>(input), State::DIVISION);
    }
    setStateTransition(State::SLASH, InputType::Asterisk, State::MULTI_LINE);
    setStateTransition(State::SLASH, InputType::Slash, State::SingleLine);

    // Multi-line Comment State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::MULTI_LINE, static_cast<InputType>(input), State::MULTI_LINE);
    }
    setStateTransition(State::MULTI_LINE, InputType::Asterisk, State::END_MULTI);

    // End Multi-line Comment State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::END_MULTI, static_cast<InputType>(input), State::MULTI_LINE);
    }
    setStateTransition(State::END_MULTI, InputType::Slash, State::START);

    // Single Line Comment State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::SingleLine, static_cast<InputType>(input), State::SingleLine);
    }
    setStateTransition(State::END_MULTI, InputType::Slash, State::START);

    // Equal State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::Equals, static_cast<InputType>(input), State::Assignment);
    }
    setStateTransition(State::Equals, InputType::Equals, State::Equality);

    // Less State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::Less, static_cast<InputType>(input), State::LessThan);
    }
    setStateTransition(State::Less, InputType::Equals, State::LessEqual);

    // Greater State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::Greater, static_cast<InputType>(input), State::GreaterThan);
    }
    setStateTransition(State::Greater, InputType::Equals, State::GreaterEqual);

    // Exclamation State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::Exclamation, static_cast<InputType>(input), State::Not);
    }
    setStateTransition(State::Exclamation, InputType::Equals, State::NotEqual);

    // Right Brace State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::RightBrace, static_cast<InputType>(input), State::RightBraceFinal);
    }
    setStateTransition(State::RightBrace, InputType::EndFile, State::EndFile);
}

// construct FSA for Java 0 function
void TableDrivenFSA::configJava0FSA() {
    configureFinalStates();
    configureTransitions();
}