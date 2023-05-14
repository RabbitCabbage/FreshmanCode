//
// Created by lu'ren'jia'd's on 2022/5/14.
//

#include <iostream>

using namespace std;
const int maxn = 1e5 + 5;

struct edge {
    int from, to;
    long long value;
} e[maxn];

void merge(edge array[], int l, int r, int mid) {
    //把两段排好序，一段l~mid 另一段mid+1~r
    edge tmp[r - l + 1];
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (array[i].value > array[j].value)tmp[k++] = array[j++];
        else tmp[k++] = array[i++];
    }
    //k指向的是要放进去的空位子，ij指向要放的元素
    if (i == mid + 1)while (j <= r)tmp[k++] = array[j++];
    if (j == r + 1)while (i <= mid)tmp[k++] = array[i++];
    for (int p = 0, q = l; p < r - l + 1; p++, q++)
        array[q] = tmp[p];
}

void sort(edge array[], int start, int end) {
    if (start >= end)return;
    int mid = (start + end) >> 1;
    sort(array, start, mid);
    sort(array, mid + 1, end);
    merge(array, start, end, mid);
}

int n;
int father[maxn];
long long scale[maxn];//某个节点所在的连通块的规模
long long sum = 0;

void init() {
    for (int i = 0; i <= n; ++i) {
        father[i] = i;
        scale[i] = 1;
    }
}

int find_father(int x) {
    if (father[x] == x)return x;
    else return father[x] = find_father(father[x]);
}

void unit(int x, int y, long long value) {
    x = find_father(x);
    y = find_father(y);
    if (x == y) {
        sum += value;
        return;
    }
    father[x] = y;
    //连接这两块，要用到a*b条边
    sum += value + (value + 1) * (scale[x] * scale[y] - 1);
    //并且现在x的father是y
    scale[y] += scale[x];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        scanf("%d %d %lld", &e[i].from, &e[i].to, &e[i].value);
    }
    sort(e, 1, n - 1);
    init();
    for (int i = 1; i < n; ++i) {
        unit(e[i].from, e[i].to, e[i].value);
    }
    printf("%lld\n", sum);
    return 0;
}