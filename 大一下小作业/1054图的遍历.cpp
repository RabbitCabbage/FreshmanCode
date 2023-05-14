//
// Created by lu'ren'jia'd's on 2022/5/14.
//

#include<iostream>
#include <cstring>

using namespace std;
const int maxn = 1e5 + 5;
const int maxm = 1e5 + 5;
int n, m;
struct edge {
    int to, nxt;
} e[maxm];
int first[maxn];
int total = 0;

void add_edge(int from, int to) {
    total++;
    e[total].to = to;
    e[total].nxt = first[from];
    first[from] = total;
}

int remotest[maxn];
int visited[maxn];

void dfs(int start, int origin) {
    //cout << "dfs " << start << endl;
    for (int i = first[start]; i; i = e[i].nxt) {
        if (!visited[e[i].to]) {
            //cout << "to " << e[i].to << endl;
            if (origin > remotest[e[i].to])remotest[e[i].to] = origin;
            visited[e[i].to] = true;
            dfs(e[i].to, origin);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    memset(visited, false, sizeof(visited));
    memset(first, 0, sizeof(first));
    for (int i = 1; i <= m; ++i) {
        int from, to;
        scanf("%d %d", &to, &from);
        add_edge(from, to);
    }
    for (int i = n; i >= 1; --i)remotest[i] = i;
    for (int i = n; i >= 1; --i)dfs(i, i);
    for (int i = 1; i <= n; ++i)printf("%d ", remotest[i]);
    printf("%c", '\n');
    return 0;
}