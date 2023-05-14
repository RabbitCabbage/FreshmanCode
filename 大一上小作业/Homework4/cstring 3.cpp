

#include <bits/stdc++.h>

#include "src.hpp"

using namespace std;


//---------------------------------------
int n;
char s1[2000000], s2[100];
int main(){
    ios::sync_with_stdio(0),cin.tie(0);

    int op;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> op >> s1 >> s2;
        char *token = strtok(s1, s2);
        while(token != nullptr) {
            if (*token == '\0') cout << "empty str\n";
            else cout << token << '\n';
            token = strtok(nullptr, s2);
        }
    }

    return 0;
}














//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);


