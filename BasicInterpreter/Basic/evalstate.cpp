/*
 * File: evalstate.cpp
 * -------------------
 * This file implements the EvalState class, which defines a symbol
 * table for keeping track of the value of identifiers.  The public
 * methods are simple enough that they need no individual documentation.
 */

#include <string>
#include "evalstate.h"
#include <unordered_set>

#include "../StanfordCPPLib/map.h"

using namespace std;
unordered_set<string> command_issue_{"REM", "INPUT", "LET", "PRINT", "END", "IF", "RUN", "CLEAR", "QUIT", "HELP", "LIST",
                                    "GOTO"};

/* Implementation of the EvalState class */

EvalState::EvalState() {
    /* Empty */
}

EvalState::~EvalState() {
    /* Empty */
}

void EvalState::setValue(string var, int value) {
    symbolTable.put(var, value);
}

int EvalState::getValue(string var) {
    return symbolTable.get(var);
}

bool EvalState::isDefined(string var) {
    return symbolTable.containsKey(var);
}

bool EvalState::identifier_collision(string var) {
    if (command_issue_.count(var))return true;
    else return false;
}

void EvalState::clear(){
   symbolTable.clear();
}