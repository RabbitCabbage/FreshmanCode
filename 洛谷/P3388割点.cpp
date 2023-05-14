//
// Created by lu'ren'jia'd's on 2022/5/29.
//

#include <iostream>
#include <cstring>

using namespace std;
int n, m;
const int maxn = 2e4 + 5;
const int maxm = 1e5 + 5;
struct edge {
    int to, nxt;
} e[maxm << 1];
int total = 0;
int first[maxn];

void add(int from, int to) {
    total++;
    e[total].to = to;
    e[total].nxt = first[from];
    first[from] = total;
}

int cnt = 0;
int dfn[maxn], low[maxn];
int stack[maxn];
int top = -1;
bool cut[maxn];
int cutn = 0;
int son = 0;

void tarjan(int u, int root) {
    dfn[u] = low[u] = ++cnt;
    stack[++top] = u;//进栈
    for (int i = first[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (dfn[v])low[u] = min(low[u], dfn[v]);
        else {
            if (u == root)son++;//随时统计下每次dfs根节点的孩子数目，
            tarjan(v, root);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u])//说明这个孩子v他没有一条返祖边，u就是个割点
            {
                if (!cut[u]) {
                    cut[u] = true;
                    cutn++;
                }
                //如果要统计点双的的话，这里点双的个数就会++，
                //并且可以记下点双的大小和组成点
                while (1) {
                    int destack = stack[top--];
                    if (destack == v)break;
                }
                if (u == root && son <= 1) {
                    cut[u] = false;
                    cutn--;
                }
            }
        }
    }
}

int main() {
    memset(first, 0, sizeof(first));
    memset(cut, false, sizeof(cut));
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        add(v, u);
        add(u, v);
    }
    for (int i = 1; i <= n; ++i) {
        son = 0;
        tarjan(i, i);
    }
    printf("%d\n", cutn);
    for (int i = 1; i <= n; ++i) {
        if (cut[i])printf("%d ", i);
    }
    printf("%c", '\n');
    return 0;
}