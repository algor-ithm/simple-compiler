#ifndef PARSER_H
#define PARSER_H

#include "enumDefinitions.h"
#include <iostream>
#include <vector>

using  namespace std;

class Parser
{
private:
    char opPrecedence[PO_COUNT][PO_COUNT];
    void configOpTable();
 
public:
    Parser();
};

#endif