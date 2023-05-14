/*
 * File: parser.cpp
 * ----------------
 * Implements the parser.h interface.
 */

#include <iostream>
#include <string>
#include <sstream>
#include<unordered_set>
#include "exp.h"
#include "parser.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/strlib.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "program.h"
#include "statement.h"


using namespace std;
unordered_set<string> command_issue{"REM", "INPUT", "LET", "PRINT", "END", "IF", "RUN", "CLEAR", "QUIT", "HELP",
                                    "LIST",
                                    "GOTO"};

/*
 * Implementation notes: parseExp
 * ------------------------------
 * This code just reads an expression and then checks for extra tokens.
 */
//将具有计算功能的部分特化，我们仍要输入一个string，仅含有运算式,相当于之前的效果一点没变
Expression *parseExp_calculation(TokenScanner &scanner) {
    Expression *exp = readE(scanner);
    if (scanner.hasMoreTokens()) {
        error("parseExp: Found extra token: " + scanner.nextToken());
    }
    return exp;
}

//parser的部分是有行号的部分
int parseExp(TokenScanner &scanner, Program &program, EvalState &state) {
    int line_number;
    while (scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        //处理行数
        int ascii = token[0] - '0';
        if (ascii < 0 || ascii > 9) {
            if (command_issue.count(token)) {
                if (token == "IF") {
                    Statement *st = new if_then;
                    line_number = st->execute(state, program, scanner);
                    delete st;
                } else if (token == "LET") {
                    Statement *st = new let;
                    line_number = st->execute(state, program, scanner);
                    delete st;
                } else if (token == "INPUT") {
                    Statement *st = new input;
                    line_number = st->execute(state, program, scanner);
                    delete st;
                } else if (token == "PRINT") {
                    Statement *st = new print;
                    line_number = st->execute(state, program, scanner);
                    delete st;
                } else if (token == "END") {
                    Statement *st = new end_;
                    line_number = st->execute(state, program, scanner);
                    delete st;
                    break;
                } else if (token == "REM") {
                    Statement *st = new rem;
                    line_number = st->execute(state, program, scanner);
                    delete st;
                    break;
                } else if (token == "GOTO") {
                    Statement *st = new goto_line;
                    line_number = st->execute(state, program, scanner);
                    delete st;
                } else if (token == "RUN") {
                    Statement *st = new run;
                    line_number = st->execute(state, program, scanner);
                    delete st;
                } else if (token == "LIST") {
                    Statement *st = new list;
                    line_number = st->execute(state, program, scanner);
                    delete st;
                } else if (token == "CLEAR") {
                    Statement *st = new clear;
                    line_number = st->execute(state, program, scanner);
                    delete st;
                } else if (token == "QUIT") {
                    Statement *st = new quit;
                    line_number = st->execute(state, program, scanner);
                    delete st;
                }

            }

        }
    }
    return line_number;
};

/*
 * Implementation notes: readE
 * Usage: exp = readE(scanner, prec);
 * ----------------------------------
 * This version of readE uses precedence to resolve the ambiguity in
 * the grammar.  At each recursive level, the parser reads operators and
 * subexpressions until it finds an operator whose precedence is greater
 * than the prevailing one.  When a higher-precedence operator is found,
 * readE calls itself recursively to read in that subexpression as a unit.
 */

Expression *readE(TokenScanner &scanner, int prec) {
    Expression *exp = readT(scanner);
    string token;
    while (true) {
        token = scanner.nextToken();
        int newPrec = precedence(token);
        if (newPrec <= prec) break;
        Expression *rhs = readE(scanner, newPrec);
        exp = new CompoundExp(token, exp, rhs);
    }
    scanner.saveToken(token);
    return exp;
}

/*
 * Implementation notes: readT
 * ---------------------------
 * This function scans a term, which is either an integer, an identifier,
 * or a parenthesized subexpression.
 */

Expression *readT(TokenScanner &scanner) {
    string token = scanner.nextToken();
    TokenType type = scanner.getTokenType(token);
    if (type == WORD) return new IdentifierExp(token);
    if (type == NUMBER) return new ConstantExp(stringToInteger(token));
    if (token != "(") error("Illegal term in expression");
    Expression *exp = readE(scanner);
    if (scanner.nextToken() != ")") {
        error("Unbalanced parentheses in expression");
    }
    return exp;
}

/*
 * Implementation notes: precedence
 * --------------------------------
 * This function checks the token against each of the defined operators
 * and returns the appropriate precedence value.
 */

int precedence(string token) {
    if (token == "=") return 1;
    if (token == "+" || token == "-") return 2;
    if (token == "*" || token == "/") return 3;
    return 0;
}
