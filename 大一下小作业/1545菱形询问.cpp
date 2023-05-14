#include<iostream>

using namespace std;
const int maxmn = 3e3 + 5;
const int max_ = maxmn * 2;
long long field[max_][max_]{0};
int m, n;
int trans;

inline long long read() {
    char ch = getchar();
    long long x = 0, sig = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')sig = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * sig;
}

int lowbit(int x) { return x & (-1 * x); }

pair<int, int> transfer(int x, int y) {
    --x, --y;
    return {x + y + 1, y - x + trans};
}

void build(int x, int y, long long number) {
    pair<int, int> p = transfer(x, y);
    x = p.first, y = p.second;
    for (int i = y; i < max_; i += lowbit(i)) {
        for (int j = x; j <= max_; j += lowbit(j)) {
            field[i][j] += number;
        }
    }
}

long long query_sum(int x, int y) {
    long long res = 0;
    for (int i = y; i > 0; i -= lowbit(i)) {
        for (int j = x; j > 0; j -= lowbit(j)) {
            res += field[i][j];
        }
    }
    return res;
}

long long query(int x, int y, int a) {
    pair<int, int> p_start = transfer(x, y - a);
    pair<int, int> p_end = transfer(x, y + a);
    return query_sum(p_end.first, p_end.second) - query_sum(p_end.first, p_start.second - 1) -
           query_sum(p_start.first - 1, p_end.second) + query_sum(p_start.first - 1, p_start.second - 1);
}

int main() {
    m = read(), n = read();
    trans = (m > n ? m : n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            long long tmp = read();
            build(j, i, tmp);
        }
    }
    int op;
    while (cin >> op) {
        if (op == 1) {
            int x = read(), y = read();
            long long d = read();
            build(x, y, d);
        } else {
            int x = read(), y = read(), a = read();
            printf("%lld%c", query(x, y, a), '\n');
        }
    }
    return 0;
}