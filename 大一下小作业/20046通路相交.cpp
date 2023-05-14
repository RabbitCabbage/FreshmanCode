//
// Created by lu'ren'jia'd's on 2022/4/4.
//

#include <iostream>
#include <cstring>

using namespace std;
int t, n, m;
const int maxn = 1e5 + 5;
struct node {
    int first = -1;
};
struct edge {
    int to = 0, next = -1;
};
node nl[maxn];
edge el[maxn * 2 - 2];
int tot = 0;

void add(int from, int to) {

    el[tot].to = to;
    el[tot].next = nl[from].first;
    nl[from].first = tot++;
}

int f[maxn][21];
int depth[maxn];
bool visited[maxn];

void dfs(int cur, int fa) {
    depth[cur] = depth[fa] + 1;
    visited[cur] = true;
    f[cur][0] = fa;
    for (int i = 1; i <= 20; ++i) {
        f[cur][i] = f[f[cur][i - 1]][i - 1];
    }
    int nex = nl[cur].first;
    while (nex != -1) {
        if (!visited[el[nex].to])dfs(el[nex].to, cur);
        nex = el[nex].next;
    }
}

int LCA(int x, int y) {
    if (depth[x] < depth[y])swap(x, y);
    for (int i = 20; i >= 0; --i) {
        if (depth[f[x][i]] >= depth[y])x = f[x][i];
    }
    if (x == y)return x;
    for (int i = 20; i >= 0; --i) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

int main() {
    cin >> t;
    for (int j = 0; j < t; ++j) {
        memset(nl, -1, sizeof(nl));
        tot = 0;
        cin >> n >> m;
        for (int i = 1; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            add(x, y);
            add(y, x);
        }
        memset(visited, false, sizeof(visited));
        depth[0] = 0;
        f[1][0] = 0;
        dfs(1, 0);
        for (int i = 0; i < m; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (x1 == x2 || x1 == y2 || y1 == x2 || y1 == y2)cout << "YES" << endl;
            else {
                int lca1 = LCA(x1, y1);
                int lca2 = LCA(x2, y2);
                //lca1 is on x2-y2
                //lca(lca1,x2)==lca1||lca(lca1,y2)==lca2 and the depth of the lca1 < x2 ||lca1 < y2
                if (depth[lca1] >= depth[lca2])//lca1更深，有可能在lca2的路径上
                {
                    if ((LCA(lca1, x2) == lca1 && depth[lca1] >= depth[lca2]) ||
                        (LCA(lca1, y2) == lca1 && depth[lca1] >= depth[lca2]) ||
                        (LCA(lca2, x1) == lca2 && depth[lca2] >= depth[lca1]) ||
                        (LCA(lca2, y1) == lca2 && depth[lca2] >= depth[lca1]))
                        cout << "YES" << endl;
                    else cout << "NO" << endl;
                } else {
                    if ((LCA(lca2, x1) == lca2 && depth[lca2] >= depth[lca1]) ||
                        (LCA(lca2, y1) == lca2 && depth[lca2] >= depth[lca1]) ||
                        (LCA(lca1, x2) == lca1 && depth[lca1] >= depth[lca2]) ||
                        (LCA(lca1, y2) == lca1 && depth[lca1] >= depth[lca2]))
                        cout << "YES" << endl;
                    else cout << "NO" << endl;
                }
            }
        }
    }
    return 0;
}