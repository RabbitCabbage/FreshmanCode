//
// Created by lu'ren'jia'd's on 2022/4/13.
//
#include <iostream>
#include <cmath>

using namespace std;
//公式 方差s=E(X^2)-(E(X))^2
//主要就是维护一个平方和，用来计算方差
const int maxn = 1e5 + 5;
struct node {
    double number;
    double pow;
    double tag = 0;
};
node tree[maxn << 2];
double array[maxn];
int n, m;

void push_up(int p) {
    tree[p].number = tree[p << 1].number + tree[p << 1 | 1].number;
    tree[p].pow = tree[p << 1].pow + tree[p << 1 | 1].pow;
}

void build(int p, int l, int r) {
    if (l == r) {
        tree[p].number = array[l];
        tree[p].pow = array[l] * array[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}

void push_down(int p, int l, int r) {
    //把tag下放一层
    int mid = (l + r) >> 1;
    tree[p << 1].tag += tree[p].tag;
    tree[p << 1].pow += tree[p].tag * tree[p].tag * (mid - l + 1) + 2 * tree[p << 1].number * tree[p].tag;
    tree[p << 1].number += tree[p].tag * (mid - l + 1);
    tree[p << 1 | 1].tag += tree[p].tag;
    tree[p << 1 | 1].pow += tree[p].tag * tree[p].tag * (r - mid) + 2 * tree[p << 1 | 1].number * tree[p].tag;
    tree[p << 1 | 1].number += tree[p].tag * (r - mid);
    tree[p].tag = 0;
}

void update(int nl, int nr, int p, int l, int r, double k) {
    if (nl <= l && nr >= r) {
        tree[p].tag += k;
        tree[p].pow += k * k * (r - l + 1) + 2 * tree[p].number * k;
        tree[p].number += k * (r - l + 1);
        return;//这句return不能忘，要不然会死循环最后超出范围re
    }
    int mid = (l + r) >> 1;
    push_down(p, l, r);
    if (nl <= mid)update(nl, nr, p << 1, l, mid, k);
    if (nr >= mid + 1)update(nl, nr, p << 1 | 1, mid + 1, r, k);
    push_up(p);
}

double query_a(int ql, int qr, int p, int l, int r) {
    double res = 0;
    if (ql <= l && qr >= r)return tree[p].number;
    int mid = (l + r) >> 1;
    push_down(p, l, r);
    if (ql <= mid)res += query_a(ql, qr, p << 1, l, mid);
    if (qr >= mid + 1)res += query_a(ql, qr, p << 1 | 1, mid + 1, r);
    return res;
}

double query_s(int ql, int qr, int p, int l, int r) {
    double res = 0;
    if (ql <= l && qr >= r)return tree[p].pow;
    int mid = (l + r) >> 1;
    push_down(p, l, r);
    if (ql <= mid)res += query_s(ql, qr, p << 1, l, mid);
    if (qr >= mid + 1)res += query_s(ql, qr, p << 1 | 1, mid + 1, r);
    return res;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i < n + 1; ++i)cin >> array[i];
    build(1, 1, n);
    int op;
    for (int i = 0; i < m; ++i) {
        cin >> op;
        if (op == 1) {
            int l, r;
            double k;
            cin >> l >> r >> k;
            update(l, r, 1, 1, n, k);
        } else if (op == 2) {
            int l, r;
            cin >> l >> r;
//            cout << (int) (100 * query_a(l, r, 1, 1, n) / (r - l + 1)) << endl;
            printf("%.4lf\n",query_a(l, r, 1, 1, n) / (r - l + 1));
        } else if (op == 3) {
            int l, r;
            cin >> l >> r;
//            cout << (int) (100 * (query_s(l, r, 1, 1, n) / (r - l + 1) - pow(query_a(l, r, 1, 1, n) / (r - l + 1), 2)))
//                 << endl;
            printf("%.4lf\n",(query_s(l, r, 1, 1, n) / (r - l + 1) - pow(query_a(l, r, 1, 1, n) / (r - l + 1), 2)));
        }
    }
    return 0;
}
