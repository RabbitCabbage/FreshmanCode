//
// Created by lu'ren'jia'd's on 2022/4/13.
//

#include<iostream>
#include <cstring>

using namespace std;
const int maxn = 105;
const int maxm = 3e4 + 5;
const int seed = 41519;
const int mod = 1e9 + 7;
int n, m;
int nl[maxn];
int size_[maxn];//子树规模
int el[maxn * 2 - 2];//-1代表后面没有边了
int to[maxn * 2 - 2];
long long tree[maxn];//所有节点的hash值；
long long treehash[maxm];//所有树的hash值
bool visited[maxn]{false};
int total = 0;//边的编号
void add(int from, int to_) {
    to[total] = to_;
    el[total] = nl[from];
    nl[from] = total;
    ++total;
}

void sort(long long array[], int l, int r) {
    if (l >= r)return;//说明只有一个元素，不用排了
    long long chosen = array[l];
    int start = l, end = r;
    while (l < r) {
        //在这次进入循环时，r指向的是一个比自己更大或者相等的元素
//        while (array[l] <= chosen && l < r)++l;
//        while (array[r] >= chosen && l < r)--r;
        //上面这种写法出循环的时候总是指向一个比自己更大的元素，不能直接交换
        while (array[r] >= chosen && l < r)--r;
        while (array[l] <= chosen && l < r)++l;
        //把两句话调换一下位置，就可以保证出循环的时候l==r指向的是比主元更小的元素
        if (l < r) {
            long long tmp = array[l];
            array[l] = array[r];
            array[r] = tmp;
        }
    }
    array[start] = array[l];
    array[l] = chosen;//把主元放到它应该在的位置上
    //现在主元前面的都比自己小，后面的都比自己大
    sort(array, start, l - 1);
    sort(array, l + 1, end);
}

void dfs(int cur) {
    size_[cur] = 1;
    tree[cur] = 1;
    visited[cur] = true;
    int next_edge = nl[cur];
    long long son_hash[maxn];
    int son = 0;
    while (next_edge != -1) {
        if (!visited[to[next_edge]]) {
            dfs(to[next_edge]);
            size_[cur] += size_[to[next_edge]];
            son_hash[son++] = tree[to[next_edge]];
        }
        next_edge = el[next_edge];
    }
    //现在所有子树的hash值已经求好了，然后size也求好了
    sort(son_hash, 0, son - 1);
    for (int i = son - 1; i >= 0; --i) {
        tree[cur] *= seed;
        tree[cur] += son_hash[i];
        tree[cur] %= mod;
    }
    tree[cur] *= size_[cur];
    tree[cur] %= mod;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        memset(nl, -1, sizeof(nl));
        total = 0;
        int root;
        scanf("%d", &root);
        int a, b;
        for (int j = 0; j < n - 1; ++j) {
            scanf("%d %d", &a, &b);
            add(a, b);
            add(b, a);
        }
        memset(visited, false, sizeof(visited));
        dfs(root);
        treehash[i] = tree[root];
    }
    sort(treehash, 0, m - 1);
    int max = 0, i = 0;
    while (i < m) {
        int cnt = 0;
        long long tmp = treehash[i];
        while (tmp == treehash[i])++i, ++cnt;
        if (cnt > max)max = cnt;
    }
    printf("%d%c", max, '\n');
    return 0;
}