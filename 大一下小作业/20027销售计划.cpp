//
// Created by lu'ren'jia'd's on 2022/4/12.
//

#include <iostream>

using namespace std;
const int maxn = 102;
const int maxm = 1e5 + 2;
int sum[maxn][maxm]{0};
int price[maxn];
int price_sum = 0;
int max_of_column[maxm]{0};
int max_answer[maxm]{0};
int n, m, k;

int main() {
    cin >> n >> m >> k;
    int tmp;
    for (int i = 0; i < n; ++i) {
        cin >> price[i];
        price_sum += price[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        sum[i][0] = tmp;
        if (tmp > max_of_column[0])max_of_column[0] = tmp;
        for (int j = 1; j < m; ++j) {
            cin >> tmp;
            if (tmp > max_of_column[j])max_of_column[j] = tmp;
            sum[i][j] = sum[i][j - 1] + tmp;
        }
    }
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < m; ++j)cout << sum[i][j] << " ";
//        cout << endl;
//    }
//    for (int i = 0; i < m; ++i)cout << max_of_column[i] << " ";
//    cout << endl;
    int queue[m + 1];
    int head = 1, tail = 0;
    for (int i = 0; i < m; ++i) {
        //要求这个区间内最大的，因此要用一个单调递减的队列
        while (head <= tail && max_of_column[queue[tail]] <= max_of_column[i])--tail;
        queue[++tail] = i;//此元素入队
        while (queue[tail] - queue[head] + 1 > k) ++head;//维护窗口的宽度
        if (i >= k - 1)max_answer[i] = queue[head];//记下最大值的序号
    }
    //现在在maxanswer里面记下的就是以i结尾的滑动窗口的 最大值
//    for (int i = k - 1; i < m; ++i)cout << max_answer[i] << " ";
//    cout << endl;
    int ans = 0;
    for (int i = k - 1; i < m; ++i) {
        //讨论以i结尾的滑动窗口
        int honest = 0;
        for (int j = 0; j < n; ++j) {
            if (i - k >= 0)honest += price[j] * (sum[j][i] - sum[j][i - k]);
            else honest += price[j] * sum[j][i];
        }
        int cheat = max_of_column[max_answer[i]] * k * price_sum;
        if (cheat - honest > ans)ans = cheat - honest;
//        cout << i - k << " " << cheat << " " << honest << endl;
    }
    cout << ans << endl;
    return 0;
}