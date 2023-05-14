//
// Created by lu'ren'jia'd's on 2022/3/31.
//

#include<iostream>
#include <cstring>
#include <cmath>

using namespace std;

int n, m;
struct edge {
    int from, to;//下一个顶点的位置
    int next_edge_index = -1;//下一个儿子的index，是在数组中的index
    int weight;//边权
};
struct node {
    int first_edge_index = -1;//第一个儿子的index，在数组中的index
};
node node_list[100005];
edge edge_list[200008];
bool visited[100005]{false};
int depth[100005]{0};
int f[100005][21];
int ancestor_weight_sum[100005];

void dfs(int cur, int father, int edge_index) {
//    cout<<"now deal with "<<cur<<endl;
    visited[cur] = true;
    depth[cur] = depth[father] + 1;
    if (edge_index != -1)ancestor_weight_sum[cur] = ancestor_weight_sum[father] + edge_list[edge_index].weight;
    else ancestor_weight_sum[cur] = ancestor_weight_sum[father];
    f[cur][0] = father;
    for (int i = 1; (1 << i) <= depth[cur]; ++i) {
        f[cur][i] = f[f[cur][i - 1]][i - 1];
//        cout<<pow(2,i)<<" father is "<<f[cur][i]<<endl;
    }
//    cout<<"depth "<<depth[cur]<<endl;
//    cout<<"sum "<<ancestor_weight_sum[cur]<<endl;
    int next_edge_index = node_list[cur].first_edge_index;
    while (next_edge_index != -1) {
        if (!visited[edge_list[next_edge_index].to])dfs(edge_list[next_edge_index].to, cur, next_edge_index);
        next_edge_index = edge_list[next_edge_index].next_edge_index;
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
        //停留在lca的下一层
    }
    return f[x][0];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < 2 * n - 2; i += 2) {
        int one, another, weight;
        scanf("%d%d%d", &one, &another, &weight);
        edge_list[i].from = one;
        edge_list[i].to = another;
        edge_list[i].weight = weight;
        edge_list[i].next_edge_index = node_list[one].first_edge_index;
        node_list[one].first_edge_index = i;
        edge_list[i + 1].from = another;
        edge_list[i + 1].to = one;
        edge_list[i + 1].weight = weight;
        edge_list[i + 1].next_edge_index = node_list[another].first_edge_index;
        node_list[another].first_edge_index = i + 1;
    }//建立邻接表
//    for (int i = 1; i <= n; ++i) {
//        int next_edge_index = node_list[i].first_edge_index;
//        cout << i << " sons: \n";
//        while (next_edge_index != -1) {
//            cout << edge_list[next_edge_index].to << " " << edge_list[next_edge_index].weight << endl;
//            next_edge_index = edge_list[next_edge_index].next_edge_index;
//        }
//    }
    depth[0] = 0;
    dfs(1, 0, -1);
    int q, x, y;
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        scanf("%d%d", &x, &y);
        int lca = LCA(x, y);
//        cout << lca << endl;
        printf("%d%c", ancestor_weight_sum[x] + ancestor_weight_sum[y] - ancestor_weight_sum[lca] * 2, '\n');
    }
    return 0;
}