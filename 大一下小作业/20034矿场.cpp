#include <iostream>
#include <cstring>

using namespace std;
int N;
const int maxn = 5e4 + 5;
const int maxv = 1e4 + 5;
struct edge {
    int nxt, to;
} e[maxn];
int first[maxv];
int total = 0;

void add(int s, int t) {
    total++;
    e[total].nxt = first[s];
    e[total].to = t;
    first[s] = total;
}

int dfn[maxv], low[maxv];
int cnt = 0;
bool cut[maxv];//记下某一个点是不是割点
int dcc[maxv][maxv];
int dccn = 0;//dcc记下点双的个数和点双的组成点
int stack[maxv];
int top = -1;//这是dfs过程中用到的栈结构
int son;

void tarjan(int u, int root) {
    dfn[u] = low[u] = ++cnt;
    stack[++top] = u;
    if (root == u && first[u] == 0) {
        dccn++;
        dcc[dccn][0] = 1;
        dcc[dccn][1] = u;
        return;
    }
    for (int i = first[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (dfn[v])low[u] = min(low[u], dfn[v]);
        else {
            if (u == root)son++;
            tarjan(v, root);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                //说明v并不能和u的某个祖先相连，也就是u他就是个割点了
                cut[u] = true;
//                cout << u << " is a cut point" << endl;
                dccn++;//数量+1
                dcc[dccn][0] = 1;//记下这个点双他有多大
                dcc[dccn][dcc[dccn][0]] = u;
                while (1) {
                    int destack = stack[top--];
                    dcc[dccn][0]++;//点双增大一个规模
                    dcc[dccn][dcc[dccn][0]] = destack;
                    if (destack == v)break;
                }
            }
            if (u == root && son <= 1)cut[u] = false;
        }
    }
}

void init() {
    cnt = dccn = total = 0;
    top = -1;
    memset(first, 0, sizeof(first));
    memset(cut, false, sizeof(cut));
    memset(dfn, 0, sizeof(dfn));
}

int main() {
    int cases = 0;
    while (1) {
        init();
        cases++;
        int vv = 0;//记下最大点的标号，等下去跑tarjan
        scanf("%d", &N);
        if (N == 0)return 0;
        for (int i = 1; i <= N; ++i) {
            int s, t;
            scanf("%d %d", &s, &t);
            add(s, t);
            add(t, s);
            vv = max(s, t);
        }
        for (int i = 1; i <= vv; ++i) {
            son = 0;
            tarjan(i, i);
        }
        long long ans = 1;
        int num = 0;
//        for (int i = 1; i <= dccn; ++i) {
//            cout << "size of the dcc " << dcc[i][0] << endl;//遍历每一个点双
//            cout << "composition of the dcc: ";
//            for (int j = 1; j <= dcc[i][0]; ++j)
//                cout << dcc[i][j] << " ";
//            cout << endl;
//        }
        for (int i = 1; i <= dccn; ++i) {//遍历每一个点双
            int cut_num = 0;
            for (int j = 1; j <= dcc[i][0]; ++j) {
                if (cut[dcc[i][j]])cut_num++;
            }
            if (cut_num == 0) {
                ans *= dcc[i][0] * (dcc[i][0] - 1) / 2;
                num += 2;
            } else if (cut_num == 1) {
                ans *= dcc[i][0] - 1;
                num += 1;
            }
        }
        printf("Case %d: %d %lld\n", cases, num, ans);
    }
}