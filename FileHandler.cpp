#include "FileHandler.h"

string FileHandler::readProgram(const string &filePath) const {
    ifstream pgmFile(filePath);
    if (!pgmFile.is_open()) {
        throw runtime_error("Could not open file: " + this->filePath);
    }
    string buffer((std::istreambuf_iterator<char>(pgmFile)),
                         std::istreambuf_iterator<char>());
    return buffer;
}

void FileHandler::writeTokenList(const vector<Token>& tokens) {
    const string filename = "textFiles/token-list.tsv";

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