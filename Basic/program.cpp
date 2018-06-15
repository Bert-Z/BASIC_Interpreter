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
#include "statement.h"
#include <string>
using namespace std;

Program::Program()
{
    // Replace this stub with your own code
}

Program::~Program()
{
    // Replace this stub with your own code
}

void Program::clear()
{
    // Replace this stub with your own code
    linebox.clear();
    Soureline.clear();
}

void Program::addSourceLine(int lineNumber, string line)
{
    // Replace this stub with your own code
    linebox.push_back(lineNumber);
    sort(linebox.begin(), linebox.end());
    Soureline[lineNumber] = line;
}

void Program::removeSourceLine(int lineNumber)
{
    // Replace this stub with your own code

    Soureline.erase(lineNumber);
}

string Program::getSourceLine(int lineNumber)
{
    return Soureline[lineNumber]; // Replace this stub with your own code
}

void Program::setParsedStatement(int lineNumber, Statement *stmt)
{
    // Replace this stub with your own code
    if (Soureline.count(lineNumber) == 0)
        error("This line don't exist!");

    string line = Soureline[lineNumber];
}

Statement *Program::getParsedStatement(int lineNumber)
{
    return NULL; // Replace this stub with your own code
}

int Program::getFirstLineNumber()
{
    // Replace this stub with your own code

    return Soureline.begin()->first;
}

int Program::getNextLineNumber(int lineNumber)
{

    // Replace this stub with your own code
    auto it = Soureline.lower_bound(lineNumber);
    if (it == Soureline.end())
        return -1;
    else
        return Soureline.upper_bound(lineNumber)->first;
}
