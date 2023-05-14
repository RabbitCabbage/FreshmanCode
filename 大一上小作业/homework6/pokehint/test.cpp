#include <iostream>
#include "pokedex.hpp"

std::string encode(int num) {
    std::string ret;
    while (num) {
        ret += (char)(num%26 + 'a');
        num /= 26;
    }
    return "pm" + ret;
}

std::string TYPES[] = {"water", "fire", "grass", "electric", "flying", "ground", "dragon"};

static int EXPAND = 10000;

int main() {
    try {
        static int ROUND_ADD = 40, ROUND_DEL = 10, ROUND_TOTAL = 30;
        Pokedex pokedex("pokedex");
        for (int i = 1; i <= ROUND_ADD; i++) {
            int id = (1 - 1) * ROUND_TOTAL + i;
            std::string name = encode(id);
            int type1 = (id * 23 + id * 7 + (id ^ 255)) % 7;
            int type2 = (id * 11 + id * 13 + (id ^ 133)) % 7;
            int type3 = (id * 3 + id * 777 + (id ^ 513)) % 7;
            if (type2 == type1) {
                type2 = (type2 + 1) % 7;
            }
            while (type3 == type2 || type3 == type1) {
                type3 = (type3 + 1) % 7;
            }
            std::cout << pokedex.pokeAdd(name.c_str(), id * EXPAND,
                                         (TYPES[type1] + "#" + TYPES[type2] + "#" + TYPES[type3]).c_str()) << '\n';
        }

        for (int i = 1; i <= ROUND_TOTAL * (1 - 1) + ROUND_ADD; i++) { //40*(n-1) + 50
            std::cout << pokedex.pokeFind(i * EXPAND) << '\n';
        }

        for (int i = ROUND_TOTAL * (1 - 1) + ROUND_ADD - ROUND_DEL + 1; i <= ROUND_TOTAL * (1 - 1) + ROUND_ADD; i++) {
            //std::cout << "delete " << i << '\n';
            std::cout << pokedex.pokeDel(i * EXPAND) << '\n'; // delete
        }

        for (int i = 1; i <= ROUND_TOTAL * (1 - 1) + ROUND_ADD; i++) { //40*(n-1) + 50, Not Founded
            std::cout << pokedex.pokeFind(i * EXPAND) << '\n';
            for (int j = 0; j < 7; ++j) {
                std::cout << pokedex.attack(TYPES[j].c_str(), i * EXPAND) << '\n';
            }
        }

        for (int j = 0; j < 7; ++j) {
            std::cout << pokedex.typeFind(TYPES[j].c_str()) << '\n';
        }

        std::cout << pokedex.catchTry() << '\n';

    } catch (...) {
        std::cout << "Wrong Throw!\n";
    }
}