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
    setFinalState(State::Error);
    setFinalState(State::Operation);
    setFinalState(State::DigitFinal);
    setFinalState(State::IdentifierFinal);
    setFinalState(State::Division);
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
    // Start State
    setStateTransition(State::Start, InputType::Letter, State::Identifier);
    setStateTransition(State::Start, InputType::Digit, State::Digit);
    setStateTransition(State::Start, InputType::Asterisk, State::Operation);
    setStateTransition(State::Start, InputType::Plus, State::Operation);
    setStateTransition(State::Start, InputType::Minus, State::Operation);
    setStateTransition(State::Start, InputType::Slash, State::Slash);
    setStateTransition(State::Start, InputType::Newline, State::Start);
    setStateTransition(State::Start, InputType::Whitespace, State::Start);
    setStateTransition(State::Start, InputType::Equals, State::Equals);
    setStateTransition(State::Start, InputType::Less, State::Less);
    setStateTransition(State::Start, InputType::Greater, State::Greater);
    setStateTransition(State::Start, InputType::Exclamation, State::Exclamation);
    setStateTransition(State::Start, InputType::Comma, State::Delimiter);
    setStateTransition(State::Start, InputType::Semi, State::Delimiter);
    setStateTransition(State::Start, InputType::LeftBrace, State::LeftBrace);
    setStateTransition(State::Start, InputType::RightBrace, State::RightBrace);
    setStateTransition(State::Start, InputType::LeftParen, State::Parentheses);
    setStateTransition(State::Start, InputType::RightParen, State::Parentheses);
    setStateTransition(State::Start, InputType::EndFile, State::EndFile);
    setStateTransition(State::Start, InputType::Other, State::Error);
    
    // Digit State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::Digit, static_cast<InputType>(input), State::DigitFinal);
    }
    setStateTransition(State::Digit, InputType::Digit, State::Digit);

    // Identifier State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::Identifier, static_cast<InputType>(input), State::IdentifierFinal);
    }
    setStateTransition(State::Identifier, InputType::Letter, State::Identifier);
    setStateTransition(State::Identifier, InputType::Digit, State::Identifier);

    // Slash State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::Slash, static_cast<InputType>(input), State::Division);
    }
    setStateTransition(State::Slash, InputType::Asterisk, State::MultiLine);
    setStateTransition(State::Slash, InputType::Slash, State::SingleLine);

    // Multi-line Comment State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::MultiLine, static_cast<InputType>(input), State::MultiLine);
    }
    setStateTransition(State::MultiLine, InputType::Asterisk, State::EndMulti);

    // End Multi-line Comment State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::EndMulti, static_cast<InputType>(input), State::MultiLine);
    }
    setStateTransition(State::EndMulti, InputType::Slash, State::Start);

    // Single Line Comment State
    for (int input = 0; input < static_cast<int>(InputType::COUNT); input++) {
        setStateTransition(State::SingleLine, static_cast<InputType>(input), State::SingleLine);
    }
    setStateTransition(State::EndMulti, InputType::Slash, State::Start);

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