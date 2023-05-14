/*
 * File: parser.h
 * --------------
 * This file acts as the interface to the parser module.作为 语法分析 模块
 */

#ifndef _parser_h
#define _parser_h

#include <string>
#include <unordered_set>
#include "exp.h"
#include "program.h"
#include "../StanfordCPPLib/tokenscanner.h"

extern unordered_set<string> command_issue;

/*
 * Function: parseExp
 * Usage: Expression *exp = parseExp(scanner);
 * -------------------------------------------
 * Parses an expression by reading tokens from the scanner, which must
 * be provided by the client.  The scanner should be set to ignore
 * whitespace and to scan numbers.//scanner要可以忽略空格，并且读入数据
 */

class Program;

Expression *parseExp_calculation(TokenScanner &scanner);
int parseExp(TokenScanner &scanner,Program& program,EvalState& state);
/*
 * Function: readE
 * Usage: Expression *exp = readE(scanner, prec);
 * ----------------------------------------------
 * Returns the next expression from the scanner involving only operators whose precedence is at least prec.
 * 返回下一个涉及到运算符的表达式，这个运算符的优先级  >=prec
 * The prec argument is optional and
 * defaults to 0, which means that the function reads the entire expression.
 */

Expression *readE(TokenScanner &scanner, int prec = 0);

/*
 * Function: readT
 * Usage: Expression *exp = readT(scanner);
 * ----------------------------------------
 * Returns the next individual term, which is either a constant, an
 * identifier, or a parenthesized subexpression.
 */

Expression *readT(TokenScanner &scanner);

/*
 * Function: precedence
 * Usage: int prec = precedence(token);
 * ------------------------------------
 * Returns the precedence of the specified operator token.  If the token
 * is not an operator, precedence returns 0.
 */

int precedence(std::string token);

#endif
