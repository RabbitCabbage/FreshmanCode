//
// Created by lu'ren'jia'd's on 2022/3/30.
//

#include <iostream>

using namespace std;
int n, m;

int main() {
    scanf("%d%d", &n, &m);
    int ai;
    int total = 1;//there has already been a node;
    int ch[32 * (n + 10)][2];
    int value[32 * (n + 10)];
    ch[0][0] = ch[0][1] = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &ai);
        int u = 0;
        for (int j = 31; j >= 0; --j) {
            int v = (ai >> j) & 1;
            if (ch[u][v] == 0) {
                ch[u][v] = total;
                ch[total][0] = ch[total][1] = 0;
                value[total] = 0;
                ++total;
            }
            u = ch[u][v];
        }
        value[u]=ai;
    }
    for (int i = 0; i < m; ++i) {
        int q,u=0;
        scanf("%d", &q);
        for (int j = 31; j >= 0; --j) {
            int v = (q >> j) & 1;
            bool result = v^1;
            if(ch[u][result])u=ch[u][result];
            else u=ch[u][!result];
        }
        printf("%d%c",value[u]^q,'\n');
    }
    return 0;
}