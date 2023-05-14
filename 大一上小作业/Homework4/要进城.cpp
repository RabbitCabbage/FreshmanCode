//
// Created by lu'ren'jia'd's on 2021/11/3.
//

#include <iostream>
#include <string>
#include <set>

using namespace std;
set<string> sorting;

int jiecheng(int n);

int k;

void list_all(string initial, int l, int r, string array[]);

int main() {
    string initial;
    cin >> initial;
    k = jiecheng(initial.length());//string num=k;
    string array[k];
    int length = initial.length();
    list_all(initial, 0, length-1, array);
    for (int h = 0; h < k; ++h) {
        sorting.insert(array[h]);
    }
    auto pointer = sorting.begin();
    int query;
    cin >> query;
    for (int j = 1; j < query; j++) {
        pointer++;
    }
    cout << *pointer << endl;
    return 0;
}

int jiecheng(int n) {
    int result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

void list_all(string initial, int l, int r, string array[]) {
    static string ss=initial;
    static int i = 0;
    if (l == r && i < k) {
        array[i] = ss;
        ++i;
    } else {
        for (int j = l; j <= r; ++j) {
            swap(ss[j], ss[l]);
            list_all(ss, l + 1, r, array);
            swap(ss[j], ss[l]);

        }
    }
}