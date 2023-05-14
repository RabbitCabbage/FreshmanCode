#include <iostream>

using namespace std;
int n, k;

int main() {
    cin >> n >> k;
    long long array[n], sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
        sum += array[i];
    }
    if (sum < k) {
        cout << "0" << endl;
        return 0;
    }
    if (sum == k) {
        cout << "1" << endl;
        return 0;
    }
    long long  max = sum / k + 1;
    long long min = 1;
    while (min + 1 < max) {
        long long test = (min + max) / 2;
        long long test_k = 0;
        for (int i = 0; i < n; ++i)test_k += array[i] / test;
        if (test_k >= k) {//说明还可以再切大殿没事
            min = test;
        } else max = test;
    }
    cout << min << endl;
    return 0;
}