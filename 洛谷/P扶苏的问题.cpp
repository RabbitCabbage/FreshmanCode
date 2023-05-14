//
// Created by lu'ren'jia'd's on 2022/6/2.
//

#include <iostream>

using namespace std;
int n, q;
const int maxn = 1e6 + 5;
long long array[maxn];
struct node {
    long long max;
    bool modify_tag = false;//表示这个数要不要修改
    long long modify;
    long long add_tag = 0;
} tree[maxn << 2];

void push_up(int p) {
    tree[p].max = max(tree[p << 1].max, tree[p << 1 | 1].max);
}

void build(int p, int l, int r) {
    if (l == r) {
        tree[p].max = array[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}

void push_down(int p, int l, int r) {
    if (tree[p].modify_tag) {
        tree[p].modify_tag = false;
        tree[p << 1].modify_tag = tree[p << 1 | 1].modify_tag = true;
        tree[p << 1].modify = tree[p << 1 | 1].modify = tree[p].modify;
        tree[p << 1].max = tree[p].modify;
        tree[p << 1 | 1].max = tree[p].modify;
    }
    if (tree[p].add_tag != 0) {
        tree[p << 1].max += tree[p].add_tag;
        tree[p << 1 | 1].max += tree[p].add_tag;
        tree[p << 1].add_tag = tree[p << 1 | 1].add_tag = tree[p].add_tag;
        tree[p].add_tag = 0;
    }
}

void add(int nl, int nr, long long x, int p, int l, int r) {
    if (nl <= l && nr >= r) {
        tree[p].add_tag = x;
        tree[p].max += x;
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (nl <= mid)add(nl, nr, x, p << 1, l, mid);
    if (nr >= mid + 1)add(nl, nr, x, p << 1 | 1, mid + 1, r);
    push_up(p);
}

void modify(int nl, int nr, long long x, int p, int l, int r) {
    if (nl <= l && nr >= r) {
        tree[p].modify = x;
        tree[p].modify_tag = true;
        tree[p].max = x;
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (nl <= mid)modify(nl, nr, x, p << 1, l, mid);
    if (nr >= mid + 1)modify(nl, nr, x, p << 1 | 1, mid + 1, r);
    push_up(p);
}

long long query(int ql, int qr, int p, int l, int r) {
    if (ql <= l && qr >= r)return tree[p].max;
    long long max1=0, max2=0;
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid)max1 = query(ql, qr, p << 1, l, mid);
    if (qr >= mid + 1)max2 = query(ql, qr, p << 1 | 1, mid + 1, r);
    return max(max1, max2);
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; ++i)scanf("%lld", &array[i]);
    for (int i = 1; i <= q; ++i) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int l, r;
            long long x;
            scanf("%d %d %lld", &l, &r, &x);
            modify(l, r, x, 1, 1, n);
        } else if (op == 2) {
            int l, r;
            long long x;
            scanf("%d %d %lld", &l, &r, &x);
            add(l, r, x, 1, 1, n);
        } else {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%lld\n", query(l, r, 1, 1, n));
        }
    }
    return 0;
}