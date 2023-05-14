//
// Created by lu'ren'jia'd's on 2022/5/18.
//
#include <iostream>
#include <cstring>
#include <random>
#include "BPlusTree.h"

int main() {
    system("rm ../data/index\n");
    system("rm ../data/record\n");
    clock_t sts = clock();

    ds::BPlusTree<int, int> a("../data/index", "../data/record");
    ds::BPlusTree<int, int>::iterator ptr(&a);

    for (int i = 0; i < 25; ++i) {
        std::cout << a.Insert(i, i) << std::endl;
    }
    std::cout << "hello" << std::endl;
    for (int i = 0; i < 80; ++i) {
        std::cout << a.Insert(i, i) << std::endl;
    }
    std::cout << "hello" << std::endl;
    for (int i = 81; i < 100; ++i) {
        std::cout << a.Remove(i) << std::endl;
    }
//    int i;
//    std::cout << "================traverse==============" << std::endl;
//    for (ptr = a.FindBigger(0), i = 0; i < 25; ++i, ++ptr)
//        std::cout << (*ptr).first << " " << (*ptr).second << std::endl;
//    for (int i = 0; i < 25; ++i) {
//        a.Modify(i, 500);
//        std::cout << a.GetSize() << std::endl;
//    }
//    for (ptr = a.FindBigger(0), i = 0; i < 25; ++i, ++ptr)
//        std::cout << (*ptr).first << " " << (*ptr).second << std::endl;
//    for (int j = 0; j < 25; ++j) {
//        a.Remove(j);
//        std::cout << a.GetSize() << std::endl;
//    }
//    a.Clear();
//    std::cout << a.GetSize() << std::endl;
//    for (int j = 0; j < 25; ++j)
//        std::cout << a.Remove(j) << " " << std::endl;
//        ptr = a.FindBigger(29);
//        std::cout << (ptr.AtEnd() ? "at end" : "not at end") << std::endl;
//        clock_t end = clock();
//        std::cout << (end - sts) / CLOCKS_PER_SEC << std::endl;
    return 0;
}