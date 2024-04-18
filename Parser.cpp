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
    // subtraction
    opPrecedence[OP_SUB][OP_SEMI] = '>';
    opPrecedence[OP_SUB][OP_ADD] = '>';
    opPrecedence[OP_SUB][OP_SUB] = '>';
    opPrecedence[OP_SUB][OP_LPAREN] = '<';
    opPrecedence[OP_SUB][OP_RPAREN] = '>';
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
    cout << "Top op to compare: " << topToken.lexeme << endl;
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
}

string Parser::generateLabel() {
    return "L" + to_string(labelCount++);
}

string Parser::generateWhileLabel(){
    return "W" + to_string(whileCount++);
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
    bool reduced = tryReduceArithmetic() || tryReduceBooleanExp() || tryReduceAssignment();
    if (!reduced) {
        cerr << "ERROR: Failed to apply operation reductions" << endl;
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
            cerr << "ERROR: Missing a matching '{' for '}'" << endl;
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
        cerr << "ERROR: Missing a matching '(' and ')'" << endl;
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
    fixUpStack[fStackSize++] = label;
}

void Parser::handleElse() {
    string elseLabel = generateLabel();
    string thenLabel = fixUpStack[fStackSize - 1];
    Quad elseQuad("ELSE", elseLabel, "JMP" , "?");
    quads[quadCount++] = elseQuad;
    elseStack[eStackSize++] = elseLabel;
    Quad labelQuad("JLABEL", thenLabel, "?", "?");
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
        Quad quad("JLABEL", label, "?", "?");
        quads[quadCount++] = quad;
    } else {
        cerr << "ERROR: Missing IF for THEN" << endl;
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
        Quad quad("JLABEL", label, "?", "?");
        quads[quadCount++] = quad;
    } else {
        cerr << "ERROR: Missing matching IF THEN for ELSE" << endl;
    }
}

void Parser::handleWhile() {
    string whileLabel = generateWhileLabel();
    Quad quad("WHILE", whileLabel, "?", "?");
    quads[quadCount++] = quad;
    whileStack[wStackSize++] = whileLabel;
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
    fixUpStack[fStackSize++] = label;
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
            Quad whileQuad ( "WLABEL", whileLabel, "?", "?");
            Quad labelQuad ("JLABEL", label, "?", "?");
            quads[quadCount++] = whileQuad;
            quads[quadCount++] = labelQuad;
        } else {
            cerr << "ERROR: Missing WHILE" << endl;
        }
}

void Parser::handleIO(Token currentToken, Token nextToken) {
    if (nextToken.type == "IDENTIFIER") {
    Quad newQuad(currentToken.lexeme, nextToken.lexeme, "?", "?");
    quads[quadCount++] = newQuad;
    } else {
        cerr << "ERROR: Cannot perform IO for " + nextToken.lexeme + "of type " + nextToken.type << endl;
    }
}

void Parser::handleProcedureStart(string procName) {
    Quad quad("PROC", procName, "?", "?");
    quads[quadCount++] = quad;
}

void Parser::handleProcedureEnd(string procName) {
    if (isRecursive) {
        handleRecursion();
        isRecursive = false;
    }
    Quad retQuad("RETURN", "?", "?" ,"?");
    quads[quadCount++] = retQuad;
    Quad procEndQuad ("PROCEND", procName, "?", "?");
    quads[quadCount++] = procEndQuad;  
}

void Parser::handleCall(string procName) {
    Quad quad("CALL", procName, "?", "?");
    quads[quadCount++] = quad;
}

void Parser::handleReturn() {
    Quad quad("RETURN", "RetHome", "?", "?");
    quads[quadCount++] = quad;
}

void Parser::handleRecursion(){
    if (!isRecursive) return;
    int i = 0;
    while (i < quadCount) {
        if (quads[i].op == "THEN") {
            quads[i].leftArg = "RetHome";
            if (quads[i].rightArg == "NE") quads[i].rightArg = "E";
            else if (quads[i].rightArg == "E") quads[i].rightArg = "NE";
            else if (quads[i].rightArg == "G") quads[i].rightArg = "LE";
            else if (quads[i].rightArg == "GE") quads[i].rightArg = "L";
            else if (quads[i].rightArg == "L") quads[i].rightArg = "GE";
            else if (quads[i].rightArg == "LE") quads[i].rightArg = "G";
        } 
        if (quads[i].op == "ELSE" || quads[i].op == "JLABEL" || quads[i].op == "RETURN") {
            for (int k = i; k < quadCount - 1; k++){
                quads[k] = quads[k + 1];
            }
            quadCount--;
        } else {
            i++;
        }     
    }
    Quad quad("RetHome", "?", "?", "?");
    quads[quadCount++] = quad; 
}

void Parser::handleStart() {
    Quad quad("START", "?", "?", "?");
    quads[quadCount++] = quad;
}

bool Parser::isExecutable(Token t) { //, bool inDec) {
    const unordered_set<string> executableTokens = {
    "IF", "THEN", "ELSE", "WHILE", "DO", "CALL", "GET", "RETURN"
   "IDENTIFIER", "NUMERIC_LITERAL", "ASSIGN", "ADDOP", "SUBOP", "MULOP", "DIVOP", "RELOP"};
    return executableTokens.find(t.lexeme) != executableTokens.end();
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
    bool inProc = false;
    bool inDeclaration = false;
    bool mainDetected = false;
    string procName, callProc;
    int scopeDepth = 0;
    
    // Initialize the parser 
    pStackSize = 0;
    parseStack[pStackSize++] = Token(";", "DELIMITER");

    for (int i = 0; i < tokenCount; i++){
        currentToken = tokens[i];
        currentOp = getTokenOpType(currentToken);
        cout << "Reading token " << currentToken.lexeme << endl;

        // if eof done parsing return from function
        if (currentToken.lexeme == "EndFile") {
            cout << "\nDone parsing!" << endl;
            printStack(); printQuads();
            return;
        }

        // check structural tokens skip or handle
        if (currentToken.type == "CLASS") {
            i++;
            continue;
        }
        if(currentToken.type == "VAR" || currentToken.type == "CONST"){
            while (i < tokenCount && tokens[i].lexeme != ";") 
                i++;
            continue;
        }
        if (currentToken.type == "PROCEDURE") {
            i++;
            procName = tokens[i].lexeme;
            cout << "Processing start procedure: " << procName << endl;
            handleProcedureStart(procName);
            inProc = true;
            i += 2; 
            continue;
        } 
        if (!inProc && !mainDetected && isExecutable(currentToken)) {
            handleStart();
            mainDetected = true;
        }
        if (currentToken.type == "GET" || currentToken.type == "PUT") {
            ioToken = tokens[++i];
            handleIO(currentToken, ioToken);
            continue;
        } 
        if (currentToken.type == "CALL") {
            cout << "Handling Call" << endl;
            callProc = tokens[++i].lexeme;
            handleCall(callProc);
            if (inProc && callProc == procName) 
                isRecursive = true;
            i += 2;
            continue;
        }
        if (currentToken.lexeme == "RETURN") {
            handleReturn();
            continue;
        }
        // check for non terminal shift onto stack
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
        } 
        // perform reductions until no more needed
        while (reductionNeeded) {
            printStack(); cout << endl;
            performReduction();
            reductionNeeded = false;
            topOp = getNextStackOp();
            cout << "CurrentOp to compare " << currentToken.lexeme << endl;
            relation = getRelation(topOp, currentOp);
            if (relation == '>') {
                reductionNeeded = true;
            } else if (relation == '=' || relation == '<') {
                parseStack[pStackSize++] = currentToken;
                cout << "Shifted " << currentToken.lexeme << " onto the stack" << endl;
            }
        }
        if (currentToken.lexeme == ")") 
            handleClosingParen();
        if (currentToken.lexeme == "{") 
            scopeDepth++;
        if (currentToken.lexeme == "}") {
            handleClosingBrace();
            scopeDepth--;  
        }
        if (currentToken.lexeme == "IF") 
            handleIf();
        if (currentToken.lexeme == "THEN") 
            handleThen();
        if (currentToken.lexeme == "ELSE") 
            handleElse();
        if (currentToken.lexeme == "WHILE") 
            handleWhile();
        if (currentToken.lexeme == "DO") 
            handleDo();
        if ((currentToken.lexeme == "}" || currentToken.lexeme == ";") 
        && parseStack[pStackSize - 1].lexeme == "THEN" && tokens[i + 1].lexeme != "ELSE") 
            popIfThen();
        if ((currentToken.lexeme == "}" || currentToken.lexeme == ";") 
        && parseStack[pStackSize - 1].lexeme == "ELSE") 
            popIfThenElse();  
        if ((currentToken.lexeme == "}" || currentToken.lexeme == ";") 
        && parseStack[pStackSize - 1].lexeme == "DO") 
            popWhileDo();
        if (inProc && scopeDepth == 1) {
            handleProcedureEnd(procName);
            inProc = false; procName = "";
        }
    }
}