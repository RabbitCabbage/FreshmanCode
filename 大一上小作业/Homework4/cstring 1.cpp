#include <bits/stdc++.h>

#include "src.hpp"

using namespace std;

//---------------------------------------
int n;
int main(){
    ios::sync_with_stdio(0),cin.tie(0);

    string s1, s2;
    int op;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> op >> s1;
        if (op == 1) {
            cin >> s2;
            cout << strcmp(s1.c_str(), s2.c_str()) << '\n';
        } else if (op == 2) {
            char *arr = new char[s1.length() + 1];
            cout << strcpy(arr, s1.c_str()) << '\n';
            delete[] arr;
        } else if (op == 3) {
            //s1 shouldn't be too short
            char *arr = new char[s1.length() * 2 + 1];
            arr[0] = 'w';
            arr[1] = '\0';
            const char *tmp = s1.c_str();
            char *to = arr + s1.length();
            while(*tmp) {
                *to = *tmp;
                ++to, ++tmp;
            }
            *to = 0;
            cout << strcpy(arr, arr + s1.length()) << '\n';
            delete[] arr;
        } else if (op == 4) {
            cout << strcpy((char*)s1.c_str() + s1.length() - 3, s1.c_str()) << '\n';
        }

    }

    return 0;
}














//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
