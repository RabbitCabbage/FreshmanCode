//
// Created by lu'ren'jia'd's on 2022/4/13.
//

#include <iostream>

using namespace std;
const int maxn = 2e5 + 3;
int array[maxn];

void QuickSorting(int a[], int l, int r) {
    int mid = a[(l + r) / 2];
    int head = l, rear = r;
    do {
        while (a[head] < mid)head++;
        while (a[rear] > mid)rear--;
        if (head <= rear) {
            swap(a[head], a[rear]);
            head++;
            rear--;
        }
    } while (head <= rear);
    if (l < rear) QuickSorting(a, l, rear);
    if (head < r) QuickSorting(a, head, r);
}

int main() {
    int n, c;
    scanf("%d %d", &n, &c);
    if (c < 0)c = -c;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &array[i]);
    }
    QuickSorting(array, 0, n - 1);
    int res = 0;
    int i = 0, j = 1;
    while (i < n) {
        if (array[n - 1] - array[i] < c)break;
        //如果说i已经太大了，就不用往后找了
        while (j < n) {
            if (array[j] - array[i] == c) {
                int num_i = 0, num_j = 0;
                int a = array[i], b = array[j];
                while (array[i] == a)++num_i, ++i;
                while (array[j] == b)++num_j, ++j;
                //统计有多少这么大的i j
                res += num_i * num_j;
                //这里出来的时候已经不等于ab了
                //并且j也没有再加下去的必要了，因为再往后只会更大不会更小
                break;
            } else if (array[j] - array[i] > c) ++i;
            else ++j;
        }
    }
    printf("%d%c", res, '\n');
    return 0;
}