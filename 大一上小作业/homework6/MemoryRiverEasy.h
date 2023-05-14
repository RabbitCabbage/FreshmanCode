//
// Created by lu'ren'jia'd's on 2021/12/2.
//

#ifndef UNTITLED4_MEMORYRIVEREASY_H
#define UNTITLED4_MEMORYRIVEREASY_H

#include <fstream>
#include <string>
#include <set>
#include <iostream>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

template<class T, int info_len = 2>
class MemoryRiver {
private:
    /* your code here */
    fstream file;
    string file_name;
    int sizeofT = sizeof(T);
public:
    MemoryRiver() {
    }

    MemoryRiver(const string &file_name) : file_name(file_name) {
    }


    void initialise(const string &FN = "") {
        if (!FN.empty()) file_name = FN;//为文件命名
        file.open(file_name, std::ios::out);//打开文件写入
        std::cout << file.is_open() << std::endl;//todo
        int tmp = 0;
        for (int i = 0; i < info_len; ++i)//初始化在文件里全部写入0
            file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    //读出第n个int的值赋给tmp，1_base
    void get_info(int &tmp, int n) {
        if (n > info_len) return;
        /* your code here */
        file.open(file_name, std::ios::in);
        file.seekg(n - 1, std::ios::beg);
        file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    //将tmp写入第n个int的位置，1_base
    void write_info(int tmp, int n) {
        if (n > info_len) return;
        /* your code here */
        file.open(file_name, std::ios::out);
        file.seekp(n - 1, std::ios::beg);
        file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    //在文件合适位置写入类对象t，并返回写入的位置索引index
    //位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
    //位置索引index可以取为对象写入的起始位置
    int write(T &t) {
        /* your code here */
        int location;
        file.open(file_name, std::ios::out | std::ios::app);
        location = file.tellp();
        file.write(reinterpret_cast<char *>(&t), sizeof(T));
        file.close();
        return location;//返回是第几个字节
    }

    void update(T &t, const int index) {
        /* your code here */
        file.open(file_name, std::ios::out);
        file.seekp(index, std::ios::beg);
        file.write(reinterpret_cast<char *>(&t), sizeof(T));
        file.close();
    }

    //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
    void read(T &t, const int index) {
        /* your code here */
        file.open(file_name, std::ios::in);
        file.seekg(index, std::ios::beg);
        file.read(reinterpret_cast<char *>(&t), sizeof(T));
        file.close();
    }

    void Delete(int index) {
        /* your code here */
    }

};

#endif
//UNTITLED4_MEMORYRIVEREASY_H
