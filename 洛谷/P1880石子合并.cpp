//
// Created by lu'ren'jia'd's on 2022/6/2.
//

#include <iostream>
#include <cstring>

using namespace std;
const int maxn = 1e2 + 2;
const int inf = 1e8;
int n;
int num[maxn << 1];
int sum[maxn << 1];
int dp_max[maxn << 1][maxn << 1];
int dp_min[maxn << 1][maxn << 1];

int main() {
    memset(sum, 0, sizeof(sum));
    memset(dp_max, 0, sizeof(dp_max));
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &num[i]);
        num[n + i] = num[i];
    }
    for (int i = 1; i <= (n << 1); ++i) {
        sum[i] = sum[i - 1] + num[i];
        dp_max[i][i] = 0;
        dp_max[i - 1][i] = num[i] + num[i - 1];
        dp_min[i][i] = 0;
        dp_min[i - 1][i] = num[i] + num[i - 1];
    }
//    for (int i = 1; i <= (n << 1); ++i)cout << sum[i] << " ";
//    cout << endl;
    for (int step = 2; step <= n; ++step) {
        for (int i = 1; i <= n; ++i) {
            int j = i + step;
            dp_min[i][j] = inf;
            for (int k = i; k < j; ++k) {
                //求的是从i合并到j的这样一个环的最大值
                //这个环中间从k这个地方断开，所以没有加num[k]+num[k+1]
                dp_max[i][j] = max(dp_max[i][k] + dp_max[k + 1][j] + sum[j] - sum[i - 1], dp_max[i][j]);
                dp_min[i][j] = min(dp_min[i][k] + dp_min[k + 1][j] + sum[j] - sum[i - 1], dp_min[i][j]);
                if (i + n <= (n << 1) && j + n <= (n << 1))
                    dp_max[i + n][j + n] = dp_max[i][j], dp_min[i + n][j + n] = dp_min[i][j];
                //这种小规模的解出来了就先记下来，等下好用
            }
//            cout << "MAX " << i << " " << j << " " << dp_max[i][j] << endl;
//            cout << "MIN " << i << " " << j << " " << dp_min[i][j] << endl;
        }
    }
    int ans1 = 0, ans2 = inf;
    for (int i = 1; i <= n; ++i) {
        ans1 = max(ans1, dp_max[i][i + n - 1]);
        ans2 = min(ans2, dp_min[i][i + n - 1]);
    }
    printf("%d\n%d\n", ans2, ans1);
    return 0;
}