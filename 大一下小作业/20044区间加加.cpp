//
// Created by lu'ren'jia'd's on 2022/3/31.
//

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;
struct node {
    int milk_tea = 0;
    int first_edge_index = -1;
};
struct edge {
    int from, to;
    int next_edge_index = -1;
};
node node_list[100005];
edge edge_list[200008];
int depth[100005];
int f[100005][21]{0};
bool visited[100005]{false};
int n, k;

void dfs(int cur, int fa) {
    visited[cur] = true;
    depth[cur] = depth[fa] + 1;
    f[cur][0] = fa;
    for (int i = 1; i <= 20; ++i) {
        f[cur][i] = f[f[cur][i - 1]][i - 1];
        //cout<<cur<<" 's "<<pow(2,i)<<" father is "<<f[cur][i]<<endl;
    }
    int next_edge = node_list[cur].first_edge_index;
    while (next_edge != -1) {
        if (!visited[edge_list[next_edge].to]) dfs(edge_list[next_edge].to, cur);
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

int sum[100005];
int result = 0;

void dfs_sum(int cur) {
    visited[cur] = true;
    sum[cur] = node_list[cur].milk_tea;
    int next_edge = node_list[cur].first_edge_index;
    while (next_edge != -1) {
        if (!visited[edge_list[next_edge].to]) {
            dfs_sum(edge_list[next_edge].to);
            sum[cur] += sum[edge_list[next_edge].to];
        }
        next_edge = edge_list[next_edge].next_edge_index;
    }
//    cout<<cur<<" "<<sum[cur]<<endl;
    if (sum[cur] > result)result = sum[cur];
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < 2 * (n - 1); i += 2) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        edge_list[i].from = a;
        edge_list[i].to = b;
        edge_list[i].next_edge_index = node_list[a].first_edge_index;
        node_list[a].first_edge_index = i;
        edge_list[i + 1].from = b;
        edge_list[i + 1].to = a;
        edge_list[i + 1].next_edge_index = node_list[b].first_edge_index;
        node_list[b].first_edge_index = i + 1;
    }
    depth[0] = 0;
    dfs(1, 0);
    for (int i = 0; i < k; ++i) {
        int start, end;
        scanf("%d%d", &start, &end);
        int lca = LCA(start, end);
        //cout << lca << endl;
        --node_list[f[lca][0]].milk_tea;
        --node_list[lca].milk_tea;
        ++node_list[start].milk_tea;
        ++node_list[end].milk_tea;
    }
    memset(visited, false, sizeof(visited));
//    for(int i=1;i<=n;++i)cout<<node_list[i].milk_tea<<" ";
//    cout<<endl;
    dfs_sum(1);
    printf("%d%c", result, '\n');
    return 0;
}