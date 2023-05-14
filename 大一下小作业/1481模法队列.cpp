//
// Created by lu'ren'jia'd's on 2022/2/27.
//

//cstdio, iostream, cmath, cstring
#include <iostream>

using namespace std;
struct node {
    int left = 0;
    int right = 0;
};
int n, m;

void print(node *);

int main() {
    cin >> n;
    node list[n + 1];
    for (int i = 2; i <= n; ++i) {
        int index, p;
        cin >> index >> p;
        if (p) {
            list[i].right = list[index].right;
            //就算他的左右是零也无所谓，零的那个没有影响
            list[list[index].right].left = i;
            list[index].right = i;
            list[i].left = index;
        } else {
            list[i].left = list[index].left;
            list[list[index].left].right = i;
            list[index].left = i;
            list[i].right = index;
        }
//        print(list);
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int index;
        cin >> index;
        if (list[index].left == 0 && list[index].right == 0)
            continue;
        else if (list[index].left != 0 && list[index].right == 0) {
            list[list[index].left].right = 0;
            list[index].left = 0;
        } else if (list[index].left == 0 && list[index].right != 0) {
            list[list[index].right].left = 0;
            list[index].right = 0;
        } else {
            list[list[index].left].right = list[index].right;
            list[list[index].right].left = list[index].left;
            list[index].right = list[index].left = 0;
        }
//        print(list);
    }
    int i;
    for (i = 1; i <= n; ++i) {
        if (list[i].right != 0 && list[i].left == 0)break;
    }
    if (i == n + 1)cout << endl;
    else {
        while (list[i].right != 0) {
            cout << i << " ";
            i = list[i].right;
        }
        cout << i << endl;
    }
    return 0;
}

void print(node *list) {
    int i;
    cout << "Print" << endl;
    for (i = 1; i <= n; ++i) {
        if (list[i].right != 0 && list[i].left == 0)break;
    }
    if (i == n + 1)cout << endl;
    else {
        while (list[i].right != 0) {
            cout << i << " ";
            i = list[i].right;
        }
        cout << i << endl;
    }
    return;
}