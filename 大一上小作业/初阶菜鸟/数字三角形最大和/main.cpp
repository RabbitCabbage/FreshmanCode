#include <iostream>

using namespace std;
int n;

int main() {
    cin >> n;
    int array[n][n], sum[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            cin >> array[i][j];
            sum[i][j] = 0;
        }
        for (int k = i + 1; k < n; ++k) {
            array[i][k] = 0;
            sum[i][k] = 0;
        }
    }
    int sumj0 = 0;
    for (int k = 0; k < n; ++k) {
        sumj0 += array[k][0];
        sum[k][0] = sumj0;
    }//最左边一列的初始化
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < n; ++j) {
            int a = sum[i - 1][j] + array[i][j];
            int b = sum[i - 1][j - 1] + array[i][j];
            sum[i][j] = max(a, b);
        }
    }
    int max = sum[n - 1][0];
    for (int h = 0; h < n; ++h) {
        if (sum[n - 1][h] > max)max = sum[n - 1][h];
    }
    cout << max << endl;
    return 0;
}
