//
// Created by lu'ren'jia'd's on 2022/6/2.
//
//状态转移方程，每一次加了sum[i][j]之后，
//可以由sum[i-1][j-1]或者sum[i-1][j]加上自己
#include <iostream>
#include <cstring>

using namespace std;
const int maxn = 1e3 + 3;
int num[maxn][maxn];
int sum[maxn][maxn];
int n;

int main() {
    scanf("%d", &n);
    memset(num, 0, sizeof(num));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j)
            scanf("%d", &num[i][j]);
    }
    sum[1][1] = num[1][1];
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= i; ++j)
            sum[i][j] = max(sum[i - 1][j - 1], sum[i - 1][j]) + num[i][j];
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)ans = max(ans, sum[n][i]);
    printf("%d\n", ans);
    return 0;
}
