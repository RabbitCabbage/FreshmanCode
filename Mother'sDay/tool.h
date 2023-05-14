//
// Created by lu'ren'jia'd's on 2022/6/23.
//

#ifndef UNTITLED4_TOOL_H
#define UNTITLED4_TOOL_H

#include <string>
#include <iostream>

extern int Register[32];
extern int Memory[500000];
extern int Current;

int Binary_Decimal(const std::string& b_number) {
    int number = 0;
    for (int i = b_number.length() - 1, j = 0; i >= 0; --i, ++j) {
        number += (b_number[i] - '0') * (1 << j);
    }
    return number;
}

int Hex_Decimal(const std::string& h_number) {
    int number = 0;
    for (int i = h_number.length() - 1, j = 0; i >= 0; --i, ++j) {
        if ('0' <= h_number[i] && h_number[i] <= '9') number += (h_number[i] - '0') * (1 << (4 * j));
        else number += (h_number[i] - 'A' + 10) * (1 << (4 * j));
    }
    return number;
}

std::string Decimal_Hex(int number) {
    std::string h_number;
    h_number.clear();
    while (number != 0) {
        int bit = number % 16;
        if (bit < 10) h_number = (char) ('0' + bit) + h_number;
        else h_number = (char) ('A' + bit - 10) + h_number;
        number /= 16;
    }
    if (h_number == "")return h_number = "0";
    return h_number;
}

std::string Hex_Binary(const std::string& h_number) {
    int number = Hex_Decimal(h_number);
//    ////std::cout << number << std::endl;
    std::string b_number;
    b_number.clear();
    for (int i = 31; i >= 0; --i) {
//        ////std::cout << ((number >> i) & 1) << std::endl;
        b_number += (char) ('0' + (int) ((number >> i) & 1));
    }
    return b_number;
}

std::string Decimal_Binary32(const int& number) {
    std::string b_number;
    b_number.clear();
    for (int i = 31; i >= 0; --i) {
//        ////std::cout << ((number >> i) & 1) << std::endl;
        b_number += (char) ('0' + (int) ((number >> i) & 1));
    }
    return b_number;
}

std::string Decimal_Binary16(const int& number) {
    std::string b_number;
    b_number.clear();
    for (int i = 15; i >= 0; --i) {
//        ////std::cout << ((number >> i) & 1) << std::endl;
        b_number += (char) ('0' + (int) ((number >> i) & 1));
    }
    return b_number;
}

std::string Decimal_Binary8(const int& number) {
    std::string b_number;
    b_number.clear();
    for (int i = 7; i >= 0; --i) {
//        ////std::cout << ((number >> i) & 1) << std::endl;
        b_number += (char) ('0' + (int) ((number >> i) & 1));
    }
    return b_number;
}

std::string Decimal_Binary5(const int& number) {
    std::string b_number;
    b_number.clear();
    for (int i = 4; i >= 0; --i) {
//        ////std::cout << ((number >> i) & 1) << std::endl;
        b_number += (char) ('0' + (int) ((number >> i) & 1));
    }
    return b_number;
}

//这个目的就是符号扩展然后转补码变成数字
int Decode(std::string code) {
    if (code.length() < 32) {
        int len = code.length();
        std::string extend;
        extend.clear();
        if (code[0] == '0') {
            for (int i = 0; i < 32 - len; ++i)extend += "0";
        } else {
            for (int i = 0; i < 32 - len; ++i)extend += "1";
        }
        code = extend + code;
    }
    for (int i = 0; i < code.length(); ++i) {
        if (code[i] == '0')code[i] = '1';
        else code[i] = '0';
    }
    long long reverse = Binary_Decimal(code);
    long long x = reverse * (-1) - 1;
    if (x >= 2147483648)x -= 4294967296;
    return (int) x;
}

int DecodeZeroExtend(std::string code) {
    if (code.length() < 32) {
        int len = code.length();
        std::string extend;
        extend.clear();
        for (int i = 0; i < 32 - len; ++i)extend += "0";
        code = extend + code;
    }
    for (int i = 0; i < code.length(); ++i) {
        if (code[i] == '0')code[i] = '1';
        else code[i] = '0';
    }
    long long reverse = Binary_Decimal(code);
    long long x = reverse * (-1) - 1;
    if (x >= 2147483648)x -= 4294967296;
    return (int) x;
}

void R_Type(const std::string &dir, int &rs2, int &rs1, int &rd) {
    rs2 = Binary_Decimal(dir.substr(7, 5));
    rs1 = Binary_Decimal(dir.substr(12, 5));
    rd = Binary_Decimal(dir.substr(20, 5));
    ////std::cout << "rs1 = " << rs1 << " ";
    ////std::cout << "rs2 = " << rs2 << " ";
    ////std::cout << "rd = " << rd;
}

void I_Type(const std::string &dir, std::string &imm, int &rs1, int &rd) {
    imm = dir.substr(0, 12);
    rs1 = Binary_Decimal(dir.substr(12, 5));
    rd = Binary_Decimal(dir.substr(20, 5));
    ////std::cout << "rs1 = " << rs1 << " ";
    ////std::cout << "rd = " << rd << " ";
    ////std::cout << "imm = " << Decode(imm);
}

void S_Type(const std::string &dir, std::string &imm, int &rs1, int &rs2) {
    imm = dir.substr(0, 7) + dir.substr(20, 5);
    rs2 = Binary_Decimal(dir.substr(7, 5));
    rs1 = Binary_Decimal(dir.substr(12, 5));
    ////std::cout << "rs1 = " << rs1 << " ";
    ////std::cout << "rs2 = " << rs2 << " ";
    ////std::cout << "imm = " << Decode(imm);
}

void B_Type(const std::string &dir, std::string &imm, int &rs1, int &rs2) {
    imm = dir.substr(0, 1) + dir.substr(24, 1) + dir.substr(1, 6) + dir.substr(20, 4) + "0";
    rs2 = Binary_Decimal(dir.substr(7, 5));
    rs1 = Binary_Decimal(dir.substr(12, 5));
    ////std::cout << "rs1 = " << rs1 << " ";
    ////std::cout << "rs2 = " << rs2 << " ";
    ////std::cout << "imm = " << Decode(imm);
}

void U_Type(const std::string &dir, std::string &imm, int &rd) {
    imm = dir.substr(0, 20);
    rd = Binary_Decimal(dir.substr(20, 5));
    ////std::cout << "rd = " << rd << " ";
    ////std::cout << " imm = " << imm;
}

void J_Type(const std::string &dir, std::string &imm, int &rd) {
    imm = dir.substr(0, 1) + dir.substr(12, 8) + dir.substr(11, 1) + dir.substr(1, 10) + "0";
    rd = Binary_Decimal(dir.substr(20, 5));
    ////std::cout << "rd = " << rd << " jump to" << Decimal_Hex(Binary_Decimal(imm) + Current - 4);
}


#endif //UNTITLED4_TOOL_H
