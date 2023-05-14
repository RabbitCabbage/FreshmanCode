//
// Created by lu'ren'jia'd's on 2022/4/13.
//

#include<iostream>

using namespace std;
const int maxn = 5e5 + 5;
int n, m;
long long tag[maxn]{0};
long long number[maxn];

int lowbit(int i) { return i & (-1 * i); }

void update(int i, long long k) {
    for (int j = i; j <= n; j += lowbit(j))tag[j] += k;
}

long long query(int i) {
    long long tag_sum = 0;
    for (int j = i; j >= 1; j -= lowbit(j))tag_sum += tag[j];
    return tag_sum;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)scanf("%lld", &number[i]);
    for (int i = 1; i <= m; ++i) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int l, r;
            long long k;
            scanf("%d %d %lld", &l, &r, &k);
            update(l, k);
            update(r + 1, -k);
        } else {
            int x;
            scanf("%d", &x);
            long long tag_sum = query(x);
            printf("%lld%c", tag_sum + number[x], '\n');
        }
    }
    return 0;
}
//P5057简单题
//思路是一样的，方法是用打差分tag的模式，但是这个tag每次都是^1.在l和r+1分别^1,就得到的是tag了
//因为你想，^1两次就相当于抵消了tag