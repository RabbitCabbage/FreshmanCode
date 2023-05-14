//
// Created by lu'ren'jia'd's on 2022/6/2.
//

#include <iostream>
#include <cstring>

using namespace std;
int n;
const int maxn = 2e3 + 3;
int height[maxn];
int length[maxn];
int rise[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &height[i]);
    }
    for (int i = n; i >= 1; --i)
        rise[i] = 1, length[i] = 1;
    //表示的是从这个导弹往后的最长不升子序列的长度
    //所以应该是从右往左进行转移，如果这个高度比后面的某个更高或者相等，就可以加上
    for (int i = n; i >= 1; --i) {
        for (int j = 1; j < i; ++j) {
            if (height[j] >= height[i])length[j] = max(length[j], length[i] + 1);
            if (height[j] < height[i])rise[j] = max(rise[j], rise[i] + 1);
        }
    }
    int ans1 = 0, ans2 = 0;
    for (int i = 1; i <= n; ++i) {
        ans1 = max(ans1, length[i]);
        ans2 = max(ans2, rise[i]);
    }
    printf("%d\n%d\n", ans1, ans2);
    return 0;
}