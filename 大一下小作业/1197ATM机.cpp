#include <iostream>
#include <cstring>

using namespace std;
const int maxn = 5e5 + 5;
const int maxm = 5e5 + 5;
int from[maxn];
int to[maxn];
long long money[maxn];
int bar[maxn];
struct edge {
    int to, next;
    long long value = 0;
} e[maxm];
int node[maxn];//the default value is 0
int total = 1;

void add(int f, int t) {
    e[total].to = t;//put the destination into the edge
    e[total].next = node[f];
    node[f] = total;
    total++;
}

void add_with_value(int f, int t, long long val) {
    e[total].to = t;//put the destination into the edge
    e[total].next = node[f];
    e[total].value = val;
    node[f] = total;
    total++;
}

int dfn[maxn];
int low[maxn];
bool enstked[maxn];//mark the node has been en_stacked;
int count = 0;//use for the sequence;
//use recursion to find the SCC
//use array to mimic a stack;
int stack[maxn];
int top = -1;
int number_of_sections = 0;
int section[maxn];//记录每一个点应该是在哪一个缩完之后的点的内部
//section[i]=j就是说原本的i点应该在第j个缩点之中
long long section_sum[maxn]{0};

void tarjan(int x) {
    dfn[x] = low[x] = count++;
    stack[++top] = x;//en_stack;
    enstked[x] = true;
    for (int i = node[x]; i != 0; i = e[i].next) {
        //遍历所有与这个点邻接的边
        if (dfn[e[i].to] == 0) {
            //这个点还没有被访问过
            tarjan(e[i].to);
            low[x] = min(low[x], low[e[i].to]);
        } else if (enstked[e[i].to]) {
            //这个点已经访问过了并且在栈内，则应该取它的dfn
            low[x] = min(low[x], dfn[e[i].to]);
        }
    }
    if (dfn[x] == low[x]) {
        //检查是不是应该退栈了
        number_of_sections++;//连通分量多了一个,从一开始计数的
        //取出栈内的每一个点stack[top--]
        do {
            int de_stack = stack[top];
            enstked[de_stack] = false;
            section_sum[number_of_sections] += money[de_stack];
            section[de_stack] = number_of_sections;
        } while (stack[top--] != x);
//        cout << section_sum[number_of_sections] << endl;
//        cout<<section_sum[number_of_sections]<<endl;
    }
}

int n, m;
int s, p;

//用缩点建立一张新图
void build_new() {
    for (int i = 0; i <= total; ++i) {
        e[i].to = e[i].next = 0;
    }
    for (int i = 0; i <= maxn; ++i)node[i] = 0;
    total = 1;
    for (int i = 1; i <= m; ++i) {
        if (section[from[i]] == section[to[i]])continue;
        else add_with_value(section[from[i]], section[to[i]], section_sum[section[to[i]]]);
    }
}

long long dist[maxn];
bool visited[maxn];
int q[maxn];
int head = -1, rear = -1;

void spfa(int start) {
    for (int i = 1; i <= number_of_sections; i++) dist[i] = 0;
    int gs = section[start];
//    q.push(gs);
    q[++rear] = gs;//rear is the last element and the head is the one before the first
    visited[gs] = true;
    dist[gs] = section_sum[gs];
    while (rear != head) {
        int h = q[++head];
        visited[h] = false;
        for (int i = node[h]; i; i = e[i].next) {
            int t = e[i].to;
            if (dist[t] < dist[h] + e[i].value) {
                dist[t] = dist[h] + e[i].value;
                if (!visited[t]) {
                    q[++rear] = t;
                    visited[t] = true;
                }
            }
        }
    }
}

/*
//void spfa(int start) {
//    memset(dist, 0, sizeof(dist));
//    memset(visited, false, sizeof(visited));
//    dist[section[start]] = section_sum[section[start]];
////    visited[section[start]] = true;
//    int added_node;
//    for (int j = 1; j <= number_of_sections; ++j) {
//        long long biggest = 0;
//        for (int k = 1; k <= number_of_sections && !visited[k]; ++k) {
//            if (dist[k] > biggest) {
//                added_node = k;//找到下一个放到这里面的点
//                biggest = dist[k];
//            }
//            //也就是那个zui大的
//        }
////        cout<<"added "<<added_node<<endl;
//        visited[added_node] = true;
//        for (int k = node[added_node]; k != 0; k = e[k].next) {
//            if (!visited[e[k].to]) {
//                //这个点还没有被选入，它的路径还要更新
//                if (dist[e[k].to] < dist[added_node] + e[k].value) {
//                    dist[e[k].to] = dist[added_node] + e[k].value;
//                }
//            }
//        }
//    }
//}
*/
int main() {
    memset(dfn, 0, sizeof(dfn));
    memset(enstked, false, sizeof(enstked));
    memset(section_sum, 0, sizeof(section_sum));
//    memset(dist, 0, sizeof(dist));
    memset(money, 0, sizeof(money));
    scanf("%d %d\n", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d\n", &from[i], &to[i]);
        add(from[i], to[i]);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%lld\n", &money[i]);
    }
    scanf("%d %d\n", &s, &p);
    for (int i = 1; i <= p; ++i)scanf("%d", &bar[i]);
    //to calculate the SCC
//    tarjan(s);
    //因为不能保证只有一个连通分量，甚至可能有孤立出来的分量
    for (int i = 1; i <= n; ++i)if (dfn[i] == 0)tarjan(i);
//    for (int i = 1; i <= n; ++i)cout << section[i] << endl;
    build_new();
    spfa(s);
//    for (int i = 1; i <= number_of_sections; ++i) {
//        cout << dist[i] << endl;
//        cout<<visited[i]<<endl;
//    }
    long long max_ans = 0;
    for (int i = 1; i <= p; ++i) {
        if (max_ans < dist[section[bar[i]]])
            max_ans = dist[section[bar[i]]];
//        cout<<max_ans<<endl;
//        cout<<dist[section[bar[i]]]<<endl;
    }
    printf("%lld\n", max_ans);
    return 0;
}