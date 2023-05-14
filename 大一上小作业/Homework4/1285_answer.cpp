#include <bits/stdc++.h>

using namespace std;
int a[100005] = {0};

int main() {
    void Sorting(int head, int tail, int step);
    int n, k;
    cin >> n >> k;
    if (!(k % 2) || k >= 2 * n)
        cout << "-1" << endl;
    else {
        for (int i = 0; i < n; i++)
            a[i] = i + 1;
        Sorting(0, n, k);
        for (int i = 0; i < n; i++)
            cout << a[i] << " ";
        cout << endl;
    }
    return 0;
}

void Sorting(int head, int tail, int step) {
    if (step == -1)
        return;
    if (tail - head == 2) {
        if (step == 1)
            return;
        if (step == 3) {
            int temp = a[head];
            a[head] = a[tail - 1];
            a[tail - 1] = temp;
            return;
        }
    }
    if (tail - head == 3) {
        if (step == 1)
            return;
        if (step == 3) {
            int temp = a[head];
            a[head] = a[head + 1];
            a[head + 1] = temp;
            return;
        }
        if (step == 5) {
            int temp = a[head + 1];
            a[head + 1] = a[head + 2];
            a[head + 2] = temp;
            return;
        }
    }
    int mid = (head + tail) / 2;
    int l_max = (mid - head) * 2 - 1;
    if (step == 3) {
        int temp = a[mid];
        a[mid] = a[mid - 1];
        a[mid - 1] = temp;
        return;
    }
    if (l_max >= step - 2)
        Sorting(head, mid, step - 2);
    else {
        Sorting(head, mid, l_max);
        Sorting(mid, tail, step - l_max - 1);
    }
}