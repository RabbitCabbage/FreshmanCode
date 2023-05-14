//
// Created by lu'ren'jia'd's on 2022/6/1.
//
#include <iostream>
#include "BPlusTree.h"
#include "CacheMap.h"

using namespace std;


int main() {
//    system("rm ./index_file1\n");
//    system("rm ./record_file1\n");
//    system("rm ./index_file2\n");
//    system("rm ./record_file2\n");
    ds::CacheMap<int, int> map("index_file1", "record_file1");
    ds::BPlusTree<int, int> tree("index_file2", "record_file2");
    int i = 200;
    while (i--) {
        int key = rand() % 1000;
        int info = rand() % 3000;
        map.Insert(key, info);//返回值还是Insert有没有成功
        tree.Insert(key, info);
        auto i1 = map.Find(key);
        auto i2 = tree.Find(key);
        //还是分别为Find是否成功，key, info
        std::cout << i1.first << i1.second.first << i1.second.second << std::endl;
        map.Remove(key); //返回值还是Remove有没有成功
        tree.Remove(key);
    }
    for (auto p = tree.FindBigger(0); !p.AtEnd(); ++p) {
        std::cout << (*p).first << (*p).second << std::endl;
    }
    for (auto q = map.tree->FindBigger(0); !q.AtEnd(); ++q) {
        std::cout << (*q).first << (*q).second << std::endl;
    }
    return 0;
}
