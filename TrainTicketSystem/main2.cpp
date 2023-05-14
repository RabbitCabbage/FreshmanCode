//
// Created by lu'ren'jia'd's on 2022/5/18.
//

#include <iostream>
#include "BPlusTree.h"

int main() {
    system("rm index\n");
    system("rm record\n");
    ds::BPlusTree<int, int> a("index", "record");
    ds::BPlusTree<int, int>::iterator ptr(&a);
    for (int i = 0; i < 3000; ++i) {
        a.Insert(i, i);
        std::cout << a.GetSize() << std::endl;
    }
    int i;
    std::cout << "================traverse==============" << std::endl;
    for (ptr = a.FindBigger(0), i = 0; i < 50; ++i, ++ptr)
        std::cout << (*ptr).first << " " << (*ptr).second << std::endl;
    for (int j = 0; j < 1000; ++j) {
        a.Remove(j);
        std::cout << a.GetSize() << std::endl;
    }
    return 0;
}