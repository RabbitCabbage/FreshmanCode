/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"

using namespace std;

//就默认构造函数就可以
Program::Program() = default;

Program::~Program() {
    program_lines.clear();
}

void Program::clear() {
    program_lines.clear();

}

void Program::addSourceLine(int lineNumber, string line) {
    program_lines[lineNumber] = line;

}

void Program::removeSourceLine(int lineNumber) {
    program_lines.erase(lineNumber);

}

string Program::getSourceLine(int lineNumber) {
    return program_lines[lineNumber];
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {

}

Statement *Program::getParsedStatement(int lineNumber) {
    return NULL;
}

int Program::getFirstLineNumber() {
    if (program_lines.empty())return -1;
    else {
        map<int, string>::iterator ptr;
        ptr = program_lines.begin();
        return ptr->first;
    }
}

int Program::getNextLineNumber(int lineNumber) {
    map<int, string>::iterator ptr;
    ptr = program_lines.find(lineNumber);
    ptr++;
    if (ptr != program_lines.end())
        return ptr->first;
    else return -1;
}
bool Program::require(int line_num){
    if(program_lines.count(line_num))return true;
    else return false;
}