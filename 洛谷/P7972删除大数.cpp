//
// Created by lu'ren'jia'd's on 2022/5/29.
//

#include <iostream>
#include <cstring>

using namespace std;
const int maxn = 3e5 + 5;
const long long mod = 1e9 + 7;
int n;
long long a[maxn];
int l[maxn];
int r[maxn];
long long f[maxn];//表示的是以第i个数字ai这个数字结尾的序列的个数
long long tr[maxn];

int lowbit(int x) {
    return x & (-x);
}

void update(long long x, int index) {
    for (int i = index; i <= n; i += lowbit(i)) {
        tr[i] += x;
        tr[i] %= mod;
    }
}

long long query(int index) {
    long long answer = 0;
    for (int i = index; i >= 1; i -= lowbit(i)) {
        answer += tr[i];
        answer %= mod;
    }
    return answer;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    //跑两遍单调队列，目的是找到左右两边首个比自己小的,等于也行，等于也出列吧
    //要找到首个比自己小的,应该用单调递增序列
    for (int i = 1; i <= n; ++i) {
        l[i] = 1;
        r[i] = n;
    }
    int stack[maxn];
    int top = -1;
    stack[++top] = 1;
    for (int i = 2; i <= n; ++i) {
        while (top >= 0 && a[stack[top]] >= a[i]) {
//            r[stack[top--]]=i;
            r[stack[top--]] = i - 1;//这里记下的是最多能删除到哪一个
        }
        stack[++top] = i;
    }
    top = -1;
    stack[++top] = n;
    for (int i = n - 1; i >= 1; --i) {
        while (top >= 0 && a[stack[top]] >= a[i]) {
//            l[stack[top--]] = i;
            l[stack[top--]] = i + 1;
        }
        stack[++top] = i;
    }
//    for (int i = 1; i <= n; ++i) {
//        cout << i << " l = " << l[i] << " r = " << r[i] << endl;
//    }
    //l[i] r[i]都是代表第i个数字可以删除到第l[i] r[i] 个数字
    memset(f, 0, sizeof(f));
    memset(tr, 0, sizeof(tr));
    update(1, 1);
    for (int i = 1; i <= n; ++i) {
//        cout << query(n) << " " << query(l[i] - 1) << endl;
        f[i] = ((query(n) - query(l[i] - 1)) % mod + mod) % mod;
//        cout << f[i] << endl;
        update(f[i], r[i]);
    }
    long long min = 2147483647;
    long long ans = 0;
    for (int i = n; i >= 1; --i) {
//        cout << "f[" << i << "]= " << f[i] << endl;
        if (min < a[i])continue;
        else {
            min = a[i];
            ans += f[i];
            ans %= mod;
        }
    }
    printf("%lld\n", ans);
    return 0;
}