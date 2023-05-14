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
        cin >> op >> s1 >> s2;
        if (op == 1) {
            cout << strcspn(s1.c_str(), s2.c_str()) << '\n';
        } else if (op == 2) {
            const char *res = strstr(s1.c_str(), s2.c_str());
            if (res == nullptr) cout << "NOT FOUND\n";
            else cout << res << '\n';
        }
    }

    return 0;
}














//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
