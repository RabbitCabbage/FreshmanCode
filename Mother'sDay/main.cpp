#include <iostream>
#include <string>
#include "contol.h"
#include "tool.h"

int Register[32];
int Memory[500000];
int Current = 0;

int main() {
    ReadCommand();
    while (1) {
        std::string machine_code16 = Parser();
        if (machine_code16 == "0FF00513")break;
        std::string machine_code2 = Hex_Binary(machine_code16);
        //std::cout << machine_code2 << "\t";
        Trans(machine_code2);
        //std::cout << std::endl;
        Register[0] = 0;
    }
    std::cout << (Register[10] & 255u) << std::endl;
    return 0;
}