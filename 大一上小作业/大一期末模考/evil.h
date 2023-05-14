//
// Created by Administrator on 2021/12/6.
//

#ifndef UNTITLED4_EVIL_HPP
#define UNTITLED4_EVIL_HPP
#ifndef EVIL_HPP
#define EVIL_HPP

#include <iostream>

using namespace std;

class Evil {
private:
    int st, ed, val;
    int *data;

public:

    //构造函数
    Evil(int start, int end, int value) {
        st = start;
        ed = end;
        val = value;
        data = new int[ed - st + 1];
        for (int i = 0; i < ed - st + 1; ++i)data[i] = 0;
    }

    Evil() {
        st = 0;
        ed = 0;
        val = 0;
        data = new int[1];
        data[0] = 0;
    }

    //下标运算符重载
    int &operator[](int p) {
        if (p < st || p > ed)return data[0];
        else return data[p - st];
    }

    //赋值运算符重载
    Evil &operator=(const Evil &e) {
        if(&e==this)return *this;
        st = e.st;
        ed = e.ed;
        val = e.val;
        delete[]data;
        data = new int[e.ed - e.st + 1];
        for (int i = 0; i < e.ed - e.st + 1; ++i) {
            data[i] = e.data[i];
        }
        return *this;
    }

    //前缀++重载
    Evil &operator++() {
        this->val++;
        return *this;
    }

    //后缀++重载
    Evil &operator++(int x) {
        Evil a(st,ed,val);
        a=*this;
        this->val++;
        return a;
    }

    //输出重载
    void Print() {
        cout << val << " ";
        for (int i = 0; i < ed - st + 1; ++i)
            cout << data[i] << " ";
        cout << endl;
    }

    friend ostream &operator<<(ostream &os, const Evil &evil) {
        os << evil.val;
        for (int i = 0; i < evil.ed - evil.st + 1; ++i) {
            os << " " << evil.data[i];
        }
        os << '\n';
        return os;
    }

    //析构函数
    ~Evil() {
        delete[]data;
    }
};

#endif//EVIL_HPP
#endif //UNTITLED4_EVIL_HPP