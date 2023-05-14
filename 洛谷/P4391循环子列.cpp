//
// Created by lu'ren'jia'd's on 2022/3/5.
//
#include <iostream>
#include <cstring>

using namespace std;
int len;

int main() {
    cin >> len;
    char s1[len + 1];
    cin>>s1;
    int next[len + 1];
    int j = 0, k = -1;
    next[j] = k;

    while (j <= len) {
//        cout << '\n';
//        cout<<j<<" "<<k<<endl;
//        cout<<s1[j]<<" "<<s1[k]<<endl;
        if (k == -1 || s1[j] == s1[k]) {
            ++j, ++k, next[j] = k;
            //因为不能包括自己，所以从真正比较的地方先加加，再去给next赋值
        } else k = next[k];
//        cout << "next" << next[j] << endl;
    }
    cout << len - next[len] << endl;
    return 0;
}
