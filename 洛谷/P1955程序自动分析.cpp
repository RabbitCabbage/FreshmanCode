//
// Created by lu'ren'jia'd's on 2022/4/30.
//
#include<iostream>
//这题不能用种类并查集啊啊
//如果说2！=3 1！=3 就会把23放在相同的种类里，这是不对的
using namespace std;
const int maxn = 1e6 + 5;
int father[maxn << 1];

void merge_array(long long array[], int l, int r) {
    int mid = (l + r) >> 1;
    long long tmp[r - l + 1];
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (array[i] < array[j])tmp[k++] = array[i++];
        else tmp[k++] = array[j++];
        //ij分别指向要放进去的，k指向下一个空位
    }
    if (i == mid + 1) {
        while (j <= r)tmp[k++] = array[j++];
    } else while (i <= mid)tmp[k++] = array[i++];
    for (int q = l, p = 0; q <= r; ++q, ++p)array[q] = tmp[p];
}

void merge_sort(long long array[], int l, int r) {
    if (l == r)return;
    int mid = (l + r) >> 1;
    merge_sort(array, l, mid);
    merge_sort(array, mid + 1, r);
    merge_array(array, l, r);
}

void unique(long long array[], int l, int &r) {
    int i = l, j = 0;
    array[++j] = array[i];
    while (i <= r) {
        while (array[i] == array[j])++i;
        if (i <= r) array[++j] = array[i];//找到一个不一样的
    }
    r = j;
}

int index(long long x, const long long array[], int l, int r) {
    int mid;
    while (l < r) {
        mid = (l + r) >> 1;
        if (array[mid] == x)return mid;
        else if (array[mid] > x)r = mid - 1;
        else l = mid + 1;
    }
    return l;
}

void init(int x) {
    x <<= 1;
    for (int i = 0; i <= x; ++i)father[i] = i;
}

int find_father(int x) {
    if (x == father[x])return x;
    else return father[x] = find_father(father[x]);
}

bool check(int x, int y) {
    return find_father(x) == find_father(y);
}

void merge(int x, int y) {
    x = find_father(x);
    y = find_father(y);
    father[x] = y;
}

int t, n;
long long record[maxn << 1];
long long num1[maxn];
long long num2[maxn];
int op[maxn];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld %lld %d", &num1[i], &num2[i], &op[i]);
            record[2 * i - 1] = num1[i], record[2 * i] = num2[i];
        }
        int count = n << 1;
        merge_sort(record, 1, count);
        unique(record, 1, count);
        //我们想象一下，他总共会有n次询问，每次涉及到两个数字，那么也就是说最多会有2*n个数字
        //所以我们的father开的小了
        init(n << 1);
//        init(n);
        bool flag = false;
        for (int i = 1; i <= n; ++i) {
            if (op[i] == 1) {
                num1[i] = index(num1[i], record, 1, count);
                num2[i] = index(num2[i], record, 1, count);
                merge(num1[i], num2[i]);
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
