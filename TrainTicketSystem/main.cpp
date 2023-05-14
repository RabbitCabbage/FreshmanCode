#include <iostream>
#include "BPlusTree.h"
#include "CacheMap.h"

using namespace std;


int main() {
    system("rm ./index_file1\n");
    system("rm ./record_file1\n");
    system("rm ./index_file2\n");
    system("rm ./record_file2\n");
    ds::CacheMap<int, int> right_("index_file1", "record_file1");
    ds::BPlusTree<int, int> tree("index_file2", "record_file2");
    int i = 8000;
    while (i--) {
        int key = rand() % 50;
        int info = rand() % 30000;
        right_.Insert(key, info);
        tree.Insert(key, info);
    }
    i = 8000;
    while (i--) {
        int key = rand() % 50;
        int info = rand() % 3000;
        if (right_.Modify(key, info) != tree.Modify(key, info))std::cout << "Error Modify" << std::endl;
    }
    right_.Flush();
    auto p = tree.FindBigger(0);
    auto q = right_.tree->FindBigger(0);
    for (; !p.AtEnd(); ++p, ++q) {
        if ((*p).second != (*q).second)std::cout << "Iterator Error" << endl;
//        else std::cout << "quq" << std::endl;
    }
    return 0;
}
//i = 1000;
//    while (i--) {
//        int op = rand() % 3;
//        if (op == 0) {
//            int key = rand() % 1000;
//            int info = rand() % 3000;
//            right_.Insert(key, info);
//            tree.Insert(key, info);
//        }
//        if (op == 1) {
//            int key = rand() % 1000;
//            auto i1 = right_.Find(key);
//            auto i2 = tree.Find(key);
//            if (i2.first != i1.first)std::cout << "Error Find First" << std::endl;
////            else std::cout << "quq" << std::endl;
//            if (i2.first) {
//                if (i1.second.second != i2.second.second)std::cout << "Error Find Second" << std::endl;
////                else std::cout << "quq" << std::endl;
//            }
//        }
//        if (op == 2) {
//            int key = rand() % 2000;
//            if (right_.Remove(key) != tree.Remove(key))std::cout << "Error Remove" << std::endl;
//        }
//    }
/*a.Insert(11, 111111);
    std::cout << a.Find(11).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Insert(6, 666);
    std::cout << a.Find(6).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Insert(12, 121212);
    std::cout << a.Find(12).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Insert(3, 10003);
    std::cout << a.Find(3).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Insert(8, 888);
    std::cout << a.Find(8).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Insert(7, 777);
    std::cout << a.Find(7).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Insert(13, 131313);
    std::cout << a.Find(13).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Insert(2, 222);
    std::cout << a.Find(2).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Insert(14, 141414);
    std::cout << a.Find(14).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Insert(1, 111);
    std::cout << a.Find(1).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Insert(15, 151515);
    std::cout << a.Find(15).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Insert(4, 444);
    std::cout << a.Find(4).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Insert(10, 101010);
    std::cout << a.Find(10).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Insert(9, 999);
    std::cout << a.Find(9).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Insert(16, 161616);
    std::cout << a.Find(16).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Insert(5, 555);
    std::cout << a.Find(5).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    ds::BPlusTree<int, int>::iterator ptr(&a);
    int i;
    std::cout << "================traverse==============" << std::endl;
    for (ptr = a.FindBigger(3), i = 0; i < 7; ++i, ++ptr)std::cout << (*ptr).first << " " << (*ptr).second << std::endl;

    a.Remove(2);
    std::cout << a.Find(2).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Remove(3);
    std::cout << a.Find(3).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Remove(6);
    std::cout << a.Find(6).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Remove(7);
    std::cout << a.Find(7).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    //done
    a.Remove(8);
    std::cout << a.Find(8).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Remove(11);
    std::cout << a.Find(11).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Remove(12);
    std::cout << a.Find(12).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Remove(13);
    std::cout << a.Find(13).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Remove(1);
    std::cout << a.Find(1).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;

    std::cout << "================traverse==============" << std::endl;
    for (ptr = a.FindBigger(3), i = 0; i < 7; ++i, ++ptr)std::cout << (*ptr).first << " " << (*ptr).second << std::endl;

    a.Remove(4);
    std::cout << a.Find(4).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Remove(15);
    std::cout << a.Find(15).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Remove(5);
    std::cout << a.Find(5).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Remove(9);
    std::cout << a.Find(9).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Remove(16);
    std::cout << a.Find(16).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Remove(10);
    std::cout << a.Find(10).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;
    a.Remove(14);
    std::cout << a.Find(14).second.second << std::endl;
    std::cout << "size " << a.GetSize() << std::endl;*/
