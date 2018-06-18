/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "exp.h"
#include "parser.h"
#include "program.h"
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

vector<string> lines;
int processLine(int linenum, Program &program, EvalState &state);
void directPro(string line, EvalState &state);
void getProgram(string line, Program &program);
void LISTfunc(Program &program);
void processProgram(Program &program, EvalState &state);
/* Main program */

int main()
{
    EvalState state;
    Program program;

    while (true)
    {
        try
        {
            string line;
            getline(cin, line);
            while (line != "QUIT" && line != "CLEAR" && line != "LIST" && line != "HELP" && line != "RUN")
            {
                lines.push_back(line);

                if (isdigit(line[0]))
                {
                    getProgram(line, program);
                }
                else
                {
                    directPro(line, state);
                }

                getline(cin, line);
            }

            if (line == "QUIT")
                return 0;
            else if (line == "CLEAR")
            {
                lines.clear();
                program.clear();
                state.clear();
            }
            else if (line == "LIST")
            {
                LISTfunc(program);
            }
            else if (line == "HELP")
            {
                cout << "Yet another basic interpreter." << endl;
            }
            else if (line == "RUN")
            {
                processProgram(program, state);
            }
            else
                error("SYNTAX ERROR1");
        }
        catch (ErrorException &ex)
        {
            cout << ex.getMessage() << endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

int processLine(int linenum, Program &program, EvalState &state)
{
    string line = program.getSourceLine(linenum);
    program.thislineNumber = linenum;

    Statement *stm = program.getParsedStatement(state, linenum);
    stm->execute(state);
    delete stm;

    if (program.thislineNumber == linenum)
        return program.getNextLineNumber(linenum);
    else
        return program.thislineNumber;
}

void processProgram(Program &program, EvalState &state)
{
    int First = program.getFirstLineNumber();

    int thisnum = processLine(First, program, state);
    while (thisnum != First && !state.isDefined("END"))
    {
        thisnum = processLine(thisnum, program, state);
        if (program.Soureline.count(thisnum) == 0)
        {
            error("LINE NUMBER ERROR");
        }
    }
}

void LISTfunc(Program &program)
{
    if (lines.size() == 0)
        return;
    int First = program.getFirstLineNumber();
    cout << First << program.getSourceLine(First) << endl;

    int thisnum = program.getNextLineNumber(First);
    while (thisnum != First)
    {
        cout << thisnum << program.getSourceLine(thisnum) << endl;

        thisnum = program.getNextLineNumber(thisnum);
    }
}

void getProgram(string line, Program &program)
{
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    parseProgram(line, scanner, program);
}

void directPro(string line, EvalState &state)
{
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    string gettype = scanner.nextToken();

    if (gettype == "REM")
        return;
    if (gettype == "LET")
    {
        Expression *exp = parseExp(scanner);
        int val = exp->eval(state);
        delete exp;

        return;
    }
    if (gettype == "PRINT")
    {
        Expression *exp = parseExp(scanner);
        int value = exp->eval(state);
        cout << value << endl;
        delete exp;

        return;
    }
    if (gettype == "INPUT")
    {
        string token = scanner.nextToken();

        cout << " ? ";
        string inputvar;
        getline(cin, inputvar);

        int check = 0;

        for (int i = 0; i < inputvar.size(); i++)
        {
            if (i == 0)
            {
                if (inputvar[i] == '+' || inputvar[i] == '-' || isdigit(inputvar[i]))
                    check++;
            }
            else
            {
                if (isdigit(inputvar[i]))
                    check++;
            }
        }

        if (check != inputvar.size())
        {
            cout << "INVALID NUMBER" << endl;
            cout << " ? ";
            getline(cin, inputvar);
            check = 0;
        }

        int var = stringToInteger(inputvar);

        state.setValue(token, var);

        return;
    }
    // else
    //     error("SYNTAX ERROR");
    return;
}