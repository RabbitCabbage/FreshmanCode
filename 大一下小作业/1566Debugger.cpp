//
// Created by lu'ren'jia'd's on 2022/5/5.
//

#include <iostream>

using namespace std;
const int maxn = 4e6 + 5;
long long record[maxn << 1];
long long num1[maxn];
long long num2[maxn];
int op[maxn];
int father[maxn << 1];//每次询问有两个数字

void merge(long long array[], int l, int r) {
    if (l == r)return;
    int mid = (l + r) >> 1;
    int start = l, end = r;
    int i = l, j = mid + 1, k = 1;
    long long tmp[r - l + 2];
    while (i <= mid && j <= r) {
        if (array[i] < array[j])tmp[k++] = array[i++];
        else tmp[k++] = array[j++];
    }
    if (i > mid) {
        while (j <= r)tmp[k++] = array[j++];
    } else if (j > r) {
        while (i <= mid)tmp[k++] = array[i++];
    }
    for (int q = start, s = 1; q <= end; ++q, ++s)array[q] = tmp[s];
}

void sort(long long array[], int l, int r) {
    if (l >= r)return;
    int mid = (l + r) >> 1;
    sort(array, l, mid);
    sort(array, mid + 1, r);
    merge(array, l, r);
}

void unique(long long array[], int l, int &r) {
    int i = l, j = 0;
    array[++j] = array[i];
    while (i <= r) {
        while (array[j] == array[i])++i;
        if (i <= r)array[++j] = array[i];
    }
    r = j;
}

int index(long long x, long long array[], int l, int r) {
    int mid;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (array[mid] == x)return mid;
        else if (array[mid] > x)r = mid - 1;
        else l = mid + 1;
    }
    return l;
}

void init(int x) {
    for (int i = 0; i <= x; ++i)father[i] = i;
}

int find_father(int x) {
    if (father[x] == x)return x;
    else return father[x] = find_father(father[x]);
}

void unit(int x, int y) {
    x = find_father(x);
    y = find_father(y);
    father[y] = x;
}

bool check(int x, int y) {
    return find_father(x) == find_father(y);
}

int t, n;

int main() {
    scanf("%d\n", &t);
    while (t--) {
        bool flag = false;
        scanf("%d\n", &n);
        init(n << 1);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld %lld %d", &num1[i], &num2[i], &op[i]);
            record[2 * i - 1] = num1[i];
            record[2 * i] = num2[i];
        }
        int count = n << 1;
        sort(record, 1, count);
        unique(record, 1, count);
        for (int i = 1; i <= n; ++i) {
            if (op[i] == 1) {
                num1[i] = index(num1[i], record, 1, count);
                num2[i] = index(num2[i], record, 1, count);
                unit(num1[i], num2[i]);
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (op[i] == 0) {
                num1[i] = index(num1[i], record, 1, count);
                num2[i] = index(num2[i], record, 1, count);
                if (check(num1[i], num2[i])) {
                    printf("%s", "NO\n");
                    flag = true;
                    break;
                }
            }
        }
        if (!flag)printf("%s", "YES\n");
    }
    return 0;
}

#include <iostream>
#include <cstring>

using namespace std;
const int maxn = 4e6 + 5;
const int mod = 7e6 + 3;
long long num1[maxn];
long long num2[maxn];
int op[maxn];
int father[mod + 1];
long long hash_table[mod + 1];

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

void init(int x) {
    memset(hash_table, 0, sizeof(hash_table));
    for (int i = 0; i <= x; ++i)father[i] = i;
}

int find_father(int x) {
    if (father[x] == x)return x;
    else return father[x] = find_father(father[x]);
}

void unit(int x, int y) {
    x = find_father(x);
    y = find_father(y);
    father[y] = x;
}

bool check(int x, int y) {
    return find_father(x) == find_father(y);
}

int hash_(long long x) {
    long long first_hash = x % mod;
    if (!hash_table[first_hash]) {
        hash_table[first_hash] = x;
        return first_hash;
    } else if (hash_table[first_hash] == x)return first_hash;
    long long second_hash = first_hash + 1;
    int step = 1;
    while (1) {
        if (!hash_table[second_hash]) {
            hash_table[second_hash] = x;
            return second_hash;
        } else if (hash_table[second_hash] == x)return second_hash;
        step++;
        second_hash = (first_hash + (step & 1 ? -1 : 1) * (step >> 1) % mod + mod) % mod;
        // hh = ((h + (i & 1 ? -1 : 1) * (i >> 1)) % cap + cap) % cap;
    }
}

int t, n;

int main() {
    scanf("%d\n", &t);
    while (t--) {
        bool flag = false;
        n = read();
        init(mod);
        for (int i = 1; i <= n; ++i) {
            num1[i] = read();
            num2[i] = read();
            op[i] = read();
            //我们希望在这里给一个独一无二的index，把它放进去
            num1[i] = hash_(num1[i]);
            num2[i] = hash_(num2[i]);
        }
        for (int i = 1; i <= n; ++i) {
            if (op[i] == 1) {
                unit(num1[i], num2[i]);
            }
        }
        for (int i = 1; i <= n; ++i)
            if (op[i] == 0) {
                if (check(num1[i], num2[i])) {
                    puts("NO\n");
                    flag = true;
                    break;
                }
            }
        if (!flag)puts("YES\n");
    }
    return 0;
}