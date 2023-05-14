#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int num = 1, i = 0;
    for (num = 1; num <= 2018; num++)
        if (num % 10 == 8 || num % 100 / 10 == 8 || num % 1000 / 100 == 8)
            ++i;
    cout << "含有8的数共有" << i << "个" << endl;
    return 0;
}