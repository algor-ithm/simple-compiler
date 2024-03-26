#include "FileHandler.h"

string FileHandler::readProgram(const string &filePath) const {
    ifstream pgmFile(filePath);
    if (!pgmFile.is_open()) {
        throw runtime_error("Could not open file: " + this->filePath);
    }
    string buffer((std::istreambuf_iterator<char>(pgmFile)),
                         std::istreambuf_iterator<char>());
    
    pgmFile.close();
    return buffer;
}

void FileHandler::writeTokenList(const Token* tokens, int tokenCount) {
    const string filename = "textFiles/token-list.txt";

    ofstream tokenFile(filename);
    if (!tokenFile.is_open()) {
        throw runtime_error("Couldn't not open file: " + filename);
    }
    // Write header line (needed?)
    tokenFile << "Lexeme\tTokenType\n";

    // Iterate through vector and write each token with its type
    for(int i = 0; i < tokenCount; i++) {
        tokenFile << tokens[i].lexeme << "\t" << tokens[i].type << "\n";
    }
    tokenFile.close();
}

void FileHandler::writeSymbolTable(const SymbolTableEntry* symbolList, int symbolCount){
    const string filename = "textFiles/symbol-table.txt";

    ofstream symbolFile(filename);
    if(!symbolFile.is_open()){
        throw runtime_error("Could not open file: " + filename);
    }
    // Write header line (if needed?)
    symbolFile << "Token\tType\tValue\tAddress\tSegement\n";

    // Iterate through symbol list and write each one to the file
    for (int i = 0; i < symbolCount; i++){
        symbolFile << symbolList[i].token << "\t" << symbolList[i].type << "\t" << symbolList[i].value << "\t" 
            << symbolList[i].address << "\t" << symbolList[i].segment << "\n";
    }
    symbolFile.close();
}

//write quads?