//
// Created by lu'ren'jia'd's on 2022/6/23.
//

#ifndef UNTITLED4_CONTOL_H
#define UNTITLED4_CONTOL_H

#include <string>
#include <iostream>
#include "tool.h"
#include "risc-v32.h"

extern int Register[32];
extern int Memory[500000];
extern int Current;
//read commands into memory
//读进所有的指令并且把它以十进制的形式存在了内存里面
void ReadCommand() {
    char x;
    int addr;
    while (std::cin >> x) {
        if (x == '@') {
            std::string address;
            address.clear();
            for (int i = 0; i < 8; ++i) {
                std::cin >> x;
                address += x;
            }
            addr = Hex_Decimal(address);
        } else if (x == ' ')continue;
        else if (x == '#')break;
        else {
            std::string section;//指令的片段，是一个十六进制数字
            section += x;
            std::cin >> x;
            section += x;
            Memory[addr++] = Hex_Decimal(section);
        }
    }
}

std::string Parser() {
    std::string dir;
    dir.clear();
    for (int i = 3; i >= 0; --i) {
        std::string part = Decimal_Hex(Memory[Current + i]);
        if (part.length() == 1)part = '0' + part;
        dir += part;
    }
    Current += 4;
//    //std::cout << dir << std::endl;
    return dir;
}

void Trans(const std::string &dir) {
    std::string com = dir.substr(25, 7);
    if (com == "0110111")Lui(dir);
    else if (com == "0010111")Auipc(dir);
    else if (com == "1101111")Jal(dir);
    else if (com == "1100111")Jalr(dir);
    else if (com == "1100011") {
        std::string f3 = dir.substr(17, 3);
        if (f3 == "000")Beq(dir);
        else if (f3 == "001")Bne(dir);
        else if (f3 == "100")Blt(dir);
        else if (f3 == "101")Bge(dir);
        else if (f3 == "110")Bltu(dir);
        else if (f3 == "111")Bgeu(dir);
    } else if (com == "0000011") {
        std::string f3 = dir.substr(17, 3);
        if (f3 == "000")Lb(dir);
        else if (f3 == "001")Lh(dir);
        else if (f3 == "010")Lw(dir);
        else if (f3 == "100")Lbu(dir);
        else if (f3 == "101")Lhu(dir);
    } else if (com == "0100011") {
        std::string f3 = dir.substr(17, 3);
        if (f3 == "000") Sb(dir);
        else if (f3 == "001")Sh(dir);
        else if (f3 == "010")Sw(dir);
    } else if (com == "0010011") {
        std::string f3 = dir.substr(17, 3);
        if (f3 == "000")Addi(dir);
        else if (f3 == "010")Slti(dir);
        else if (f3 == "011")Sltiu(dir);
        else if (f3 == "001")Slli(dir);
        else if (f3 == "100")Xori(dir);
        else if (f3 == "101") {
            std::string f7 = dir.substr(0, 7);
            if (f7 == "0000000")Srli(dir);
            else Srai(dir);
        } else if (f3 == "110")Ori(dir);
        else if (f3 == "111")Andi(dir);
    } else if (com == "0110011") {
        std::string f3 = dir.substr(17, 3);
        if (f3 == "000") {
            std::string f7 = dir.substr(0, 7);
            if (f7 == "0000000")Add(dir);
            else Sub(dir);
        } else if (f3 == "001")Sll(dir);
        else if (f3 == "010")Slt(dir);
        else if (f3 == "011")Sltu(dir);
        else if (f3 == "100")Xor(dir);
        else if (f3 == "101") {
            std::string f7 = dir.substr(0, 7);
            if (f7 == "0000000")Srl(dir);
            else Sra(dir);
        } else if (f3 == "110")Or(dir);
        else if (f3 == "111")And(dir);
    }
}

#endif //UNTITLED4_CONTOL_H
