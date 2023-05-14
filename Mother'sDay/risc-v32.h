//
// Created by lu'ren'jia'd's on 2022/6/23.
//

#ifndef UNTITLED4_RISC_V32_H
#define UNTITLED4_RISC_V32_H

#include <string>
#include <iostream>
#include "tool.h"

extern int Register[32];
extern int Memory[500000];
extern int Current;

void Lui(const std::string &dir) {
    //std::cout << "lui" << "\t";
    std::string imm;
    int rd;
    U_Type(dir, imm, rd);
    Register[rd] = Decode(imm + "000000000000");
    //std::cout << rd << " " << Decode(imm + "000000000000") << " ";
//    //std::cout << rd << " " << (Binary_Decimal(imm) << 12) << std::endl;
}

void Auipc(const std::string &dir) {
    //std::cout << "auipc" << "\t";
    std::string imm;
    int rd;
    U_Type(dir, imm, rd);
    Register[rd] = Decode(imm + "000000000000") + Current - 4;
    //std::cout << rd << " " << Decode(imm + "000000000000");
}

void Jal(const std::string &dir) {
    //std::cout << "jal" << "\t";
    std::string imm;
    int rd;
    J_Type(dir, imm, rd);
    Register[rd] = Current;
    Current += Decode(imm) - 4;
    //std::cout << rd << " " << Decimal_Hex(Current);
}

void Jalr(const std::string &dir) {
    //std::cout << "jalr" << "\t";
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    Register[rd] = Current;
    std::cout << "@@@@@@ " << imm << " " << Register[rs1] << std::endl;
    std::string cur = Decimal_Binary32(Decode(imm) + Register[rs1]);
    cur[31] = '0';
    Register[rd] = Current;
    Current = Binary_Decimal(cur);
    //std::cout << rd << " " << Decimal_Hex(Current);
}

void Beq(const std::string &dir) {
    //std::cout << "beq" << "\t";
    int rs2, rs1;
    std::string imm;
    B_Type(dir, imm, rs1, rs2);
    //现在的Current已经是指向下一条指令了，相当于正在执行的+4了
    //std::cout << Register[rs1] << " " << Register[rs2] << " ";
    if (Register[rs1] == Register[rs2]) {
        Current += Decode(imm) - 4;
        //std::cout << "jump to " << Current;
    }
}

void Bne(const std::string &dir) {
    //std::cout << "bne" << "\t";
    int rs2, rs1;
    std::string imm;
    B_Type(dir, imm, rs1, rs2);
    //std::cout << Register[rs1] << " " << Register[rs2] << " ";
    if (Register[rs1] != Register[rs2]) {
        Current += Decode(imm) - 4;
        //std::cout << "jump to " << Current;
    }
}

void Blt(const std::string &dir) {
    //std::cout << "blt" << "\t";
    int rs2, rs1;
    std::string imm;
    B_Type(dir, imm, rs1, rs2);
    //std::cout << Register[rs1] << " " << Register[rs2] << " ";
    if (Register[rs1] < Register[rs2]) {
        Current += Decode(imm) - 4;
        //std::cout << "jump to " << Current;
    }
}

void Bge(const std::string &dir) {
    //std::cout << "bge" << "\t";
    int rs2, rs1;
    std::string imm;
    B_Type(dir, imm, rs1, rs2);
    //std::cout << Register[rs1] << " " << Register[rs2] << " ";
    if (Register[rs1] >= Register[rs2]) {
        Current += Decode(imm) - 4;
        //std::cout << "jump to " << Current;
    }
}

void Bltu(const std::string &dir) {
    //std::cout << "bltu" << "\t";
    int rs2, rs1;
    std::string imm;
    B_Type(dir, imm, rs1, rs2);
    //std::cout << ((unsigned) Register[rs1]) << " " << ((unsigned) Register[rs2]) << " ";
    if (((unsigned) Register[rs1]) < ((unsigned) Register[rs2])) {
        Current += Decode(imm) - 4;
        //std::cout << "jump to " << Current;
    }
}

void Bgeu(const std::string &dir) {
    //std::cout << "bgeu" << "\t";
    int rs2, rs1;
    std::string imm;
    B_Type(dir, imm, rs1, rs2);
    //std::cout << ((unsigned) Register[rs1]) << " " << ((unsigned) Register[rs2]) << " ";
    if (((unsigned) Register[rs1]) >= ((unsigned) Register[rs2])) {
        Current += Decode(imm) - 4;
        //std::cout << "jump to " << Current;
    }
}

void Lb(const std::string &dir) {
    //std::cout << "lb" << "\t";
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    int address = Register[rs1] + Decode(imm);
    Register[rd] = Decode(Decimal_Binary8(Memory[address]));
    //std::cout << rd << " " << Register[rd];
}

void Lh(const std::string &dir) {
    //std::cout << "lh" << "\t";
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    int address = Register[rs1] + Decode(imm);
    std::string code = Decimal_Binary8(Memory[address + 1]) + Decimal_Binary8(Memory[address]);
    Register[rd] = Decode(code);
    //std::cout << rd << " " << Register[rd];
}

void Lw(const std::string &dir) {
    //std::cout << "lw" << "\t";
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    int address = Register[rs1] + Decode(imm);
    std::string code = Decimal_Binary8(Memory[address + 3]) + Decimal_Binary8(Memory[address + 2])
                       + Decimal_Binary8(Memory[address + 1]) + Decimal_Binary8(Memory[address]);
    Register[rd] = Decode(code);
    //std::cout << rd << " " << Register[rd];
}

void Lbu(const std::string &dir) {
    //std::cout << "lbu" << "\t";
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    int address = Register[rs1] + Decode(imm);
    Register[rd] = DecodeZeroExtend(Decimal_Binary8(Memory[address]));
    //std::cout << rd << " " << Register[rd];
}

void Lhu(const std::string &dir) {
    //std::cout << "lhu" << "\t";
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    int address = Register[rs1] + Decode(imm);
    std::string code = Decimal_Binary8(Memory[address + 1]) + Decimal_Binary8(Memory[address]);
    Register[rd] = DecodeZeroExtend(code);
    //std::cout << rd << " " << Register[rd];
}

void Sb(const std::string &dir) {
    //std::cout << "sb" << "\t";
    int rs1, rs2;
    std::string imm;
    S_Type(dir, imm, rs1, rs2);
    int address = Register[rs1] + Decode(imm);
    std::string b_number32 = Decimal_Binary32(Register[rs2]);
    Memory[address] = Binary_Decimal(b_number32.substr(24, 8));
    //std::cout << rs1 << " " << rs2 << " " << Memory[address];
}

void Sh(const std::string &dir) {
    //std::cout << "sh" << "\t";
    int rs1, rs2;
    std::string imm;
    S_Type(dir, imm, rs1, rs2);
    int address = Register[rs1] + Decode(imm);
    std::string b_number32 = Decimal_Binary32(Register[rs2]);
    Memory[address] = Binary_Decimal(b_number32.substr(24, 8));
    Memory[address + 1] = Binary_Decimal(b_number32.substr(16, 8));
    //std::cout << rs1 << " " << rs2 << " " << Memory[address];
}

void Sw(const std::string &dir) {
    //std::cout << "sw" << "\t";
    int rs1, rs2;
    std::string imm;
    S_Type(dir, imm, rs1, rs2);
    int address = Register[rs1] + Decode(imm);
    std::string b_number32 = Decimal_Binary32(Register[rs2]);
    Memory[address] = Binary_Decimal(b_number32.substr(24, 8));
    Memory[address + 1] = Binary_Decimal(b_number32.substr(16, 8));
    Memory[address + 2] = Binary_Decimal(b_number32.substr(8, 8));
    Memory[address + 3] = Binary_Decimal(b_number32.substr(0, 8));
    //std::cout << rs1 << " " << rs2 << " " << Memory[address];
}

void Xori(const std::string &dir) {
    //std::cout << "xori" << "\t";
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    Register[rd] = Register[rs1] ^ Decode(imm);
    //std::cout << rd << " " << Register[rd];
}

void Ori(const std::string &dir) {
    //std::cout << "ori" << "\t";
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    Register[rd] = Register[rs1] | Decode(imm);
    //std::cout << rd << " " << Register[rd];
}

void Andi(const std::string &dir) {
    //std::cout << "andi" << "\t";
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    Register[rd] = Register[rs1] & Decode(imm);
    //std::cout << rd << " " << Register[rd];
}

void Xor(const std::string &dir) {
    //std::cout << "xor" << "\t";
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    Register[rd] = Register[rs1] ^ Register[rs2];
    //std::cout << rd << " " << Register[rd];
}

void Or(const std::string &dir) {
    //std::cout << "or" << "\t";
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    Register[rd] = Register[rs1] | Register[rs2];
    //std::cout << rd << " " << Register[rd];
}

void And(const std::string &dir) {
    //std::cout << "and" << "\t";
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    Register[rd] = Register[rs1] & Register[rs2];
    //std::cout << rd << " " << Register[rd];
}

void Slli(const std::string &dir) {
    //std::cout << "slli" << "\t";
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    Register[rd] = ((unsigned) Register[rs1]) << rs2;
    //std::cout << rd << " " << Register[rd];
}

void Srli(const std::string &dir) {
    //std::cout << "srli" << "\t";
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    Register[rd] = ((unsigned) Register[rs1]) >> rs2;
    //std::cout << rd << " " << Register[rd];
}

void Srai(const std::string &dir) {
    //std::cout << "srai" << "\t";
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    Register[rd] = ((int) Register[rs1]) >> rs2;
    //std::cout << rd << " " << Register[rd];
}

void Sll(const std::string &dir) {
    //std::cout << "sll" << "\t";
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    int move = Binary_Decimal(Decimal_Binary5(Register[rs2]));
    Register[rd] = ((unsigned) Register[rs1]) << move;
    //std::cout << rd << " " << Register[rd];
}

void Slt(const std::string &dir) {
    //std::cout << "slt" << "\t";
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    if (Register[rs1] < Register[rs2])Register[rd] = 1;
    else Register[rd] = 0;
    //std::cout << rd << " " << Register[rd];
}

void Sltu(const std::string &dir) {
    //std::cout << "sltu" << "\t";
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    if (((unsigned) Register[rs1]) < ((unsigned) Register[rs2]))
        Register[rd] = 1;
    else Register[rd] = 0;
    //std::cout << rd << " " << Register[rd];
}

void Srl(const std::string &dir) {
    //std::cout << "srl" << "\t";
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    int move = Binary_Decimal(Decimal_Binary5(Register[rs2]));
    Register[rd] = ((unsigned) Register[rs1]) >> move;
    //std::cout << rd << " " << Register[rd];
}

void Sra(const std::string &dir) {
    //std::cout << "sra" << "\t";
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    int move = Binary_Decimal(Decimal_Binary5(Register[rs2]));
    Register[rd] = ((int) Register[rs1]) >> move;
    //std::cout << rd << " " << Register[rd];
}

void Slti(const std::string &dir) {
    //std::cout << "slti" << "\t";
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    if (Register[rs1] < Decode(imm))Register[rd] = 1;
    else Register[rd] = 0;
    //std::cout << rd << " " << Register[rd];
}

void Sltiu(const std::string &dir) {
    //std::cout << "sltiu" << "\t";
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    if (((unsigned) Register[rs1]) < ((unsigned) Decode(imm)))
        Register[rd] = 1;
    else Register[rd] = 0;
    //std::cout << rd << " " << Register[rd];
}

void Add(const std::string &dir) {
    //std::cout << "add" << "\t";
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    Register[rd] = Register[rs1] + Register[rs2];
    //std::cout << rd << " " << Register[rd];
}

void Sub(const std::string &dir) {
    //std::cout << "sub" << "\t";
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    Register[rd] = Register[rs1] - Register[rs2];
    //std::cout << rd << " " << Register[rd];
}

void Addi(const std::string &dir) {
    //std::cout << "addi" << "\t";
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    Register[rd] = Register[rs1] + Decode(imm);
    //std::cout << rd << " " << Register[rd];
}

#endif //UNTITLED4_RISC_V32_H
