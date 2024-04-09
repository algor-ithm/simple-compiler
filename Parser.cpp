#include "Parser.h"

Parser::Parser() {
    configOpTable();
}

// Initialize operator precedence table 
void Parser::configOpTable() {
    for (int i = 0; i < OP_COUNT; i++) {
        for (int j = 0; j < OP_COUNT; j++) {
            opPrecedence[i][j] = '?';
        }
    }
    // semicolon
    opPrecedence[OP_SEMI][OP_ASSIGN] = '<';
    opPrecedence[OP_SEMI][OP_LBRACE] = '<';
    // assignment
    opPrecedence[OP_ASSIGN][OP_SEMI] = '>';
    opPrecedence[OP_ASSIGN][OP_ADD] = '<';
    opPrecedence[OP_ASSIGN][OP_SUB] = '<';
    opPrecedence[OP_ASSIGN][OP_LPAREN] = '<';
    opPrecedence[OP_ASSIGN][OP_MUL] = '<';
    opPrecedence[OP_ASSIGN][OP_DIV] = '<';
    //opPrecedence[OP_ASSIGN][OP_RBRACE] = '>';
    opPrecedence[OP_ASSIGN][OP_COMMA] = '>';
    // addition
    opPrecedence[OP_ADD][OP_SEMI] = '>';
    opPrecedence[OP_ADD][OP_ADD] = '>';
    opPrecedence[OP_ADD][OP_SUB] = '>';
    opPrecedence[OP_ADD][OP_LPAREN] = '<';
    opPrecedence[OP_ADD][OP_RPAREN] = '>';
    opPrecedence[OP_ADD][OP_MUL] = '<';
    opPrecedence[OP_ADD][OP_DIV] = '<';
    opPrecedence[OP_ADD][OP_THEN] = '>';
    opPrecedence[OP_ADD][OP_DO] = '>';
    opPrecedence[OP_ADD][OP_EQ] = '>';
    opPrecedence[OP_ADD][OP_NE] = '>';
    opPrecedence[OP_ADD][OP_GT] = '>';
    opPrecedence[OP_ADD][OP_LT] = '>';
    opPrecedence[OP_ADD][OP_GTE] = '>';
    opPrecedence[OP_ADD][OP_LTE] = '>';
    //opPrecedence[OP_ADD][OP_RBRACE] = '>';
    //opPrecedence[OP_ADD][OP_COMMA] = '>';
    // subtraction
    opPrecedence[OP_SUB][OP_SEMI] = '>';
    opPrecedence[OP_SUB][OP_ADD] = '>';
    opPrecedence[OP_SUB][OP_SUB] = '>';
    opPrecedence[OP_SUB][OP_LBRACE] = '<';
    opPrecedence[OP_SUB][OP_RBRACE] = '>';
    opPrecedence[OP_SUB][OP_MUL] = '<';
    opPrecedence[OP_SUB][OP_DIV] = '<';
    opPrecedence[OP_SUB][OP_THEN] = '>';
    opPrecedence[OP_SUB][OP_DO] = '>';
    opPrecedence[OP_SUB][OP_EQ] = '>';
    opPrecedence[OP_SUB][OP_NE] = '>';
    opPrecedence[OP_SUB][OP_GT] = '>';
    opPrecedence[OP_SUB][OP_LT] = '>';
    opPrecedence[OP_SUB][OP_GTE] = '>';
    opPrecedence[OP_SUB][OP_LTE] = '>';
    //opPrecedence[OP_SUB][OP_RBRACE] = '>';
    //opPrecedence[OP_SUB][OP_COMMA] = '>';
    // left parentheses
    opPrecedence[OP_LPAREN][OP_ADD] = '<';
    opPrecedence[OP_LPAREN][OP_SUB] = '<';
    opPrecedence[OP_LPAREN][OP_LPAREN] = '<';
    opPrecedence[OP_LPAREN][OP_RPAREN] = '=';
    opPrecedence[OP_LPAREN][OP_MUL] = '<';
    opPrecedence[OP_LPAREN][OP_DIV] = '<';
    // right parentheses
    opPrecedence[OP_RPAREN][OP_SEMI] = '>';
    opPrecedence[OP_RPAREN][OP_ADD] = '>';
    opPrecedence[OP_RPAREN][OP_SUB] = '>';
    opPrecedence[OP_RPAREN][OP_RPAREN] = '>';
    opPrecedence[OP_RPAREN][OP_MUL] = '>';
    opPrecedence[OP_RPAREN][OP_DIV] = '>';
    //opPrecedence[OP_ASSIGN][OP_COMMA] = '>';
    // multiplication
    opPrecedence[OP_MUL][OP_SEMI] = '>';
    opPrecedence[OP_MUL][OP_ADD] = '>';
    opPrecedence[OP_MUL][OP_SUB] = '>';
    opPrecedence[OP_MUL][OP_LPAREN] = '<';
    opPrecedence[OP_MUL][OP_RPAREN] = '>';
    opPrecedence[OP_MUL][OP_MUL] = '>';
    opPrecedence[OP_MUL][OP_DIV] = '>';
    opPrecedence[OP_MUL][OP_THEN] = '>';
    opPrecedence[OP_MUL][OP_DO] = '>';
    opPrecedence[OP_MUL][OP_EQ] = '>';
    opPrecedence[OP_MUL][OP_NE] = '>';
    opPrecedence[OP_MUL][OP_GT] = '>';
    opPrecedence[OP_MUL][OP_LT] = '>';
    opPrecedence[OP_MUL][OP_GTE] = '>';
    opPrecedence[OP_MUL][OP_LTE] = '>';
    //opPrecedence[OP_MUL][OP_RBRACE] = '>';
    //opPrecedence[OP_ASSIGN][OP_COMMA] = '>';
    // divide
    opPrecedence[OP_DIV][OP_SEMI] = '>';
    opPrecedence[OP_DIV][OP_ADD] = '>';
    opPrecedence[OP_DIV][OP_SUB] = '>';
    opPrecedence[OP_DIV][OP_LPAREN] = '<';
    opPrecedence[OP_DIV][OP_RPAREN] = '>';
    opPrecedence[OP_DIV][OP_MUL] = '>';
    opPrecedence[OP_DIV][OP_DIV] = '>';
    opPrecedence[OP_DIV][OP_THEN] = '>';
    opPrecedence[OP_DIV][OP_DO] = '>';
    opPrecedence[OP_DIV][OP_EQ] = '>';
    opPrecedence[OP_DIV][OP_NE] = '>';
    opPrecedence[OP_DIV][OP_GT] = '>';
    opPrecedence[OP_DIV][OP_LT] = '>';
    opPrecedence[OP_DIV][OP_GTE] = '>';
    opPrecedence[OP_DIV][OP_LTE] = '>';
    //opPrecedence[OP_DIV][OP_RBRACE] = '>';
    //opPrecedence[OP_ASSIGN][OP_COMMA] = '>';
    // if
    opPrecedence[OP_IF][OP_ADD] = '<';
    opPrecedence[OP_IF][OP_SUB] = '<';
    opPrecedence[OP_IF][OP_LPAREN] = '<';
    opPrecedence[OP_IF][OP_MUL] = '<';
    opPrecedence[OP_IF][OP_DIV] = '<';
    opPrecedence[OP_IF][OP_THEN] = '=';
    opPrecedence[OP_IF][OP_ODD] = '<';
    opPrecedence[OP_IF][OP_EQ] = '<';
    opPrecedence[OP_IF][OP_NE] = '<';
    opPrecedence[OP_IF][OP_GT] = '<';
    opPrecedence[OP_IF][OP_LT] = '<';
    opPrecedence[OP_IF][OP_GTE] = '<';
    opPrecedence[OP_IF][OP_LTE] = '<';
    // then
    opPrecedence[OP_THEN][OP_ASSIGN] = '<';
    opPrecedence[OP_THEN][OP_IF] = '<';
    opPrecedence[OP_THEN][OP_WHILE] = '<';
    opPrecedence[OP_THEN][OP_LBRACE] = '<';
    opPrecedence[OP_THEN][OP_CALL] = '<';
    opPrecedence[OP_THEN][OP_ELSE] = '=';
    // while (not done)
    opPrecedence[OP_WHILE][OP_ADD] = '<';
    opPrecedence[OP_WHILE][OP_SUB] = '<';
    opPrecedence[OP_WHILE][OP_LPAREN] = '<';
    opPrecedence[OP_WHILE][OP_MUL] = '<';
    opPrecedence[OP_WHILE][OP_DIV] = '<';
    opPrecedence[OP_WHILE][OP_DO] = '=';
    opPrecedence[OP_WHILE][OP_ODD] = '<';
    opPrecedence[OP_WHILE][OP_EQ] = '<';
    opPrecedence[OP_WHILE][OP_NE] = '<';
    opPrecedence[OP_WHILE][OP_GT] = '<';
    opPrecedence[OP_WHILE][OP_LT] = '<';
    opPrecedence[OP_WHILE][OP_GTE] = '<';
    opPrecedence[OP_WHILE][OP_LTE] = '<';
    // do
    opPrecedence[OP_DO][OP_ASSIGN] = '<';
    opPrecedence[OP_DO][OP_IF] = '<';
    opPrecedence[OP_DO][OP_WHILE] = '<';
    opPrecedence[OP_DO][OP_LBRACE] = '<';
    opPrecedence[OP_DO][OP_CALL] = '<';
    // odd
    opPrecedence[OP_ODD][OP_ADD] = '<';
    opPrecedence[OP_ODD][OP_SUB] = '<';
    opPrecedence[OP_ODD][OP_LPAREN] = '<';
    opPrecedence[OP_ODD][OP_MUL] = '<';
    opPrecedence[OP_ODD][OP_DIV] = '<';
    opPrecedence[OP_ODD][OP_THEN] = '>';
    opPrecedence[OP_ODD][OP_DO] = '>';
    // equals 
    opPrecedence[OP_EQ][OP_ADD] = '<';
    opPrecedence[OP_EQ][OP_SUB] = '<';
    opPrecedence[OP_EQ][OP_LPAREN] = '<';
    opPrecedence[OP_EQ][OP_MUL] = '<';
    opPrecedence[OP_EQ][OP_DIV] = '<';
    opPrecedence[OP_EQ][OP_THEN] = '>';
    opPrecedence[OP_EQ][OP_DO] = '>';
    // not equals
    opPrecedence[OP_NE][OP_ADD] = '<';
    opPrecedence[OP_NE][OP_SUB] = '<';
    opPrecedence[OP_NE][OP_LPAREN] = '<';
    opPrecedence[OP_NE][OP_MUL] = '<';
    opPrecedence[OP_NE][OP_DIV] = '<';
    opPrecedence[OP_NE][OP_THEN] = '>';
    opPrecedence[OP_NE][OP_DO] = '>';
    // greater than
    opPrecedence[OP_GT][OP_ADD] = '<';
    opPrecedence[OP_GT][OP_SUB] = '<';
    opPrecedence[OP_GT][OP_LPAREN] = '<';
    opPrecedence[OP_GT][OP_MUL] = '<';
    opPrecedence[OP_GT][OP_DIV] = '<';
    opPrecedence[OP_GT][OP_THEN] = '>';
    opPrecedence[OP_GT][OP_DO] = '>';
    // less than
    opPrecedence[OP_LT][OP_ADD] = '<';
    opPrecedence[OP_LT][OP_SUB] = '<';
    opPrecedence[OP_LT][OP_LPAREN] = '<';
    opPrecedence[OP_LT][OP_MUL] = '<';
    opPrecedence[OP_LT][OP_DIV] = '<';
    opPrecedence[OP_LT][OP_THEN] = '>';
    opPrecedence[OP_LT][OP_DO] = '>';
    // greather than or equals
    opPrecedence[OP_GTE][OP_ADD] = '<';
    opPrecedence[OP_GTE][OP_SUB] = '<';
    opPrecedence[OP_GTE][OP_LPAREN] = '<';
    opPrecedence[OP_GTE][OP_MUL] = '<';
    opPrecedence[OP_GTE][OP_DIV] = '<';
    opPrecedence[OP_GTE][OP_THEN] = '>';
    opPrecedence[OP_GTE][OP_DO] = '>';
    // less than or equals
    opPrecedence[OP_LTE][OP_ADD] = '<';
    opPrecedence[OP_LTE][OP_SUB] = '<';
    opPrecedence[OP_LTE][OP_LPAREN] = '<';
    opPrecedence[OP_LTE][OP_MUL] = '<';
    opPrecedence[OP_LTE][OP_DIV] = '<';
    opPrecedence[OP_LTE][OP_THEN] = '>';
    opPrecedence[OP_LTE][OP_DO] = '>';
    // left brace
    opPrecedence[OP_LBRACE][OP_ASSIGN] = '<';
    opPrecedence[OP_LBRACE][OP_IF] = '<';
    opPrecedence[OP_LBRACE][OP_WHILE] = '<';
    opPrecedence[OP_LBRACE][OP_LBRACE] = '<';
    opPrecedence[OP_LBRACE][OP_RBRACE] = '=';
    opPrecedence[OP_LBRACE][OP_CALL] = '<';
    // else
    opPrecedence[OP_ELSE][OP_ASSIGN] = '<';
    opPrecedence[OP_ELSE][OP_IF] = '<';
    opPrecedence[OP_ELSE][OP_WHILE] = '<';
    opPrecedence[OP_ELSE][OP_LBRACE] = '<';
}

ParserOps Parser::getNextStackOp() {
    Token topToken;
    ParserOps topOp;    
    for(int i = pStackSize - 1; i >= 0; i--){
        topToken = parseStack[i];
        topOp = getTokenOpType(topToken);
        if (topOp != NON_OP) break;
    }
    cout << "Top op to compare " << topToken.lexeme << endl;
    return topOp;
}

// get precedence relation from table 
char Parser::getRelation(ParserOps op1, ParserOps op2) {
    if (op1 < 0 || op1 >= OP_COUNT || op2 < 0 || op2 >= OP_COUNT) {
       throw out_of_range("One or more of the operators is out of range.");
    } 
    return opPrecedence[op1][op2];  
}

string Parser::generateTemp() {
    return "T" + to_string(tempCount++);
    if (tempCount == 5) tempCount = 1; 
}

string Parser::generateLabel() {
    return "L" + to_string(labelCount++);
}

string Parser::generateWhileLabel(){
    return "W" + to_string(whileCount++);
}

bool Parser::isStructural(Token& token){
     return (token.type == "CLASS" || token.type == "CONST" || token.type == "VAR" 
        || token.type == "PROCEDURE" || token.type == "GET" || token.type == "PUT");
}

ParserOps Parser::getTokenOpType(const Token& token){
    if(token.lexeme == ";") return OP_SEMI;
    if(token.lexeme == "=") return OP_ASSIGN;
    if(token.lexeme == "+") return OP_ADD;
    if(token.lexeme == "-") return OP_SUB;
    if(token.lexeme == "(") return OP_LPAREN;
    if(token.lexeme == ")") return OP_RPAREN;
    if(token.lexeme == "*") return OP_MUL;
    if(token.lexeme == "/") return OP_DIV;
    if(token.lexeme == "IF") return OP_IF;
    if(token.lexeme == "THEN") return OP_THEN;
    if(token.lexeme == "WHILE") return OP_WHILE;
    if(token.lexeme == "DO") return OP_DO;
    if(token.lexeme == "ODD") return OP_ODD;
    if(token.lexeme == "==") return OP_EQ;
    if(token.lexeme == "!=") return OP_NE;
    if(token.lexeme == ">") return OP_GT;
    if(token.lexeme == "<") return OP_LT;
    if(token.lexeme == ">=") return OP_GTE;
    if(token.lexeme == "<=") return OP_LTE;
    if(token.lexeme == "{") return OP_LBRACE;
    if(token.lexeme == "}") return OP_RBRACE;
    if(token.lexeme == "CALL") return OP_CALL;
    if(token.lexeme == ",") return OP_COMMA;
    if(token.lexeme == "ELSE") return OP_ELSE;
    return NON_OP;
}

void Parser::performReduction() {
    cout << "Reduction function called" << endl;
    if (tryReduceArithmetic()) {
        cout << "Reducing arithmetic opeartion" << endl;
    } else if (tryReduceBooleanExp()){
        cout << "Reducing boolean operation" << endl;
    } else if (tryReduceAssignment()){
        cout << "Reducing assignment opeartion" << endl;
    }
}

bool Parser::tryReduceArithmetic() {
    Token rOperand = parseStack[pStackSize - 1];
    Token op = parseStack[pStackSize - 2];
    Token lOperand = parseStack[pStackSize - 3];
    if ((lOperand.type == "IDENTIFIER" || lOperand.type == "NUMERIC_LITERAL") &&
        (rOperand.type == "IDENTIFIER" || rOperand.type == "NUMERIC_LITERAL") &&
        (op.lexeme == "+" || op.lexeme == "-" || op.lexeme == "*" || op.lexeme == "/")) {
        string temp = generateTemp();
        Quad quad(op.lexeme, lOperand.lexeme, rOperand.lexeme, temp);
        quads[quadCount++] = quad;
        cout << "Created quad: " << quad.op << "," << quad.leftArg << "," << quad.rightArg << "," << quad.result << endl;
        Token reduced(temp, "IDENTIFIER");
        pStackSize -= 3;
        parseStack[pStackSize++] = reduced;
        return true;
    }  
    return false;
}

bool Parser::tryReduceBooleanExp() {
    Token rOperand = parseStack[pStackSize - 1];
    Token op = parseStack[pStackSize - 2];
    Token lOperand = parseStack[pStackSize - 3];
    if ((lOperand.type == "IDENTIFIER" || lOperand.type == "NUMERIC_LITERAL") &&
        (rOperand.type == "IDENTIFIER" || rOperand.type == "NUMERIC_LITERAL") &&
        (op.lexeme == "==" || op.lexeme == "!=" || op.lexeme == ">" || 
        op.lexeme == "<" || op.lexeme == ">=" || op.lexeme == "<=")){

            Quad quad(op.lexeme, lOperand.lexeme, rOperand.lexeme, "?");
        
        quads[quadCount++] = quad;
        cout << "Created quad: " << quad.op << "," << quad.leftArg << "," << quad.rightArg << "," << quad.result << endl;
        pStackSize -= 3;
        return true;
    } 
    return false;
}

bool Parser::tryReduceAssignment() {
        Token rOperand = parseStack[pStackSize - 1];
        Token op = parseStack[pStackSize - 2];
        Token lOperand = parseStack[pStackSize - 3];
        if(lOperand.type == "IDENTIFIER" && (rOperand.type == "IDENTIFIER" || rOperand.type == "NUMERIC_LITERAL") 
            && op.lexeme == "=") {

            Quad quad(op.lexeme, lOperand.lexeme, rOperand.lexeme, "?");
            quads[quadCount++] = quad;
            cout << "Created quad: " << quad.op << "," << quad.leftArg << "," << quad.rightArg << "," << quad.result << endl;
            pStackSize -= 3; 
            return true;   
        }
    return false;
}

void Parser::handleClosingBrace() {
        Token rightBrace = parseStack[pStackSize - 1];
        Token leftBrace = parseStack[pStackSize - 2];
        if (leftBrace.lexeme == "{" && rightBrace.lexeme == "}") {
            pStackSize -= 2;
        } else {
            cout << "ERROR: Missing a matching '{' for '}'" << endl;
        }
}

void Parser::handleClosingParen(){
    Token popToken;
    Token id;
    bool found = false;
    Token rightParen = parseStack[pStackSize - 1];
    for (int i = pStackSize - 1; i >= 0; i--){
        popToken = parseStack[i];
        if (popToken.lexeme == "(") {
            found = true;
            break;
        } else {
            id = popToken;
        }
    }
    if (found) {
        pStackSize -= 3;
        parseStack[pStackSize++] = id;   
    } else {
        cout << "ERROR: Missing a matching '(' and ')'" << endl;
    }
}

void Parser::handleIf() {
    Quad quad("IF", "?", "?", "?");
    quads[quadCount++] = quad;
}

void Parser::handleThen() {
    Quad lastQuad = quads[quadCount - 1];
    string label = generateLabel();
    string jump;
    if (lastQuad.op == ">") jump = "LE";
    if (lastQuad.op == ">=") jump = "L";
    if (lastQuad.op == "<") jump = "GE";
    if (lastQuad.op == "<=") jump = "G";
    if (lastQuad.op == "==") jump = "NE";
    if (lastQuad.op == "!=") jump = "E";
    Quad newQuad("THEN", label, jump, "?");
    quads[quadCount++] = newQuad;
    // put label on fix up stack
    fixUpStack[fStackSize++] = label;
    for (int i = fStackSize - 1; i >= 0; i--){
        cout << fixUpStack[i] << endl;
    }
}

void Parser::handleElse() {
    string elseLabel = generateLabel();
    string thenLabel = fixUpStack[fStackSize - 1];
    Quad elseQuad("ELSE", elseLabel, "JMP" , "?");
    quads[quadCount++] = elseQuad;
    elseStack[eStackSize++] = elseLabel;
    Quad labelQuad(thenLabel, "JLABEL", "?", "?");
    quads[quadCount++] = labelQuad;
    fStackSize--;
}

void Parser::popIfThen() {
    string label;
    Token ifToken = parseStack[pStackSize - 2];
    if (ifToken.lexeme == "IF") {
        pStackSize -= 2;
        label = fixUpStack[fStackSize - 1];
        fStackSize--;
        Quad quad(label, "JLABEL", "?", "?");
        quads[quadCount++] = quad;
    } else {
         cout << "ERROR: Missing IF for THEN" << endl;
    }
}

void Parser::popIfThenElse() {
    string label;
    Token thenToken = parseStack[pStackSize - 2];
    Token ifToken = parseStack[pStackSize - 3];
    if (ifToken.lexeme == "IF" && thenToken.lexeme == "THEN") {
        pStackSize -= 3;
        label = elseStack[eStackSize - 1];
        eStackSize--;
        Quad quad(label, "JLABEL", "?", "?");
        quads[quadCount++] = quad;
    } else {
        cout << "ERROR: Missing matching IF THEN for ELSE" << endl;
    }
}

void Parser::handleWhile() {
    string whileLabel = generateWhileLabel();
    Quad quad("WHILE", whileLabel, "?", "?");
    quads[quadCount++] = quad;
    whileStack[wStackSize++] = whileLabel;
    for (int i = wStackSize - 1; i >= 0; i--){
        //cout << whileStack[i] << endl;
    }
}

void Parser::handleDo() {
    Quad lastQuad = quads[quadCount - 1];
    string label = generateLabel();
    string jump;
    if (lastQuad.op == ">") jump = "LE";
    if (lastQuad.op == ">=") jump = "L";
    if (lastQuad.op == "<") jump = "GE";
    if (lastQuad.op == "<=") jump = "G";
    if (lastQuad.op == "==") jump = "NE";
    if (lastQuad.op == "!=") jump = "E";
    Quad newQuad("DO", label, jump, "?");
    quads[quadCount++] = newQuad;
    // put label on fix up stack
    fixUpStack[fStackSize++] = label;
    for (int i = fStackSize - 1; i >= 0; i--){
        cout << fixUpStack[i] << endl;
    }
}

void Parser::popWhileDo() {
        string label, whileLabel;
        Token whileToken = parseStack[pStackSize - 2];
        if (whileToken.lexeme == "WHILE") {
            pStackSize -= 2;
            whileLabel = whileStack[wStackSize - 1];
            label = fixUpStack[fStackSize - 1];
            wStackSize--;
            fStackSize--;
            Quad whileQuad ( whileLabel, "WLABEL", "?", "?");
            Quad labelQuad (label, "JLABEL", "?", "?");
            quads[quadCount++] = whileQuad;
            quads[quadCount++] = labelQuad;
        } else {
            cout << "ERROR: Missing WHILE" << endl;
        }
}

void Parser::handleIO(Token currentToken, Token nextToken) {
    if (nextToken.type == "IDENTIFIER") {
    Quad newQuad(currentToken.lexeme, nextToken.lexeme, "?", "?");
    quads[quadCount++] = newQuad;
    } else {
        cout << "ERROR: Cannot perform IO for " << nextToken.lexeme << "of type " << nextToken.type << endl;
    }
}

void Parser::printStack() {
    cout << "\n";
    for (int i = pStackSize - 1; i >= 0; i--) {
    cout << parseStack[i].lexeme << " " << parseStack[i].type << endl;
    }
}

void Parser::printQuads() {
    cout << "\n";
    for(int i = 0; i < quadCount; i++){
        cout << quads[i].op << ", " << quads[i].leftArg << ", " << quads[i].rightArg << ", " << quads[i].result << endl;
    }
}

// public functions
const Quad* Parser::getQuads(){
    return quads;
}

int Parser::getQuadCount() {
    return quadCount;
}

void Parser::parse(const Token* tokens, int tokenCount) {
    Token currentToken, ioToken;
    ParserOps currentOp, topOp;
    char relation;
    bool reductionNeeded;
    
    // Initialize the parser 
    pStackSize = 0;
    parseStack[pStackSize++] = Token(";", "DELIMITER");

    for (int i = 0; i < tokenCount; i++){
        currentToken = tokens[i];
        currentOp = getTokenOpType(currentToken);

        // if eof done parsing return from function
        if (currentToken.lexeme == "EndFile") {
            cout << "\nDone parsing!" << endl;
            printStack(); printQuads();
            return;
        }

        // check structural tokens
        if (isStructural(currentToken)){
            if(currentToken.type == "VAR" || currentToken.type == "CONST"){
                cout << "Skipped: " << currentToken.lexeme << endl;
                // Skip to end of decleration
                while (i < tokenCount && tokens[i].lexeme != ";") {
                    i++;
                    cout << "Skipped: " << tokens[i].lexeme << endl;
                }
            }
            if (currentToken.type == "CLASS") {
                cout << "Skipped: " << currentToken.lexeme << endl;
                i++;
                cout << "Skipped: " << tokens[i].lexeme << endl;
            }
            // later: add ability to handle procedure calls for A option
            if (currentToken.type == "PROCEDURE") {
                i += 3;
                //cout << "Skipped: " << tokens[i].lexeme << endl;
                
            } 
            if (currentToken.type == "GET" || currentToken.type == "PUT") {
                cout << "Skipped: " << currentToken.lexeme << endl;
                i++; // Skip keyword
                cout << "Skipped: " << tokens[i].lexeme << endl;
                ioToken = tokens[i]; // get identifier 
                handleIO(currentToken, ioToken);
                i++; // Skip semi 
                cout << "Skipped: " << tokens[i].lexeme << endl;
            }
            continue;
        }

        // if non-terminal shift directly onto stack
        if (currentOp == NON_OP) {
            parseStack[pStackSize++] = currentToken;
            cout << "Shifted " << currentToken.lexeme << " onto the stack (NON-OP)" << endl;
            continue;
        }
        
        // determine relation and appropriate action
        topOp = getNextStackOp();
        cout << "CurrentOp to compare " << currentToken.lexeme << endl;
        relation = getRelation(topOp, currentOp); 
        cout << "Relation: " << relation << endl;
        if (relation == '<' || relation == '=') {
            parseStack[pStackSize++] = currentToken;
            cout << "Shifted " << currentToken.lexeme << " onto the stack" << endl;
        }  else if (relation == '>'){
            reductionNeeded = true;
        } else {
            // add error handling 
            cout << "ERROR: You fucked up. Stupid Compiler" << endl;
        }
        
        // perform reductions until no more needed
        int count = 0;
        while (reductionNeeded && count < 5) {
            printStack(); cout << endl;
            cout << "Reduction called:" << endl;
            performReduction();
            reductionNeeded = false;
            topOp = getNextStackOp();
            cout << "CurrentOp to compare " << currentToken.lexeme << endl;
            relation = getRelation(topOp, currentOp);
            if (relation == '>') {
                reductionNeeded = true;
            } else if (relation == '=' || relation == '<') {
                parseStack[pStackSize++] = currentToken;
            }
            count++;
        }

        if (currentToken.lexeme == ")") {
            cout << "Dealing with paren" << endl;
            handleClosingParen();
        }

        if (currentToken.lexeme == "}") {
            cout << "Reducing braces" << endl;
            cout << endl; printStack(); cout << endl;
            handleClosingBrace();
        }

        if (currentToken.lexeme == "IF") {
            cout << "Handling IF" << endl;
            handleIf();
        }

        if (currentToken.lexeme == "THEN") {
            cout << "Handling THEN" << endl;
            handleThen();
        }

        if (currentToken.lexeme == "ELSE") {
            cout << "Handling ELSE" << endl;
            handleElse();
        }

        if ((currentToken.lexeme == "}" || currentToken.lexeme == ";") 
            && parseStack[pStackSize - 1].lexeme == "THEN" && tokens[i + 1].lexeme != "ELSE") {
            cout << "Popping IF THEN off stack." << endl;
            popIfThen();
        } 

        if ((currentToken.lexeme == "}" || currentToken.lexeme == ";") 
            && parseStack[pStackSize - 1].lexeme == "ELSE") {
            cout << "Popping IF THEN ELSE off stack." << endl;
            popIfThenElse();
        }   

        if (currentToken.lexeme == "WHILE") {
            cout << "Handling WHILE" << endl;
            handleWhile();
        }

        if (currentToken.lexeme == "DO") {
            cout << "Handling DO" << endl;
            handleDo();
        }

        if ((currentToken.lexeme == "}" || currentToken.lexeme == ";") 
            && parseStack[pStackSize - 1].lexeme == "DO") {
            cout << "Popping off WHILE DO" << endl;
            popWhileDo();
            printStack();
        }
    }
}