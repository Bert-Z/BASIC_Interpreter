/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include "program.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "statement.h"
#include <string>
using namespace std;

Program::Program()
{
    /*empty*/
}

Program::~Program()
{
}

void Program::clear()
{
    Soureline.clear();
}

void Program::addSourceLine(int lineNumber, string line)
{
    Soureline[lineNumber] = line;
}

void Program::removeSourceLine(int lineNumber)
{
    Soureline.erase(lineNumber);
}

string Program::getSourceLine(int lineNumber)
{
    return Soureline[lineNumber];
}

void Program::setParsedStatement(int lineNumber, Statement *stmt)
{
    if (Soureline.count(lineNumber) == 0)
        error("This line don't exist!");

    string line = Soureline[lineNumber];
}

Statement *Program::getParsedStatement(int lineNumber)
{
    string line = getSourceLine(lineNumber);

    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);

    string token = scanner.nextToken();
    if (token == "REM" || token == "LET" || token == "PRINT" || token == "INPUT" || token == "END")
    {
        SStatement *stmt = new SStatement(token, line);
        return stmt;
    }
    else if (token == "GOTO" || token == "IF")
    {
        CStatement *stmt = new CStatement(token, line);
        thislineNumber = stmt->getLinenum();
        return stmt;
    }
    else
        error("SYNTAX ERROR");
}

int Program::getFirstLineNumber()
{
    return Soureline.begin()->first;
}

int Program::getNextLineNumber(int lineNumber)
{
    int nextnum = Soureline.upper_bound(lineNumber)->first;

    if (nextnum != Soureline.end()->first)
        return Soureline.upper_bound(lineNumber)->first;
    else
        return Soureline.begin()->first;
}
