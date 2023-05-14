//
// Created by lu'ren'jia'd's on 2022/5/28.
//
//比较牛逼的地方是这道题可以意识到这个水流相当于是一棵树
//并且还用倍增决定在树上怎么跳比较快
//然后还加上一个最大的兜底托盘作为根节点，如果跳到根节点就是无解，牛逼
#include <iostream>
#include <cstring>

using namespace std;
const int maxn = 1e5 + 5;
struct plate {
    long long dd;
    int cc;
} plates[maxn];
int n, q;

struct edge {
    int to, nxt;
} e[maxn];
int head[maxn];
int total = 0;

void add(int to, int from) {
    total++;
    e[total].nxt = head[from];
    e[total].to = to;
    head[from] = total;
}

//log 2 1e5 大概是20的样子现在层数就按照20取
bool vis[maxn];
long long sum[maxn][20];//sum是向上的这一路上的和值，不包括自己
int f[maxn][20];
int dep[maxn];

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    sum[u][0] = plates[fa].cc;
    vis[u] = true;
    for (int i = 1; i < 20; ++i) {
        f[u][i] = f[f[u][i - 1]][i - 1];
        sum[u][i] = sum[f[u][i - 1]][i - 1] + sum[u][i - 1];
    }
    for (int i = head[u]; i; i = e[i].nxt) {
        if (!vis[e[i].to])dfs(e[i].to, u);
    }
}

int main() {
    memset(vis, false, sizeof(vis));
    memset(head, 0, sizeof(head));
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld %d", &plates[i].dd, &plates[i].cc);
    }
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //这里必须模拟那个大水池一下，也就是最后一层一定要用用一个半径无限大的东西接着
    //这样对于后面没有比自己更大的元素的东西就会跑到这里
    //他也相当于是我们倒着建的那棵树的根结点
    const long long inf = 1e9 + 5;
    const int inf_cc = 1e4 + 5;
    plates[n + 1].dd = inf;
    plates[n + 1].cc = inf_cc;
    //用单调栈，一个单调递减的栈找到第一个大于自己的
    //第一个等于自己的是不可以用的，所以我们在出栈的时候，要出比自己小的，相等的不能出
    int stack[maxn];//这里面记下的都是编号
    int first_bigger[maxn];
    int top = -1;
    stack[++top] = 1;
    for (int i = 2; i <= n + 1; ++i) {
        while (top >= 0 && plates[stack[top]].dd < plates[i].dd) {
            first_bigger[stack[top]] = i;
            top--;
        }
        stack[++top] = i;
    }
    for (int i = 1; i <= n; ++i) {
        add(i,first_bigger[i]);//只添加从大盘到小盘的边，也就是树边
        //cout << i << " first bigger " << first_bigger[i] << " " << endl;
    }
    //cout << endl;
    dfs(n + 1, 0);
    for (int i = 1; i <= q; ++i) {
        int index;
        long long vv;
        scanf("%d %lld", &index, &vv);
        //cout << "deal with " << index << " water " << vv << endl;
        if (plates[index].cc >= vv) {
            printf("%d\n", index);
            continue;
        }
        vv -= plates[index].cc;
        for (int j = 19; j >= 0; --j) {
            if ((1 << j) <= dep[index] && vv - sum[index][j] >= 0) {
                vv -= sum[index][j];
                //cout << "from " << index << " to " << f[index][j] << endl;
                index = f[index][j];
            }
            //如果说往上跳这么多还有水剩余，就往上跳到这里
        }
        if (vv == 0) {
            printf("%d\n", index);
            continue;
        }
        if (index == n + 1) {
            printf("%d\n", 0);
            continue;
        }
        index = f[index][0];//再往上条一层，应该就可以装下所有的水
        if (index == n + 1) {
            printf("%d\n", 0);
        } else printf("%d\n", index);
    }
    return 0;
}