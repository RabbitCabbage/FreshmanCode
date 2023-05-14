#include<iostream>
#include <cmath>
//利用前缀和，sum[k]^sum[j]就相当于从k~j的异或和
//利用前缀和来解决这道题，就是说寻找以i作为分界线的左右各最大值
//方法就是 l[i]要么是取sum[i]与其他的某个sum[j]异或的最大值
//要么就是取前面出现的更大的所以就和l[i]取一个max
using namespace std;
const int maxn = 4e5+2;
int n;

int l_tree[31 * maxn][2]{0};
int r_tree[31 * maxn][2]{0};
int l_value[31 * maxn];
int r_value[31 * maxn];
int l_tot = 1;
int r_tot = 1;

void insert(int tree[31 * maxn][2], int number, int &tot, int value[]) {
    int u = 0;
    for (int i = 30; i >= 0; --i) {
        int v = (number >> i) & 1;
        if (!tree[u][v]) {
            tree[u][v] = tot;
            value[tot] = 0;
            ++tot;
        }
        u = tree[u][v];
    }
    value[u] = number;//标记好到这一个节点是这个数字，等会好找；
}

int find_max(int tree[31 * maxn][2], int number, const int value[]) {
    int u = 0;
    for (int i = 30; i >= 0; --i) {
        int v = (number >> i) & 1;
        if (tree[u][v ^ 1])u = tree[u][v ^ 1];
        else u = tree[u][!(v ^ 1)];
    }
    return value[u] ^ number;//直接返回的是最大的结果
}

int main() {
    scanf("%d", &n);
    int sum[n], tmp;
    scanf("%d", &sum[0]);
    for (int i = 1; i < n; ++i) {
        scanf("%d", &tmp);
        sum[i] = sum[i - 1] ^ tmp;
    }
    int l[n], r[n];//分别代表的是i作为分界线左右所有段的异或值中的最大值
    //规定l[i]包括第i个，r[i]不包括i
    l[0] = sum[0], r[n - 1] = 0;
    insert(l_tree, sum[0], l_tot, l_value);
    insert(r_tree, sum[n - 1], r_tot, r_value);
    for (int i = 1, j = n - 2; i < n, j >= 0; ++i, --j) {
        //i表示的是以i作为分界线，左边i个里面的所有异或段的最大值
        //j表示的时以j作为分界线，从j右边的所有异或段的最大值
        l[i] = max(l[i - 1], find_max(l_tree, sum[i], l_value));
        insert(l_tree, sum[i], l_tot, l_value);
        r[j] = max(r[j + 1], find_max(r_tree, sum[j], r_value));
        insert(r_tree, sum[j], r_tot, r_value);
    }
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        answer = max(answer, l[i] + r[i]);
    }
    printf("%d%c", answer, '\n');
    return 0;
}