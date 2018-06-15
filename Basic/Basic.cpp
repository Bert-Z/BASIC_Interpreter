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
void processLine(string line, Program &program, EvalState &state);
void getProgram(string line, Program &program);
/* Main program */

int main()
{
    EvalState state;
    Program program;

    cout << "Stub implementation of BASIC" << endl;
    while (true)
    {
        try
        {
            string line;
            getline(cin, line);
            while (line != "RUN" && line != "QUIT" && line != "CLEAR" && line != "LIST" && line != "HELP")
            {
                lines.push_back(line);
                getline(cin, line);
            }
            for (auto it : lines)
            {
                getProgram(it, program);
            }


            if (line == "QUIT")
                return 0;
            if (line == "CLEAR")
            {
                lines.clear();
                program.clear();
            }
            if (line == "LIST")
            {
                int First = program.getFirstLineNumber();
                cout << First << " " << program.getSourceLine(First) << endl;
                int thisnum = program.getNextLineNumber(First);
                while (thisnum != First)
                {
                    cout << thisnum << " " << program.getSourceLine(thisnum) << endl;

                    thisnum = program.getNextLineNumber(thisnum);
                }
            }
            if (line == "HELP")
            {
                cout << "Yet another basic interpreter." << endl;
            }
            // if (line == "RUN")
            // {
            // }
        }
        catch (ErrorException &ex)
        {
            cerr << "Error: " << ex.getMessage() << endl;
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

void processLine(string line, Program &program, EvalState &state)
{
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);

    Expression *exp = parseExp(scanner);
    int value = exp->eval(state);
    cout << value << endl;
    delete exp;
}

void getProgram(string line, Program &program)
{
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    parseProgram(line, scanner, program);
}
