//
// Created by lu'ren'jia'd's on 2022/3/1.
//

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;
int n, q;

//void print(int *p);
//
//void print_sum(int left, int right, int *sum);

int main() {
//    cin >> n >> q;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d", &n, &q);
    int a[n], b[n], d[n], sum[n], f_max[n][20], f_min[n][20];//sum是d的前缀和
    for (int i = 0; i < n; ++i)scanf("%d", &a[i]);
    scanf("%d", &b[0]);
    d[0] = sum[0] = a[0] - b[0];
    f_max[0][0] = f_min[0][0] = sum[0];
    for (int i = 1; i < n; ++i) {
        scanf("%d", &b[i]);
        sum[i] = sum[i - 1] + a[i] - b[i];
        f_max[i][0] = f_min[i][0] = sum[i];
    }
    for (int j = 1; j <= int(log(n) / log(2)); ++j) {
        for (int i = 0; i + (1 << j) <= n; ++i) {//这个等号必须得有，这样2^j-1次方能完整的计算了
            f_max[i][j] = max(f_max[i][j - 1], f_max[i + (1 << (j - 1))][j - 1]);
            f_min[i][j] = min(f_min[i][j - 1], f_min[i + (1 << (j - 1))][j - 1]);
        }
    }
    for (int i = 0; i < q; ++i) {
        int left, right;
//        cin >> left >> right;
        scanf("%d%d", &left, &right);
        --left, --right;
        if ((left == 0 && sum[right] == 0) || sum[left - 1] == sum[right]) {
            //那么肯定是每一次操作只能+1 0 +1 0 +1这种
            //最后要使得所有数相同，也就是a-b是相等的，那么这一串的前缀和就得是完全相同的
            //那么这一串前缀和就得都比左右开头的小，才能通过+1或者不动这些操作获得相同
            //并且最多的操作次数取决于和左右端点相差最多的
            int x = (int) (log(right - left + 1) / log(2));
            int max_sum = max(f_max[left][x], f_max[right - (1 << x) + 1][x]);
            int min_sum = min(f_min[left][x], f_min[right - (1 << x) + 1][x]);
//            cout << "MAX = " << max_sum << " MIN = " << min_sum << endl;
            if (max_sum == min_sum)printf("%d%c", 0, '\n');
            else if (max_sum > sum[right])printf("%d%c", -1, '\n');
            else {
                printf("%d%c", sum[right] - min_sum, '\n');
            }
        } else printf("%d%c", -1, '\n');
    }
    return 0;
}

//void print(int *p) {
//    for (int i = 0; i < n; ++i)cout << p[i] << " ";
//    cout << endl;
//}
//
//void print_sum(int left, int right, int *sum) {
//    for (int i = left; i <= right; ++i)cout << sum[i] << ' ';
//    cout << endl;
//}