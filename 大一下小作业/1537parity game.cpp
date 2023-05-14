//
// Created by lu'ren'jia'd's on 2022/4/27.
//

#include <iostream>

using namespace std;

//记下前缀和中是奇是偶s[i]，
//如果我说i到j有奇数个1，也即是s[i-1]s[j]的奇偶性不同
//如果我说i到j有偶数个1，也即是s[i-1]s[j]的奇偶性是相同的
//这里要维护和i个相同的以及不同的，因此将并查集扩展到两倍
//father[i]表示的是与自己相同的集合的father，
//father[i+n]表示的是与自己不同的father。里面放的也是j+n
const long long maxn = 1e9 + 5;
const int maxm = 5e4 + 5;
int father[maxm << 2];

int find_father(int x) {
    if (father[x] == x)return x;
    return father[x] = find_father(father[x]);
}

void merge(int x, int y) {
    x = find_father(x);
    y = find_father(y);
    if (x == y)return;
    else father[x] = y;
}

bool check(int x, int y) {
    return find_father(x) == find_father(y);
}

long long n;
int m;
struct Q {
    long long l, r;
    char parity;
};
Q query[maxm];
long long record[maxm << 1];

void sort(long long array[], int l, int r) {
    if (l >= r)return;
    int start = l, end = r;
    long long pivot = array[start];
    while (l < r) {
        while (l < r && array[r] >= pivot)--r;
        while (l < r && array[l] <= pivot)++l;
        if (l < r) {
            long long tmp = array[l];
            array[l] = array[r];
            array[r] = tmp;
        }
    }
    array[start] = array[l];
    array[l] = pivot;
    sort(array, start, l - 1);
    sort(array, l + 1, end);
}

void unique(long long array[], int l, int &r) {
    int i = l, j = l;
    while (i <= r) {
        while (i <= r && array[i] == array[j])++i;
        if (i <= r)array[++j] = array[i];
    }
    r = j;
}

int unique_index(long long x, long long array[], int l, int r) {
    //找到unique之后的数组应该是多少下标
    if (array[l] == x)return l;
    if (array[r] == x)return r;
    int mid = (l + r) >> 1;
    while (l < r) {
        mid = (l + r) >> 1;
        if (array[mid] == x)return mid;
        if (array[mid] > x)r = mid - 1;
        else l = mid + 1;
    }
    return l;
}

int main() {
    scanf("%lld\n%d\n", &n, &m);
    for (int i = 0; i < (maxm << 2); ++i)father[i] = i;
    char tmp[5];
    for (int i = 1; i <= m; ++i) {
        scanf("%lld %lld %s", &query[i].l, &query[i].r, tmp);
        query[i].parity = tmp[0];
        record[2 * i - 1] = (--query[i].l);
        record[2 * i] = query[i].r;
    }
    int count = 2 * m;
    sort(record, 1, count);
    unique(record, 1, count);
    for (int i = 1; i <= m; ++i) {
        query[i].l = unique_index(query[i].l, record, 1, count);
        query[i].r = unique_index(query[i].r, record, 1, count);
    }
    int partition = count + 1;
    //这个partition的目的是分开奇偶性相同的father集合和奇偶性不同的father集合
    //现在经过离散化之后在query里面的元素最大也就是count，不会超过count的范围，因此这里用count就够作分割线
    for (int i = 1; i <= m; ++i) {
        if (query[i].parity == 'e') {
            //我现在断言，lr之间的1的个数是偶数,也即是他们奇偶性相同
            if (check(query[i].l, query[i].r + partition)) {
                //如果说现在他们已经被确定为奇偶性需要不同
                //和我相同的与和你不同的是一个集合，也即是与我相同的必将与你不同，就是奇偶性不通
                printf("%d\n", i - 1);
                return 0;
            } else {
                merge(query[i].l, query[i].r);
                merge(query[i].l + partition, query[i].r + partition);
                //这个意思就是说，把他俩放到了表示相同奇偶性的集合里面
                //与l奇偶性同的与r奇偶性同的合并在一起
                //与l奇偶性不同的与r奇偶性不同的合并在一起
            }
        } else {
            if (check(query[i].l, query[i].r)) {
                //如果说现在他们已经被确定为奇偶性需要相同
                printf("%d\n", i - 1);
                return 0;
            } else {
                merge(query[i].l, query[i].r + partition);
                merge(query[i].l + partition, query[i].r);
                //这个意思就是说，把他俩放到了表示不同奇偶性的集合里面
                //与l奇偶性不同的与r奇偶性同的合并在一起
                //与l奇偶性同的与r奇偶性不同的合并在一起
            }
        }
    }
    printf("%d\n", m);
    return 0;
}