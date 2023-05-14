//
// Created by lu'ren'jia'd's on 2022/6/2.
//

#include <iostream>
#include <cstring>

using namespace std;
const int maxn = 1e2 + 2;
int n;
long long sum[maxn << 1];
long long dp[maxn << 1][maxn << 1];
struct bead {
    int front, end;
} bead[maxn << 1];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &bead[i].front);
        bead[i + n].front = bead[i].front;
    }
    for (int i = 1; i <= 2 * n - 1; ++i) {
        bead[i].end = bead[i + 1].front;
    }
    bead[2 * n].end = bead[1].front;
    //还是用二倍的长度，把这条链展开，等会取一个长度是n的最大值就好
//    for (int i = 1; i <= 2 * n; ++i)
//        cout << bead[i].front << " " << bead[i].end << endl;
    //还用合并石子的那个方法，遍历把环形拆成链的分点k
    //记dp是从i到j的珠子合并在一起，（从k分开遍历讨论）的最大能量值
    //dp[i][j]=dp[i][k]+dp[k+1][j]+i的头*k的尾（或者k+1的头）*j的尾，与原来的取最大值
    memset(dp, 0, sizeof(dp));//dp的含义是从i一直合并到j的最大值，显而易见dp[i][i]==0
    for (int step = 1; step <= n; ++step) {//因为我们没初始化i_i+1这里的step就从①开始
        for (int i = 1; i <= n; ++i) {
            int j = i + step;
            for (int k = i; k < j; ++k) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j] + bead[i].front * bead[j].end * bead[k].end);
                if (i + n <= (n << 1) && j + n <= (n << 1))dp[i + n][j + n] = dp[i][j];
            }
//            cout << i << " " << j << " " << dp[i][j] << endl;
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, dp[i][i + n - 1]);//这里记得减去一
    }
    printf("%lld\n", ans);
    return 0;
}