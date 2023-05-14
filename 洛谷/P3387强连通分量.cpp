//
// Created by lu'ren'jia'd's on 2022/5/29.
//

#include <iostream>
#include <cstring>

using namespace std;
const int maxn = 1e4 + 5;
const int maxm = 1e5 + 5;
int n, m;
int weight[maxn];
struct edge {
    int to, nxt;
} e[maxm];
int first[maxn];
int total = 0;
int in[maxn];

void add_init() {
    total = 0;
    memset(first, 0, sizeof(first));
    memset(in, 0, sizeof(in));
}

int from[maxm], to[maxm];

void add(int from, int to) {
    total++;
    e[total].to = to;
    e[total].nxt = first[from];
    first[from] = total;
}

int sect = 0;
long long sum[maxn];//这是记录每一个强连通分量的点权和
int sect_index[maxn];//记录下每一个点分别是属于那一个强连通分量
int dfn[maxn], low[maxn];
int cnt = 0;
int stack[maxn];
int top = -1;
bool enstack[maxn];

void tarjan_init() {
    sect = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(enstack, false, sizeof(enstack));
    memset(sum, 0, sizeof(sum));
    top = -1;
    cnt = 0;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    enstack[u] = true;
    stack[++top] = u;
    for (int i = first[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (enstack[v])low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        //找到一个强连通分量
        sect++;
        //退栈，直到退到u
        while (1) {
            int destack = stack[top--];
            enstack[destack] = false;
            sum[sect] += weight[destack];
            sect_index[destack] = sect;
            if (destack == u)break;
        }
    }
}

int queue[maxn];
int head = -1;
int tail = -1;
long long dist[maxn];

long long topo() {
    //统计入度为零的点，把它入队
    for (int i = 1; i <= sect; ++i) {
        if (in[i] == 0) {
            queue[++tail] = i;
            dist[i] = sum[i];
        } else dist[i] = 0;
        //注意 这入队的都是已经缩点之后的编号
        //入队的元素的sum就先加上，相当于边权，求一个最大
    }
    while (head < tail) {
        int dequeue = queue[++head];//头部元素出队
        for (int i = first[dequeue]; i; i = e[i].nxt) {
            int v = e[i].to;
            dist[v] = max(dist[v], dist[dequeue] + sum[v]);
            //把点权视为边权，uv的边权就是v的点权，u的点权最开始加上了
            in[v]--;
            if (in[v] == 0)queue[++tail] = v;
            //如果说v的入度等于0l说明他的这个距离和值已经求好了，入队进行其他和值的更新
        }
    }
    long long ans = 0;
    for (int i = 1; i <= sect; ++i) {
        ans = max(ans, dist[i]);
    }
    return ans;
}

int main() {
    memset(first, 0, sizeof(first));
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)scanf("%d", &weight[i]);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &from[i], &to[i]);
        add(from[i], to[i]);
    }
    tarjan_init();
    for (int i = 1; i <= n; ++i) {
        if (dfn[i] == 0) tarjan(i);
    }//tarjan缩点之后还得再跑一次 todo 拓扑排序
    add_init();
    for (int i = 1; i <= m; ++i) {
        if (sect_index[from[i]] == sect_index[to[i]])continue;
        else {
//            cout << "from " << sect_index[from[i]] << " to " << sect_index[to[i]] << endl;
            add(sect_index[from[i]], sect_index[to[i]]);
            in[sect_index[to[i]]]++;//统计每一个强连通分量的入边
        }

    }
    //todo 关于为什么要用拓扑排序，我们现在没有出发点，没有结束点
    //todo 这个是与ATM那道题不同的，那道题有出发点，跑一遍spfa就可以了
    //todo 但是这个没有，所以我们要把所有可以连接到一起的强连通分量都连起来
    //todo 那这样我们的出发点就应该是入度为零的点
    //todo 从入度为零的点出发，一直跑，跑出的最大值就是结果，其实就是一个拓扑排序
    printf("%lld\n", topo());
    return 0;
}