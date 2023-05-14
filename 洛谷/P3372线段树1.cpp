//
// Created by lu'ren'jia'd's on 2022/4/12.
//

#include <iostream>

using namespace std;
const int maxn = 1e5 + 5;
const int maxm = 1e5 + 5;
int n, m;
int array[maxn];
long long ans[4 * maxn]{0};
int tag[4 * maxn]{0};

void push_up(int p) {
    ans[p] = ans[p << 1] + ans[p << 1 | 1];
}

void build(int p, int l, int r) {
    if (l == r) {
        ans[p] = array[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}

void lazy_tag(int p, int l, int r, long long k) {
    tag[p] += k;
    ans[p] += k * (r - l + 1);
}

void push_down(int p, int l, int r) {
    int mid = (l + r) >> 1;
    long long k = tag[p];
    lazy_tag(p << 1, l, mid, k);
    lazy_tag(p << 1 | 1, mid + 1, r, k);
    tag[p] = 0;
}

void update(int nl, int nr, int p, int l, int r, long long k) {
    if (nl <= l && nr >= r) {
        //这一段在我们要更新的那段内，需要打tag
        tag[p] += k;
        ans[p] += k * (r - l + 1);
        return;
    }
    push_down(p, l, r);//这一段的范围内包括有不需要+k的，因此标签下放
    int mid = (l + r) >> 1;
    if (nl <= mid)update(nl, nr, p << 1, l, mid, k);
    if (nr >= mid + 1)update(nl, nr, p << 1 | 1, mid + 1, r, k);
    push_up(p);
}

long long query(int qx, int qy, int p, int l, int r) {
    long long res = 0;
    if (qx <= l && qy >= r)return ans[p];
    int mid = (l + r) >> 1;
    push_down(p, l, r);//这一段里面包括不需要的，因此标签下放一层
    if (qx <= mid)res += query(qx, qy, p << 1, l, mid);
    if (qy >= mid + 1)res += query(qx, qy, p << 1 | 1, mid + 1, r);
    return res;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)cin >> array[i];
    build(1, 1, n);//建立线段树
    for (int i = 0; i < m; ++i) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            long long k;
            cin >> l >> r >> k;
            update(l, r, 1, 1, n, k);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(l, r, 1, 1, n) << endl;
        }
    }

    return 0;
}