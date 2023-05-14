#include <iostream>

using namespace std;
const int maxn = 1e5 + 4;
int N;
int a_[maxn];

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
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)scanf("%d", &a_[i]);
    QuickSorting(a_, 0, N - 1);
    for (int i = 0; i < N; ++i)printf("%d%c", a_[i], ' ');
    printf("%c", '\n');
    return 0;
}