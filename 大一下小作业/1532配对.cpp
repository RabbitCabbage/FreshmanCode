#include <iostream>

using namespace std;
const int maxn = 1e5 + 5;
const int maxm = 1e5 + 5;

int father[maxn << 1];

int find_father(int x) {
    if (father[x] == x)return x;
    else return father[x] = find_father(father[x]);
}

bool check(int x, int y) {
    x = find_father(x);
    y = find_father(y);
    return (x == y);
}

void merge(int x, int y) {
    x = find_father(x);
    y = find_father(y);
    father[x] = y;
}

int n, m, p, q;

int main() {
    scanf("%d %d %d %d", &n, &m, &p, &q);
    for (int i = 0; i < m + n; ++i)father[i] = i;
    for (int i = 0; i < p; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (!check(x, y))merge(x, y);
    }
    for (int i = 0; i < q; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        x = n - x, y = n - y;
        if (!check(x, y))merge(x, y);
    }
    int male=0,female=0;
    for (int i = 1; i <= n; ++i) {
        if(check(i,1))male++;
    }
    m=-m;
    for(int i=-1;i>=m;--i){
        if(check(n-i,n+1))++female;
    }
    printf("%d\n",min(female,male));
    return 0;
}