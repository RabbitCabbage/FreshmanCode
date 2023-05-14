#include <iostream>
#include <cstring>

using namespace std;

int n;

int *&funA(int **&p);

int *&funB(int array[], int **p, int **q);

int main() {
    int a[100], b[100], c[100];
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        cin >> b[i];
    int **p, **q;
    funA(p) = a;
    funA(q) = b;
    funB(c, p, q);
    for (int i = 0; i < n; ++i)
        cout << c[i] << " ";
    return 0;

}

int *&funA(int **&p) {//这里要用引用传递，这样才能对p进行写的操作
    p = new int *;//如果用*p=new int；相当于是p的第二级指向了new的数组，p的第一级并没有初始化，那么你此时*p就会出问题
    return (*p);
};

int *&funB(int array[], int **p, int **q) {
    for (int i = 0; i < n; ++i) {
        array[i] = ((*p)[i]) * ((*q)[i]);
    }
    delete p;
    delete q;
    return array;
};
//
// Created by lu'ren'jia'd's on 2021/11/15.
//

