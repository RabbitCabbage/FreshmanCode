//
// Created by lu'ren'jia'd's on 2022/5/14.
//

#include <iostream>
#include <cstring>

using namespace std;
//要最大值最小
//二分答案，考虑要掏钱的里面的，最长的那条边它的长度为x
//如果说某条边的长度比x大，那么就得用掉一次免费的边，以保证x确实是最长的
//如果说这条边的长度没有x大，那么就可以保证x这条是最大的，就掏钱把这个修建了
//如果说跑完全程，k个名额用多了，说明x选小了
//如果说跑完全程k个名额没用完，说明x选大了
//当x取到了他应该取的最小的时候，就可以保证整个工程最小
int n, p, k;
const int maxp = 1e4 + 5;
const int maxn = 1e3 + 5;
struct edge {
    int to, value;
    int nxt;
} e[maxp << 1];
int first[maxn];//与每个节点相连的第一条边的index
int total = 0;

void add_edge(int f, int t, int val) {
    total++;
    e[total].to = t;
    e[total].value = val;
    e[total].nxt = first[f];
    first[f] = total;
}

//check 函数返回的是k条免费的边是不是够用
//如果说正好够用或者说不够用，就返回true，k is enough
//现在要找到从1到n的最短路径，
// 并且按照这条边要不要用掉一个免费的名额给他们赋边权是1/0
//趁着把这次求的边权用引用的变量返回回去
long long dist[maxn];//每一点到第一个点的最短距离
bool enqueued[maxn];
const int infinity = 4e7;
int queue[maxn << 2];
int head = -1, rear = -1;
//rear指向最后一个元素
//head指向第一个元素前面的元素
//enqueue表示的是是否在队列里面

bool k_is_enough(int x) {
//用dijkstra算法计算那个01路径的单源点最短路
    head = rear = -1;
    memset(enqueued, false, sizeof(enqueued));
    enqueued[1] = true;
    for (int i = 0; i <= n; ++i)dist[i] = infinity;
    dist[1] = 0;
    queue[++rear] = 1;
    enqueued[1] = true;
    while (head != rear) {
        int top = queue[++head];//取出头，并且头部元素出队.下面就是检查每一个和top相连的点他们的距离
        enqueued[top] = false;
        for (int i = first[top]; i; i = e[i].nxt) {
            int step;
            if (e[i].value > x)step = 1; else step = 0;//这是化成这一个名额是用or不用的step
            if (dist[top] + step < dist[e[i].to]) {
                dist[e[i].to] = dist[top] + step;
                if (!enqueued[e[i].to]) {
                    queue[++rear] = e[i].to;
                    enqueued[e[i].to] = true;
                }
            }
        }
    }
    if (dist[n] > k)return false;
    else return true;
}

int main() {
    memset(first, 0, sizeof(first));
    scanf("%d %d %d", &n, &p, &k);
//    if (p < n - 1) {
//        printf("%d\n", -1);
//        return 0;
//    }
    for (int i = 1; i <= p; ++i) {
        int from, to, value;
        scanf("%d %d %d", &from, &to, &value);
        add_edge(from, to, value);
        add_edge(to, from, value);
    }
    //二分答案要掏钱的最长的边的长度是x
    int l = 0, r = 1000000;
    int x;
    int res = -1;
    while (l < r) {
        x = (l + r) >> 1;
        if (k_is_enough(x)) {
            //k条免费的正好用完或者没有用完，应该要x更小一点
            //并且这个x有可能成为解
            r = x;
            res = x;
        } else l = x + 1;
    }
    printf("%d", res);
    return 0;
}