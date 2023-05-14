//
// Created by lu'ren'jia'd's on 2022/5/27.
//

#include <iostream>
#include <cstring>

using namespace std;
const int maxn = 5e3 + 5;
const int maxm = 1e4 + 5;
struct edge {
    int nxt, to;
    long long len;
} e[maxm << 1];
int first[maxn];
int total = 0;

void add(int s, int t, long long len) {
    e[total].nxt = first[s];
    e[total].to = t;
    e[total].len = len;
    first[s] = total;
    total++;
}

int n, m;
int queue[maxn * 200];
int head = -1, tail = -1;
bool enqueued[maxn];
long long dist[maxn];
const long long inf = 2e8;

void init() {
    head = -1, tail = -1;
    memset(enqueued, false, sizeof(enqueued));
    for (int i = 0; i <= n; ++i)dist[i] = inf;
}

//因为一条路径不能重复经过，我们要把直接和1点相连的边去掉，不能经过这里
//所以跑所有和1相邻的点到1点的最短路，记得要把直接到1的边都去掉
void spfa(int from) {
    queue[++tail] = from;
    enqueued[from] = true;
    dist[from] = 0;
    while (head < tail) {
        int dequeue = queue[++head];
        enqueued[dequeue] = false;
        for (int i = first[dequeue]; i != -1; i = e[i].nxt) {
            int to = e[i].to;
            if (dequeue == from && to == 1)continue;//直接路径就要跳过
            if (dist[to] > dist[dequeue] + e[i].len) {
                dist[to] = dist[dequeue] + e[i].len;
                if (!enqueued[to]) {
                    queue[++tail] = to;
                    enqueued[to] = true;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i <= n; ++i) { first[i] = -1; }
    for (int i = 1; i <= m; ++i) {
        int s, t;
        long long len, re_len;
        scanf("%d %d %lld %lld", &s, &t, &len, &re_len);
        add(s, t, len);
        add(t, s, re_len);
    }
    long long ans = inf;
    for (int i = first[1]; i != -1; i = e[i].nxt) {
        init();
        spfa(e[i].to);//为了找这个点，间接到1的最短路径
        ans = min(ans, e[i].len + dist[1]);//就是1到这些点的直接距离+这些点到1的最小距离
    }
    printf("%lld\n", ans);
    return 0;
}