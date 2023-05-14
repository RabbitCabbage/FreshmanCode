//
// Created by lu'ren'jia'd's on 2022/4/20.
//

#include <iostream>

using namespace std;
const int maxn = 1e5 + 5;
int tree[maxn << 2];
int tag[maxn << 2]{0};
int number[maxn];
int answer[maxn];
int n;

int min(int a, int b) {
    return (a < b ? a : b);
}

void pushup(int p) {
    tree[p] = min(tree[p << 1], tree[p << 1 | 1]);
}

void build(int p, int l, int r) {
    if (l == r) {
        tree[p] = number[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void pushdown(int p, int l, int r) {
    if (l == r) {
        tag[p] = 0;
    } else {
        tag[p << 1] += tag[p];
        tag[p << 1 | 1] += tag[p];
        tree[p << 1] -= tag[p];
        tree[p << 1 | 1] -= tag[p];
        tag[p] = 0;
    }
}

void modify(int ml, int mr, int p, int l, int r) {
    if (ml > mr)return;
    if (tag[p])pushdown(p, l, r);
    if (ml <= l && mr >= r) {
        tree[p] -= 1;
        tag[p] += 1;
        return;
    }
    int mid = (l + r) >> 1;
    if (ml <= mid)modify(ml, mr, p << 1, l, mid);
    if (mr >= mid + 1)modify(ml, mr, p << 1 | 1, mid + 1, r);
    pushup(p);
}

void modify_dot(int index, int p, int l, int r) {
    if (l == r) {
        tree[p] = maxn + 1;
        return;
    }
    if (tag[p])pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (index <= mid)modify_dot(index, p << 1, l, mid);
    if (index >= mid + 1)modify_dot(index, p << 1 | 1, mid + 1, r);
    pushup(p);
}

int find0(int p, int l, int r) {
    if (l == r)return l;
    if (tag[p])pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (tree[p << 1 | 1] == 0)return find0(p << 1 | 1, mid + 1, r);
    else return find0(p << 1, l, mid);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &number[i]);
    }
    build(1, 1, n);
    for (int i = 1; i <= n; ++i) {
        int index = find0(1, 1, n);
        answer[index] = i;
        modify_dot(index, 1, 1, n);
        modify(index + 1, n, 1, 1, n);
//        for (int J = 1; J <= n; ++J) printf("%d%c", answer[J], ' ');
//        printf("%c", '\n');
    }
    for (int i = 1; i <= n; ++i) printf("%d%c", answer[i], ' ');
    printf("%c", '\n');
    return 0;
}
//2 4 1 3
//0 1 0 2