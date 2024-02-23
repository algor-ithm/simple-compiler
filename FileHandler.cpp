#include "FileHandler.h"

string FileHandler::readProgram(const string &filePath) const {
    ifstream pgmFile(this->filePath);
    if (!pgmFile.is_open()) {
        throw runtime_error("Could not open file: " + this->filePath);
    }
    string buffer((std::istreambuf_iterator<char>(pgmFile)),
                         std::istreambuf_iterator<char>());
    return buffer;
}