/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include "statement.h"
#include <string>
using namespace std;

/* Implementation of the Statement class */

Statement::Statement()
{
    /* Empty */
}

Statement::~Statement()
{
    /* Empty */
}

SStatement::SStatement(string sstype)
{
    this->sstype = sstype;
}

string SStatement::getSstype()
{
    return sstype;
}

string SStatement::getVar()
{
    return variable;
}

Expression *SStatement::getNEXP()
{
    return nexp;
}

void SStatement::execute(EvalState &state)
{
    if (sstype == "REM")
        return;
    if (sstype == "LET")
    {
        int var = nexp->eval(state);
        varmap[variable] = var;
        return;
    }
    if (sstype == "PRINT")
    {
        cout << varmap[variable] << endl;
        return;
    }
    if (sstype == "INPUT")
    {
        cout << "?";
        int inputvar;
        cin >> inputvar;
        varmap[variable] = inputvar;
        return;
    }
    if (sstype == "END")
    {
        
    }
    error("SYNTAX ERROR");
    return;
}