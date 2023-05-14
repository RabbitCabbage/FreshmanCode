//
// Created by lu'ren'jia'd's on 2022/6/27.
//

#include <iostream>
#include <cstring>

using namespace std;
//要维护数组表示的是在这个高度会有多少个手办，然后逐个插入
//从左到右插入一次，从右到左插入一次
//然后询问区间的和即可，用线段树维护这个插入过程
const int maxh = 1e5 + 5;
const int maxn = 1e5 + 5;
int n;
int toys[maxh];//表示的是高度li到ri的玩具总共有toy[i]个,并且这是一个树状数组
int height[maxn];//表示的输入顺序下玩具的高度
int l[maxn], r[maxn];

int lowbit(int x) { return x & (-1 * x); }

void insert(int x) {
    //增加了一个高度是x的手办
    for (int i = x; i <= maxn; i += lowbit(i))toys[i]++;
}

int query(int x) {
    //询问到x的前缀和
    int res = 0;
    for (int i = x; i > 0; i -= lowbit(i))res += toys[i];
    return res;
}

int main() {
    int h_m = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &height[i]);
        h_m = max(h_m, height[i]);
    }
    memset(toys, 0, sizeof(toys));
    for (int i = 1; i <= n; ++i) {
        l[i] = query(h_m + 1) - query(height[i]);
        insert(height[i]);
    }
    memset(toys, 0, sizeof(toys));
    for (int i = n; i >= 1; --i) {
        r[i] = query(h_m + 1) - query(height[i]);
        insert(height[i]);
    }
    int count = 0;
    for (int i = 1; i <= n; ++i) {
//        cout << l[i] << endl;
//        cout << r[i] << endl;
        if (l[i] > 2 * r[i] || r[i] > 2 * l[i])count++;
    }
    printf("%d\n", count);
    return 0;
}