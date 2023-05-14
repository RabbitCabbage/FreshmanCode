//
// Created by lu'ren'jia'd's on 2022/5/5.
//

#include <iostream>

using namespace std;

int n, m, cloud;
const int maxm = 1e5 + 5;
const int maxn = 1e3 + 5;

struct edge {
    int x, y, l;
} e[maxm];
int fraction;
long long cost;


void merge(edge array[], int l, int r) {
    if (l == r)return;
    int mid = (l + r) >> 1;
    int start = l, end = r;
    int i = l, j = mid + 1, k = 1;
    edge tmp[r - l + 2];
    while (i <= mid && j <= r) {
        if (array[i].l < array[j].l)tmp[k++] = array[i++];
        else tmp[k++] = array[j++];
    }
    if (i > mid) {
        while (j <= r)tmp[k++] = array[j++];
    } else if (j > r) {
        while (i <= mid)tmp[k++] = array[i++];
    }
    for (int q = start, s = 1; q <= end; ++q, ++s)array[q] = tmp[s];
}

void sort(edge array[], int l, int r) {
    if (l >= r)return;
    int mid = (l + r) >> 1;
    sort(array, l, mid);
    sort(array, mid + 1, r);
    merge(array, l, r);
}

int father[maxn];

void init() {
    for (int i = 0; i <= n; ++i)father[i] = i;
    fraction = n;
    cost = 0;
}

int find_father(int x) {
    if (father[x] == x)return x;
    else return father[x] = find_father(father[x]);
}

void unit(int index) {
    int x, y;
    x = find_father(e[index].x);
    y = find_father(e[index].y);
    if (x == y)return;
    else {
        father[x] = y;
        fraction--;
        cost += e[index].l;
    }
}

bool check(int index) {
    int x, y;
    x = find_father(e[index].x);
    y = find_father(e[index].y);
    return (x == y);
}

int main() {
    scanf("%d %d %d", &n, &m, &cloud);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &e[i].x, &e[i].y, &e[i].l);
    }
    sort(e, 1, m);
    init();
    if (fraction == cloud) {
        printf("%d\n", 0);
        return 0;
    }
    for (int i = 1; i <= m; ++i) {
        if (!check(i))unit(i);
        if (fraction == cloud) {
            printf("%lld\n", cost);
            return 0;
        }
    }
    printf("%s", "No Answer\n");
    return 0;
}