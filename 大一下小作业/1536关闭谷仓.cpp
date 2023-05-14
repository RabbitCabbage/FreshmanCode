#include<iostream>
#include <cstring>

using namespace std;
const int maxn = 2e5 + 5;
const int maxm = 2e5 + 5;
int m, n;
bool appear[maxn];//记录这点有没有出现，如果还没出现过的话就不用加上那条边了
bool answer[maxn];
int order[maxm];//记录去掉这些谷仓的顺序
int father[maxn];

int find_father(int x) {
    if (father[x] == x)return x;
    else return father[x] = find_father(father[x]);
}

bool check(int x, int y) {
    return find_father(x) == find_father(y);
}

void merge(int x, int y) {
    x = find_father(x), y = find_father(y);
    father[x] = y;
}

int edge[maxn << 1];//记下每条边的index
int to[maxn << 1];//记下每条边所指向的点
int first[maxn];//第一条相连的边index
int total = 0;//边的编号

void add(int f, int t) {
    edge[total] = first[f];
    first[f] = total;
    to[total] = t;
    ++total;
}

int main() {
//    memset(edge,-1,sizeof(edge));
    memset(first, -1, sizeof(first));
    scanf("%d %d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &u, &v);
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &order[i]);
        father[i] = i;
    }
    int merge_time = 0;
    for (int i = n; i > 0; --i) {
        //考虑添上这个节点之后的连通性
        appear[order[i]] = true;
        int next_edge = first[order[i]];
        while (next_edge != -1) {
            int node = to[next_edge];//找到这条边上会相连的边
            if (appear[node] && !check(order[i], node)) {
                merge(order[i], node);
                merge_time++;
            }
            next_edge = edge[next_edge];
        }
        //然后询问连通性
//        if (i == n) {
//            answer[order[i]] = true;
//            continue;
//        }
        if (merge_time == n - i)answer[order[i]] = true;
//        int fa = find_father(order[i]);
//        int j;
//        for (j = 1; j <= n; ++j) {
//            if (appear[j]) {
//                if (find_father(j) != fa) {
//                    answer[order[i]] = false;
//                    break;
//                }
//            }
//        }
//        if (j > n)answer[order[i]] = true;
//        这种方法T飞了，应该用更加巧妙的办法来解决这个问题
//        记录合并的次数，如果次数等于 k-1 则YES;反之，则NO.
    }
    for (int i = 1; i <= n - 1; i++)
        if (answer[order[i]])printf("YES\n");
        else printf("NO\n");
    printf("YES");
    return 0;
}