#include<iostream>

using namespace std;

void anti_merge(int left, int right, int array[], int k_times, int usage);

int n, k;

int main() {
    cin >> n >> k;
    int sequence[n];
    for (int i = 0; i < n; i++)sequence[i] = i + 1;
    if (k == 1) {
        cout << sequence[0];
        for (int i = 1; i < n; ++i)cout << " " << sequence[i];
        cout << '\n';
    } else if (k % 2 == 0)cout << -1 << endl;
    else {
        anti_merge(0, n - 1, sequence, k, 2 * n - 1);//usage就是有解的最大使用次数
        if (sequence[0]) {
            cout << sequence[0];
            for (int i = 1; i < n; ++i)cout << " " << sequence[i];
            cout << '\n';
        } else cout << -1 << endl;
    }
    return 0;
}

void anti_merge(int left, int right, int array[], int k_times, int usage) {
    if (k_times > usage) array[0] = 0;
    else {
        k_times -= 2;
        if (left == right - 1) {
            swap(array[left], array[right]);
        } else {
            int mid = (left + right + 1) / 2;
            swap(array[mid - 1], array[mid]);
            if (k_times <= 2 * (mid - left) - 1)
                anti_merge(left, mid - 1, array, 2 * (mid - left) - 1, 2 * (mid - left) - 1);
            if (k_times > 2 * (mid - left) - 1) {
                anti_merge(left, mid - 1, array, 2 * (mid - left) - 1, 2 * (mid - left) - 1);
                anti_merge(mid, right, array, k_times - 2 * (mid - left) + 1, 2 * (right - mid + 1) - 1);
            }
        }
    }
}

