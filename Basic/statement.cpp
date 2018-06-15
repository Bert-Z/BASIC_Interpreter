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

SStatement::SStatement(string sstype, string line)
{
    this->sstype = sstype;
    this->line = line;
}

string SStatement::getSstype()
{
    return sstype;
}

void SStatement::execute(EvalState &state)
{
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    string gettype = scanner.nextToken();

    if (sstype == "REM")
        return;
    if (sstype == "LET")
    {
        Expression *exp = parseExp(scanner);
        delete exp;

        return;
    }
    if (sstype == "PRINT")
    {
        Expression *exp = parseExp(scanner);
        int value = exp->eval(state);
        cout << value << endl;
        delete exp;

        return;
    }
    if (sstype == "INPUT")
    {
        string token = scanner.nextToken();

        cout << "?";
        int inputvar;
        cin >> inputvar;
        state.setValue(token, inputvar);

        return;
    }
    if (sstype == "END")
    {
        state.setValue("END", 1);
        return;
    }
    error("SYNTAX ERROR");
    return;
}

CStatement::CStatement(string cstype, string line)
{
    this->line = line;
    this->cstype = cstype;
}

string CStatement::getCstype()
{
    return cstype;
}

int CStatement::getLinenum()
{
    return linenum;
}

void CStatement::execute(EvalState &state)
{
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    string gettype = scanner.nextToken();

    if (cstype == "GOTO")
    {
        string token = scanner.nextToken();

        for (auto it : token)
        {
            if (!isdigit(it))
                error("SYNTAX ERROR");
        }

        linenum = stringToInteger(token);
        return;
    }
    if (cstype == "IF")
    {
        Expression *lexp = parseExp(scanner);
        int lval = lexp->eval(state);
        string cmp = scanner.nextToken();
        Expression *rexp = parseExp(scanner);
        int rval = rexp->eval(state);

        string then = scanner.nextToken();
        if (then != "THEN")
            error("SYNTAX ERROR");

        if (cmp == ">")
        {
            if (lval > rval)
            {
                linenum = stringToInteger(scanner.nextToken());
            }
            else
                return;
        }
        if (cmp == "<")
        {
            if (lval < rval)
            {
                linenum = stringToInteger(scanner.nextToken());
            }
            else
                return;
        }
        if (cmp == ">=")
        {
            if (lval >= rval)
            {
                linenum = stringToInteger(scanner.nextToken());
            }
            else
                return;
        }
        if (cmp == "<=")
        {
            if (lval <= rval)
            {
                linenum = stringToInteger(scanner.nextToken());
            }
            else
                return;
        }
        if (cmp == "==")
        {
            if (lval == rval)
            {
                linenum = stringToInteger(scanner.nextToken());
            }
            else
                return;
        }
        if (cmp == "!=")
        {
            if (lval != rval)
            {
                linenum = stringToInteger(scanner.nextToken());
            }
            else
                return;
        }

        return;
    }
    error("SYNTAX ERROR");
    return;
}
