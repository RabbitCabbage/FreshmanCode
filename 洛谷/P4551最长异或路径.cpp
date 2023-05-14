//
// Created by lu'ren'jia'd's on 2022/5/29.
//

#include <iostream>
#include <cstring>

using namespace std;
int n;
const int maxn = 1e5 + 5;
struct edge {
    int to, nxt;
    int w;
} e[maxn << 1];
int total = 0;
int first[maxn];

void add(int from, int to, int weight) {
    total++;
    e[total].to = to;
    e[total].nxt = first[from];
    e[total].w = weight;
    first[from] = total;
}

int xor_root[maxn];
bool vis[maxn];

void dfs(int u, int fa, int edge_weight) {
    vis[u] = true;
    //它的异或路径相当于是父亲的异或路径异或上父亲到自己的边权
    xor_root[u] = xor_root[fa] ^ edge_weight;
    for (int i = first[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (!vis[v]) {
            dfs(v, u, e[i].w);
        }
    }
}

int ch[32 * maxn][2];
int value[32 * maxn];
int cnt = 0;

void add_number(int x) {
    int u = 0;
    for (int i = 31; i >= 0; --i) {
        int v = (x >> i) & 1;
        if (!ch[u][v]) {
            ch[u][v] = ++cnt;
            ch[cnt][0] = ch[cnt][1] = 0;
        }
        u = ch[u][v];
    }
    value[u] = x;
}

int find_max(int x) {
    int u = 0;
    for (int i = 31; i >= 0; --i) {
        int v = (x >> i) & 1;
        if (ch[u][v ^ 1])u = ch[u][v ^ 1];
        else u = ch[u][v];
    }
    return value[u] ^ x;
}

int main() {
    memset(first, 0, sizeof(first));
    memset(xor_root, 0, sizeof(xor_root));
    memset(value, 0, sizeof(value));
    ch[cnt][0] = ch[cnt][1] = 0;
    memset(vis, false, sizeof(vis));
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        int w;
        scanf("%d %d %d", &u, &v, &w);
        add(v, u, w);
        add(u, v, w);
    }
    dfs(1, 0, 0);
    for (int i = 1; i <= n; ++i)add_number(xor_root[i]);
    int max_ = 0;
    for (int i = 1; i <= n; ++i) {
        max_ = max(max_, find_max(xor_root[i]));
    }
    printf("%d\n", max_);
    return 0;
}