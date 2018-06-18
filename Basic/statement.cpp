/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include "statement.h"
#include "parser.h"
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

SStatement::~SStatement(){};

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
        int val = exp->eval(state);
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

        cout << " ? ";
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
    error("SYNTAX ERROR7");
    return;
}

CStatement::CStatement(string cstype, string line)
{
    this->line = line;
    this->cstype = cstype;
}

CStatement::~CStatement(){};

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
    // cout << line << endl;
    string gettype = scanner.nextToken();

    if (cstype == "GOTO")
    {
        string token = scanner.nextToken();

        for (auto it : token)
        {
            if (!isdigit(it))
                error("SYNTAX ERROR6");
        }

        linenum = stringToInteger(token);
        return;
    }
    if (cstype == "IF")
    {
        string lefte, cmp, righte, then;

        size_t f1 = line.find('=');
        size_t f2 = line.find('>');
        size_t f3 = line.find('<');
        size_t f4 = line.find("THEN");
        if (f1 != string::npos)
        {
            cmp = "=";
            lefte = line.substr(4, f1 - 4);
            righte = line.substr(f1 + 1, f4 - f1 - 1);
        }
        if (f2 != string::npos)
        {
            cmp = ">";
            lefte = line.substr(4, f2 - 4);
            righte = line.substr(f2 + 1, f4 - f2 - 1);
        }
        if (f3 != string::npos)
        {
            cmp = "<";
            lefte = line.substr(4, f3 - 4);
            righte = line.substr(f3 + 1, f4 - f3 - 1);
        }

        TokenScanner scanner1;
        scanner1.ignoreWhitespace();
        scanner1.scanNumbers();
        scanner1.setInput(lefte);
        Expression *lexp = parseExp(scanner1);
        int lval = lexp->eval(state);

        TokenScanner scanner2;
        scanner2.ignoreWhitespace();
        scanner2.scanNumbers();
        scanner2.setInput(righte);
        Expression *rexp = parseExp(scanner2);
        int rval = rexp->eval(state);

        // string cmp = scanner.nextToken();

        // string then = scanner.nextToken();
        if (f4 != string::npos)
        {
            then = line.substr(f4 + 4);
        }

        if (cmp == ">")
        {
            if (lval > rval)
            {
                linenum = stringToInteger(then);
            }
            else
                return;
        }
        if (cmp == "<")
        {
            if (lval < rval)
            {
                linenum = stringToInteger(then);
            }
            else
                return;
        }
        if (cmp == "=")
        {
            if (lval == rval)
            {
                linenum = stringToInteger(then);
            }
            else
                return;
        }

        return;
    }
    // error("SYNTAX ERROR12");
    return;
}
