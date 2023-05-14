//
// Created by lu'ren'jia'd's on 2022/4/12.
//

#include <iostream>

using namespace std;
const int maxn = 1e5 + 6;
int n, m, mod;
int array[maxn];
enum upd {
    ADD, MUL
};
struct node {
    long long ans;
    long long multi_tag = 1;
    long long add_tag = 0;
};
node tree[maxn << 2];

void push_up(int p) {
    tree[p].ans = (tree[p << 1].ans + tree[p << 1 | 1].ans) % mod;
}

void build(int p, int l, int r) {
    if (l == r) {
        tree[p].ans = array[l] % mod;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}

void multi_lazytag(int p, long long mul) {
    tree[p].ans *= mul;
    tree[p].multi_tag *= mul;
    tree[p].multi_tag %= mod;
}

void add_lazytag(int p, long long add_, long long multi, int l, int r) {
    tree[p].ans += (r - l + 1) * add_;
    tree[p].ans %= mod;
    tree[p].add_tag *= multi;//!!!!!!!!!!!!!!!前面multi有更新，所以这里add也要乘上从p更新来的倍数
    tree[p].add_tag += add_;
    tree[p].add_tag %= mod;
}

void push_down(int p, int l, int r) {
    int mid = (l + r) >> 1;
    multi_lazytag(p << 1, tree[p].multi_tag);
    multi_lazytag(p << 1 | 1, tree[p].multi_tag);
    add_lazytag(p << 1, tree[p].add_tag, tree[p].multi_tag, l, mid);
    add_lazytag(p << 1 | 1, tree[p].add_tag, tree[p].multi_tag, mid + 1, r);
    tree[p].add_tag = 0;
    tree[p].multi_tag = 1;
}

void update(int nl, int nr, int p, int l, int r, long long k, upd op) {
    if (nl <= l && nr >= r) {
        if (op == ADD) {
            tree[p].ans += k * (r - l + 1);
            tree[p].add_tag += k;
        } else {
            tree[p].ans *= k;
            tree[p].multi_tag *= k;
            tree[p].add_tag *= k;
        }
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (nl <= mid)update(nl, nr, p << 1, l, mid, k, op);
    if (nr >= mid + 1)update(nl, nr, p << 1 | 1, mid + 1, r, k, op);
    push_up(p);
}

long long query(int qx, int qy, int p, int l, int r) {
    long long res = 0;
    if (qx <= l && qy >= r) {
        return tree[p].ans % mod;
    }
    int mid = (l + r) >> 1;
    push_down(p, l, r);
    if (qx <= mid) {
        res += query(qx, qy, p << 1, l, mid) % mod;
        res %= mod;
    }
    if (qy >= mid + 1) {
        res += query(qx, qy, p << 1 | 1, mid + 1, r) % mod;
        res %= mod;
    }
    return res;
}

int main() {
    cin >> n >> m >> mod;
    for (int i = 1; i <= n; ++i)cin >> array[i];
    build(1, 1, n);
    for (int i = 0; i < m; ++i) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            long long k;
            cin >> l >> r >> k;
            update(l, r, 1, 1, n, k, MUL);
        } else if (op == 2) {
            int l, r;
            long long k;
            cin >> l >> r >> k;
            update(l, r, 1, 1, n, k, ADD);
        } else if (op == 3) {
            int l, r;
            cin >> l >> r;
            cout << query(l, r, 1, 1, n) << endl;
        }
    }
    return 0;
}
//注意每次改变mul 的tag的时候，其实也是要改变add的tag的，因为当每一位都×mul的时候，我们给每个数加上的值也是要乘上multi的