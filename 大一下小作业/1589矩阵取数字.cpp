//
// Created by lu'ren'jia'd's on 2022/6/27.
//

#include <iostream>

using namespace std;
int n, m;
const int maxn = 82;
const int maxm = 82;

int number[maxm];
long long dp[maxn][maxn];
long long factors[maxm];

int main() {
    long long res = 0;
    scanf("%d %d", &n, &m);
    for (int t = 1; t <= m; ++t)factors[t] = t * t + t + 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &number[j]);
        }
        //对于这一行做处理
        //我们记dp[from][end]表示一次取数之后的总和，剩下的区间应该是从from到end
        //最开始的时候dp[1][m]=0
        //取到最后我们应该在dp[i][i]+number[i]中去找最大值
        if (m == 1) {
            res += number[m] * factors[1];
            continue;
        }
        dp[1][m] = 0;
        dp[2][m] = number[1] * factors[1];
        dp[1][m - 1] = number[m] * factors[1];//因为是取的第一个数字
        for (int from = 1; from <= m; ++from) {
            for (int end = m; from <= end; --end) {
                //从from，end这个状态可能过来的每一个状态，进行转移
                //原本有m个数字，取的还剩下end-from+1,说明取走了m-end+from-1
                int t = m - end + from - 1;
                dp[from][end] = max(dp[from - 1][end] + number[from - 1] * factors[t],
                                    dp[from][end + 1] + number[end + 1] * factors[t]);
//                cout << from << " " << end << " " << dp[from][end] << endl;
            }
        }
        long long max_ = 0;
        for (int k = 1; k <= m; ++k) {
            max_ = max(dp[k][k] + number[k] * factors[m], max_);
        }
        res += max_;
    }
    printf("%lld", res);
    return 0;
}