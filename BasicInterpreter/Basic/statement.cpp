/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include<unordered_set>
#include"../StanfordCPPLib/tokenscanner.h"
#include"program.h"

using namespace std;
unordered_set<string> command_issue___{"REM", "INPUT", "LET", "PRINT", "END", "IF", "RUN", "CLEAR", "QUIT", "HELP",
                                       "LIST",
                                       "GOTO"};
bool end_mark = false;

/* Implementation of the Statement class */

Statement::Statement() {
    /* Empty */
}

Statement::~Statement() {
    /* Empty */
}

quit::quit() = default;

quit::~quit() = default;

int quit::execute(EvalState &state, Program &program, TokenScanner &scanner) {
    exit(0);
}

end_::end_() = default;

end_::~end_() = default;

int end_::execute(EvalState &state, Program &program, TokenScanner &scanner) {
    end_mark = true;
    return -1;
    // break;
}

list::list() = default;

list::~list() = default;

int list::execute(EvalState &state, Program &program, TokenScanner &scanner) {
    int line_number = program.getFirstLineNumber();
    while (line_number != -1) {
        string line = program.getSourceLine(line_number);
        cout << line << endl;
        line_number = program.getNextLineNumber(line_number);
    }
    return -1;
}

run::run() = default;

run::~run() = default;

int run::execute(EvalState &state, Program &program, TokenScanner &scanner) {
    end_mark = false;
    int line_number = program.getFirstLineNumber();
    while (line_number != -1) {
        string line = program.getSourceLine(line_number);
        TokenScanner run_scanner;
        run_scanner.ignoreWhitespace();
        run_scanner.scanNumbers();
        run_scanner.setInput(line);
        int return_number = parseExp(run_scanner, program, state);//如果有goto语句就返回了下一句的行号
        if (return_number == -1) line_number = program.getNextLineNumber(line_number);
        else {
            line_number = return_number;
            if (!program.require(line_number)) {
                cout << "LINE NUMBER ERROR" << endl;
                break;
            } else continue;
        }
        if (end_mark)break;
    }
    return -1;
}

rem::rem() = default;

rem::~rem() = default;

int rem::execute(EvalState &state, Program &program, TokenScanner &scanner) {
    //  break;
    return -1;
}

print::print() = default;

print::~print() = default;

int print::execute(EvalState &state, Program &program, TokenScanner &scanner) {
    string token;
    string print_expression;
    while (scanner.hasMoreTokens()) {
        token = scanner.nextToken();
        print_expression += token;
    }
    TokenScanner print_scanner;
    print_scanner.ignoreWhitespace();
    print_scanner.scanNumbers();
    print_scanner.setInput(print_expression);
    Expression *print_exp = parseExp_calculation(print_scanner);
    int value = print_exp->eval(state);
    if (value != -19260817)
        cout << value << endl;
    return -1;
}

input::input() = default;

input::~input() = default;

int input::execute(EvalState &state, Program &program, TokenScanner &scanner) {
    string token;
    token = scanner.nextToken();
    string input_string = token;
    int input_num;
    cout << " ? ";
    cin >> input_num;
    if (!cin.fail()) {
        if (getchar() != '\n') {
            cout << "INVALID NUMBER" << endl;
            cin.clear();
            cout << " ? ";
            cin.ignore(10000, '\n');
            cin >> input_num;
            getchar();
        }
    }
    while (cin.fail()) {
        cout << "INVALID NUMBER" << endl;
        cin.clear();
        cout << " ? ";
        cin.ignore(10000, '\n');
        cin >> input_num;
        if (!cin.fail()) {
            if (getchar() != '\n') {
                cout << "INVALID NUMBER" << endl;
                cin.clear();
                cout << " ? ";
                cin.ignore(10000, '\n');
                cin >> input_num;
                getchar();
            }
        }

    }

    stringstream ss;
    ss.clear();
    ss << input_num;
    string input_trans;
    ss >> input_trans;
    input_string += "=";
    if (input_num < 0)input_string += "0";
    input_string += input_trans;
    TokenScanner input_scanner;
    input_scanner.ignoreWhitespace();
    input_scanner.scanNumbers();
    input_scanner.setInput(input_string);
    Expression *input_exp = parseExp_calculation(input_scanner);
    int value = input_exp->eval(state);
    return -1;
}

if_then::if_then() = default;

if_then::~if_then() = default;

int if_then::execute(EvalState &state, Program &program, TokenScanner &scanner) {
    //variable for condition
    string token;
    string condition_lhs, condition_rhs, condition_op;
    int condition_lhs_value, condition_rhs_value;
    bool condition_judge;
    TokenScanner lhs_scanner, rhs_scanner;
    Expression *expl;
    Expression *expr;
    //找到比较运算符，并且比较两边的值
    while (scanner.hasMoreTokens()) {
        token = scanner.nextToken();
        if (token == "=" || token == "<" || token == ">") {
            condition_op = token;
            break;
        } else {
            condition_lhs += token;
        }
    }
    while (scanner.hasMoreTokens()) {
        token = scanner.nextToken();
        if (token == "THEN")break;
        else condition_rhs += token;
    }
    lhs_scanner.ignoreWhitespace();
    lhs_scanner.scanNumbers();
    lhs_scanner.setInput(condition_lhs);
    expl = parseExp_calculation(lhs_scanner);
    condition_lhs_value = expl->eval(state);
    rhs_scanner.ignoreWhitespace();
    rhs_scanner.scanNumbers();
    rhs_scanner.setInput(condition_rhs);
    expr = parseExp_calculation(rhs_scanner);
    condition_rhs_value = expr->eval(state);
    delete expl;
    delete expr;
    if (condition_op == "=") {
        if (condition_lhs_value == condition_rhs_value)
            condition_judge = true;
        else condition_judge = false;
    } else if (condition_op == "<") {
        if (condition_lhs_value < condition_rhs_value)
            condition_judge = true;
        else condition_judge = false;
    } else {
        if (condition_lhs_value > condition_rhs_value)
            condition_judge = true;
        else condition_judge = false;
    }
    if (condition_judge) {
        string line_number = scanner.nextToken();
        stringstream ss;
        ss.clear();
        ss << line_number;
        int line_num;
        ss >> line_num;
        return line_num;//todo
    } else return -1;
}

goto_line::goto_line() = default;

goto_line::~goto_line() = default;

int goto_line::execute(EvalState &state, Program &program, TokenScanner &scanner) {
    string token;
    token = scanner.nextToken();
    stringstream ss;
    ss.clear();
    ss << token;
    int line_goto;
    ss >> line_goto;
    return line_goto;//这里返回了goto的句子编号//todo
}

clear::clear() = default;

clear::~clear() = default;

int clear::execute(EvalState &state, Program &program, TokenScanner &scanner) {
    program.clear();
    state.clear();
    return -1;
}

let::let() = default;

let::~let() = default;

int let::execute(EvalState &state, Program &program, TokenScanner &scanner) {
    string let_expression, token;
    while (scanner.hasMoreTokens()) {
        token = scanner.nextToken();
        let_expression += token;
    }
    TokenScanner let_scanner;
    let_scanner.ignoreWhitespace();
    let_scanner.scanNumbers();
    let_scanner.setInput(let_expression);
    Expression *let_exp = parseExp_calculation(let_scanner);
    int value = let_exp->eval(state);
    return -1;
}

help::help() = default;

help::~help() = default;

int help::execute(EvalState &state, Program &program, TokenScanner &scanner) {
    return -1;
}
