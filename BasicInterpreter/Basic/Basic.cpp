/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BASIC interpreter.
 */

#include <cctype>
#include<sstream>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"

using namespace std;

/* Function prototypes */

void processLine(string line, Program &program, EvalState &state);

/* Main program */

int main() {
    EvalState state;
    Program program;
    /* cout << "Stub implementation of BASIC" << endl;*/
    while (true) {
        try {
            string input = getLine();
            if (input.empty())
                return 0;
            processLine(input, program, state);
        } catch (ErrorException &ex) {
            cerr << "Error: " << ex.getMessage() << endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version of
 * implementation, the program reads a line, parses it as an expression,
 * and then prints the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program &program, EvalState &state) {
    int ascii = line[0] - '0';
    //有行号的情况，直接存到map
    if (ascii >= 0 && ascii <= 9) {
        TokenScanner scanner;
        scanner.ignoreWhitespace();
        scanner.scanNumbers();
        scanner.setInput(line);
        string line_num_str = scanner.nextToken();
        stringstream ss;
        ss.clear();
        ss.str(line_num_str);
        int line_num;
        ss >> line_num;
        if (line == line_num_str)program.removeSourceLine(line_num);
        else program.addSourceLine(line_num, line);
    } else {
        TokenScanner scanner;
        scanner.ignoreWhitespace();
        scanner.scanNumbers();
        scanner.setInput(line);
        int invalid = parseExp(scanner, program, state);

    }
//    TokenScanner scanner;
//    scanner.ignoreWhitespace();
//    scanner.scanNumbers();
//    scanner.setInput(line);
//    Expression *exp = parseExp(scanner);
//    int value = exp->eval(state);
//    cout << value << endl;
//    delete exp;
}
