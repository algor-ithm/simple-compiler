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

void FileHandler::writeTokenList(const vector<Token>& tokens) {
    const string filename = "textFiles/token-list.txt";

    ofstream tokenFile(filename);
    if (!tokenFile.is_open()) {
        throw runtime_error("Couldn't not open file: " + filename);
    }
    // Write header line (needed?)
    tokenFile << "Lexeme\tTokenType\n";

    // Iterate through vector and write each token with its type
    for (const auto& token : tokens){
        tokenFile << token.lexeme << "\t" << token.type << "\n";
    }
    tokenFile.close();
}

void FileHandler::writeSymbolTable(const vector<SymbolTableEntry>& symbolList){
    const string filename = "textFiles/symbol-table.txt";

    ofstream symbolFile(filename);
    if(!symbolFile.is_open()){
        throw runtime_error("Could not open file: " + filename);
    }
    // Write header line (if needed?)
    symbolFile << "Token\tType\tValue\tAddress\tSegement\n";

    // Iterate through symbol list and write each one to the file
    for (const auto& symbol : symbolList){
        symbolFile << symbol.token << "\t" << symbol.type << "\t" << symbol.value << "\t" 
            << symbol.address << "\t" << symbol.segment << "\n";
    }
    symbolFile.close();
}