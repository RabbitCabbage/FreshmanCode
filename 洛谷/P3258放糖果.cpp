//
// Created by lu'ren'jia'd's on 2022/4/3.
//

#include <iostream>
#include <cstring>

using namespace std;
const int maxn = 3e5 + 5;
const int maxe = 2 * maxn - 1;
struct edge {
    int to = 0;
    int next_edge_index = -1;
};
struct node {
    int father = 0;
    int first_edge_index = -1;
    int candy = 0;
};
node node_list[maxn];
edge edge_list[maxe];

void add(int from, int to) {
    static int total = 0;
    edge_list[total].to = to;
    edge_list[total].next_edge_index = node_list[from].first_edge_index;
    node_list[from].first_edge_index = total++;
}

bool visited[maxn]{false};
int depth[maxn];
int f[maxn][21];

void dfs(int cur, int fa) {
    node_list[cur].father = fa;
    depth[cur] = depth[fa] + 1;
    visited[cur] = true;
    f[cur][0] = fa;
//    cout<<"cur"<<cur<<endl;
    for (int i = 1; i <= 20; ++i) {
        f[cur][i] = f[f[cur][i - 1]][i - 1];
    }
    int next_edge = node_list[cur].first_edge_index;
    while (next_edge != -1) {
        if (!visited[edge_list[next_edge].to])dfs(edge_list[next_edge].to, cur);
        next_edge = edge_list[next_edge].next_edge_index;
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

int sum[maxn];

void sum_up(int cur) {
    visited[cur] = true;
    sum[cur] = node_list[cur].candy;
    int next_edge = node_list[cur].first_edge_index;
    while (next_edge != -1) {
        if (!visited[edge_list[next_edge].to]) {
            sum_up(edge_list[next_edge].to);
            sum[cur] += sum[edge_list[next_edge].to];
        }
        next_edge = edge_list[next_edge].next_edge_index;
    }
}

int n;

int main() {
    cin >> n;
    int sequence[n];
    for (int i = 0; i < n; ++i)cin >> sequence[i];
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }
    depth[0] = 0;
    f[1][0] = 0;
    dfs(1, 0);
    node_list[0].candy += 1;
    for (int i = 1; i <= n - 1; ++i) {
        int start = sequence[i - 1], end = sequence[i];
        int lca = LCA(start, end);
//        cout << "两个点是 " << start << " " << end << " 公共祖先是 " << lca << endl;
        node_list[start].candy += 1;
        node_list[end].candy += 1;
        node_list[lca].candy -= 1;
        node_list[node_list[lca].father].candy -= 1;
    }
//    for (int i = 1; i <= n; ++i)cout << node_list[i].candy << " ";
//    for (int i = 1; i <= n; ++i)cout << sum[i] << " ";
//    cout << endl;
    memset(visited, false, sizeof(visited));
    sum_up(1);
    for (int i = 1; i <= n - 1; ++i)sum[sequence[i]]--;
    for (int i = 1; i <= n; ++i)cout << sum[i] << endl;
    return 0;
}