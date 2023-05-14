//
// Created by lu'ren'jia'd's on 2022/4/21.
//

#include <iostream>
#include <cmath>

using namespace std;
const int maxn = 3e5 + 5;
const int seed = 3;
const long long mod = 19260817;

struct node {
    long long hash;//从左到右
    long long rhash;//从右到左
    int size;
};

node tree[maxn << 2];
long long pow_array[maxn];
int n;


void pushup(int p) {
    tree[p].hash = tree[p << 1].hash * pow_array[tree[p << 1 | 1].size];
    tree[p].hash %= mod;
    tree[p].hash += tree[p << 1 | 1].hash;
    tree[p].hash %= mod;
    tree[p].rhash = tree[p << 1 | 1].rhash * pow_array[tree[p << 1].size];
    tree[p].rhash %= mod;
    tree[p].rhash += tree[p << 1].rhash;
    tree[p].rhash %= mod;
    tree[p].size = tree[p << 1].size + tree[p << 1 | 1].size;
}

void build(int p, int l, int r) {
    if (l == r) {
        tree[p].hash = tree[p].rhash = 0;
        tree[p].size = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

//每次把一个树从0改到1的时候hash要重算
void modify(int index, int p, int l, int r) {
    if (l == r) {
        tree[p].hash = 1;
        tree[p].rhash = 1;
        return;
    }
    int mid = (l + r) >> 1;
    if (index <= mid) modify(index, p << 1, l, mid);
    else modify(index, p << 1 | 1, mid + 1, r);
    pushup(p);
}

int query_size(int ql, int qr, int l, int r) {
    return min(qr, r) - max(ql, l) + 1;
}

long long query_hash(int ql, int qr, int p, int l, int r) {
    if (qr < ql)return 0;
    if (ql <= l && qr >= r)return tree[p].hash;
    int mid = (l + r) >> 1;
    long long res = 0;
    if (ql <= mid) {
        if (qr >= mid + 1) {
            //先询问左边，如果右边有东西的话说明左边需要乘上自己的size
            //右边没有就不用乘了
            res += query_hash(ql, qr, p << 1, l, mid) * pow_array[query_size(ql, qr, mid + 1, r)];
            res %= mod;
            res += query_hash(ql, qr, p << 1 | 1, mid + 1, r);
            res %= mod;
        } else {
            res += query_hash(ql, qr, p << 1, l, mid);
            res %= mod;
        }
    } else if (qr >= mid + 1) {
        res += query_hash(ql, qr, p << 1 | 1, mid + 1, r);
        res %= mod;
    }
    return res;
}

long long query_rhash(int ql, int qr, int p, int l, int r) {
    if (qr < ql)return 0;
    if (ql <= l && qr >= r)return tree[p].rhash;
    int mid = (l + r) >> 1;
    long long res = 0;
    if (qr >= mid + 1) {
        if (ql <= mid) {
            res += query_rhash(ql, qr, p << 1 | 1, mid + 1, r) * pow_array[query_size(ql, qr, l, mid)];
            res %= mod;
            res += query_rhash(ql, qr, p << 1, l, mid);
            res %= mod;
        } else {
            res += query_rhash(ql, qr, p << 1 | 1, mid + 1, r);
            res %= mod;
        }
    } else if (ql <= mid) {
        res += query_rhash(ql, qr, p << 1, l, mid);
        res %= mod;
    }
    return res;
}

int main() {
    pow_array[0] = 1;
    for (int i = 1; i < maxn; i++)pow_array[i] = pow_array[i - 1] * seed % mod;
    scanf("%d", &n);
    build(1, 1, n);
    for (int i = 1; i <= n; ++i) {
        int number;
        scanf("%d", &number);
        modify(number, 1, 1, n);
        int length = min(number - 1, n - number);
        if (length == 0)continue;
        long long l_to_r = query_hash(number - length, number - 1, 1, 1, n);
        long long r_to_l = query_rhash(number + 1, number + length, 1, 1, n);
        if (l_to_r != r_to_l) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}
