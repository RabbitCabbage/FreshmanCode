#include<iostream>

using namespace std;
long long n, Q;
struct edge {
    long long from;
    long long to;
    long long pre;
};

void dfs_sequence(long long x, long long pa, long long in_step[], long long size[], long long last[], edge chain[]);

int main() {
    cin >> n >> Q;
    long long last[n + 1];
    for (int i = 0; i <= n; ++i) {
        last[i] = 0;
    }
    long long N = 2 * n - 1;
    edge chain[N];
    int from_, to_;

    for (int i = 1; i < N; i++) {
        cin >> from_ >> to_;
        chain[i].from = from_;
        chain[i].to = to_;
        chain[i].pre = last[from_];
        last[from_] = i;
        ++i;
        chain[i].from = to_;
        chain[i].to = from_;
        chain[i].pre = last[to_];
        last[to_] = i;
    }//以上没有问题

    long long in_step[n];//记录下每一个点的
    long long size[n];
    dfs_sequence(1, 0, in_step, size, last, chain);
    for (int j = 0; j < Q; ++j) {
        long long ancestor, spring_off;
        cin >> spring_off >> ancestor;
        long long l = in_step[ancestor], r = in_step[ancestor] + size[ancestor] - 1;
        if (l < in_step[spring_off] && in_step[spring_off] <= r)cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}

void dfs_sequence(long long x, long long pa, long long in_step[], long long size[], long long last[], edge chain[]) {
    static long long step = 0;
    in_step[x] = ++step;
    size[x] = 1;
    for (long long i = last[x]; i; i = chain[i].pre) {
        long long to = chain[i].to;
        if (to != pa) {
            dfs_sequence(to, x, in_step, size, last, chain);
            size[x] += size[to];
        }
    }

}//
// Created by lu'ren'jia'd's on 2021/11/20.
//

