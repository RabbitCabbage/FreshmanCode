#include <iostream>
#include <cstring>

using namespace std;
const int maxn = 154;

int n, p;
int first[maxn];
int to[maxn];
int nxt[maxn];
int total = 0;
int dp[maxn][maxn];
int size[maxn];
//dp[i][j]表示的是以i为根节点的子树当这个子树中含有j个点的时候
//所需要拆掉的最少的边的数目，这个点也包括进去
//那么对于j=1，就是只连了这一个点，i的子节点都断开了
//dp[i][j]=i的直接相连子节点数目，把和自己相连的子节点都断开了就可以
//对于每一个子节点dp[u][j]=min(dp[u][j-k]+dp[v][k]-1)
//因为一开始uv之间的那条边被断开了，v要连上去的时候就要少断一条边，-1

void add(int u, int v) {
    total++;
    to[total] = v;
    nxt[total] = first[u];
    first[u] = total;
    dp[u][1]++;//以u作为父节点、直接相连出去的增加了1,
}

void dfs(int fa, int cur) {
    for (int i = first[cur]; i; i = nxt[i]) {
        if (to[i] == fa)continue;
        dfs(cur, to[i]);
        size[cur] += size[to[i]];//这是以i为根节点的子树中的节点个数，包括根节点
        //并且不可提前（到add边的时候）统计，因为我们默认最开始时这些点都没有连上去的，
        //dfs就相当于一个一个一个儿子链接上去的过程，没有dfs到的儿子还不可以算
        //否则这里会出错！！！！！！！！！！！！！！！！！！
        ////std::cout << "用" << ' ' << to[i] << ' ' << "迭代" << ' ' << cur << std::endl;
        //for (int j = 1; j <= size[cur]; ++j) {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
        //这里为啥要倒着滚
        //todo 因为实际上相当于是一个分组背包，相当于是dp[u][v][j]
        //todo 这个v表示的就是前v个儿子考虑了，那么我们其实递推公式是这样的
        //todo dp[u][v][j]=min(dp[u][v-1][j-k]+dp[u][sons_of_v][k]-1)
        //todo 那么肯定要倒着来才可以保证前面的dp不受影响
        for (int j = size[cur]; j >= 1; --j) {
            //to[i]最多子树中节点的个数也就是size[to[i]]了，并且它还得保证j-k>=1
            //下面要保证j不会太大，
            for (int k = 1; k <= size[to[i]] && j - k >= 1; ++k) {
                //std::cout << "j = " << j << " k = " << k << std::endl;
                //std::cout << "dp[cur][j] = " << dp[cur][j] << std::endl;
                //std::cout << "dp[cur][j - k] + dp[to[i]][k] - 1 = " << dp[cur][j - k] + dp[to[i]][k] - 1 << std::endl;
                //std::cout << "dp[cur][j - k] = " << dp[cur][j - k] << " dp[to[i]][k] = " << dp[to[i]][k] << std::endl;
                dp[cur][j] = min(dp[cur][j], dp[cur][j - k] + dp[to[i]][k] - 1);
                //std::cout << dp[cur][j] << std::endl;
                //std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            }
        }
    }
}

int main() {
    for (int i = 0; i < maxn; ++i) {
        for (int j = 2; j < maxn; ++j) {
            dp[i][j] = 160;
        }
    }
    memset(first, 0, sizeof(first));
    scanf("%d %d", &n, &p);
    for (int i = 1; i <= n; ++i)size[i] = 1;
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        add(u, v);
    }
    dfs(0, 1);
    int min_ = 160;
    for (int i = 1; i <= n; ++i) {
        //并且这个点要有可能含有p个节点的子树
        //如果不是根节点，还要多断一个和根的连边
        if (i > 1)min_ = min(min_, dp[i][p]+1);
        else min_ = min(min_, dp[i][p]);
    }
    printf("%d\n", min_);
    return 0;
}