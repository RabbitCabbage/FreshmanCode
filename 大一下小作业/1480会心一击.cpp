//
// Created by lu'ren'jia'd's on 2022/2/28.
//

//cstdio, iostream, cmath, cstring
#include <iostream>
#include <cmath>

inline long long read() {
    long long x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}

using namespace std;
int n, m, query;

int main() {
    n = read();
    m = read();
    bool s[n];
    int n0[n], n1[n];
    s[0] = read();
    n0[0] = (int) (!s[0]);
    for (int i = 1; i < n; ++i) {
        s[i] = read();
        if (!s[i])n0[i] = n0[i - 1] + 1;
        else n0[i] = n0[i - 1];
    }//从前面数0的个数
    int f[n][20];

    n1[n - 1] = (int) s[n - 1];
    f[n - 1][0] = n0[n - 1] + n1[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        if (s[i])n1[i] = n1[i + 1] + 1;
        else n1[i] = n1[i + 1];
        f[i][0] = n0[i] + n1[i];
    }//从后面数1的个数
    //只要确定了0和1的分界点，不减的最长子序列长度就可以确定了
    //因为大家left之前的0的个数都是一样的，right后的1的个数也都是一样
    // 就没有必要再讨论了，直接看对于整个数组的长度的最大值，之后修修补补就可以了
    for (int j = 1; j <= (int) (log(n) / log(2)); ++j) {
        for (int i = 0; i + (1 << j) <= n; ++i)
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    }
    for (int i = 0; i < m; ++i) {
        int opt, left, right;
//        scanf("%d%d%d", &opt, &left, &right);
        opt = read();
        left = read();
        right = read();
        --left, --right;
        if (opt == 1) {
            int x = (int) (log(right - left + 1) / log(2));
            int max_length = max(f[left][x], f[right - (1 << x) + 1][x]);
            printf("%d%c", max_length - n0[left] + !s[left] - n1[right] + s[right], '\n');
        } else {
            if (left == right)printf("%d%c", 1, '\n');
            else {
                int number_of_1 = n1[left] - n1[right] + s[right];//这是这个区间段中所有1的个数
                //那么，left+number-1就是最后一个1的下标,看看那个数的前面有几个1
                if (n1[left] - n1[left + number_of_1 - 1] + s[left + number_of_1 - 1] == number_of_1)cout << 1 << '\n';
                else printf("%d%c", 2, '\n');
            }
        }
    }
    return 0;
}
