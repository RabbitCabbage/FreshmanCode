//
// Created by lu'ren'jia'd's on 2022/5/31.
//

#include "MemoryRiver.h"
#include <iostream>

int main() {
    ds::MemoryRiver<double> m("hello");
    double t;
    for (int i = 0; i < 3; ++i) {
        m.Read(i * sizeof(double), t);
        std::cout << t << std::endl;
    }
    return 0;
}
//    m.Write(0, 5.5555);
//    m.Write(8, 6.6666);
//    m.Append(7.7777);

//m.Read(0, t);
//    std::cout << t << std::endl;
//    m.Write(0, 4.4444);
//    m.Read(0, t);
//    std::cout << t << std::endl;
//    m.Read(8, t);
//    std::cout << t << std::endl;
//    m.Write(8, 4.4444);
//    m.Read(8, t);
//    std::cout << t << std::endl;
//    m.Read(16, t);
//    std::cout << t << std::endl;
//    m.Write(16, 4.4444);
//    m.Read(16, t);
//    std::cout << t << std::endl;