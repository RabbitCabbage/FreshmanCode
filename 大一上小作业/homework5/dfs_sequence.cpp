#include <bits/stdc++.h>
#define N 100005
using namespace std;

int n, m, dfn[N], cnt, sz[N]//sz子树的大小，cnt计数变量，dfn是区间的端点;
vector<int> G[N];

void dfs(int u, int p) {
    dfn[u] = ++cnt, sz[u] = 1;
    for (int v : G[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

int main() {
#ifdef LOCAL
    freopen(".in", "r", stdin);
#endif

    cin >> n >> m;
    for (int i = 1, u, v; i < n; ++i)
        scanf("%d%d", &u, &v),
                G[u].push_back(v),
                G[v].push_back(u);

    dfs(1, 0);

    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        int l = dfn[v], r = dfn[v] + sz[v] - 1;
        puts(l < dfn[u] && dfn[u] <= r ? "Yes" : "No");
    }

    return 0;
}//
// Created by lu'ren'jia'd's on 2021/11/20.
//

