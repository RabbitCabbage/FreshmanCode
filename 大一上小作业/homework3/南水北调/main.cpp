#include <iostream>

using namespace std;
int n;

long maxx(long a, long b) { return (a > b ? a : b); }

long minn(long a, long b) { return (a < b ? a : b); }

int main() {
    cin >> n;
    long array[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> array[i][j];
        }
    }

    long maxarray[n][n];
    for (int i = n - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            if (i == n - 1 && j == n - 1) maxarray[i][j] = array[n - 1][n - 1];
            else if (i == n - 1) maxarray[n - 1][j] = maxx(array[n - 1][j], maxarray[n - 1][j + 1]);
            else if (j == n - 1) maxarray[i][n - 1] = maxx(array[i][n - 1], maxarray[i + 1][n - 1]);
            else {
                long bigger = maxx(maxarray[i + 1][j], maxarray[i][j + 1]);
                maxarray[i][j] = maxx(bigger, array[i][j]);
            }
        }
    }

    long minarray[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 && j == 0) minarray[i][j] = array[0][0];
            else if (i == 0) minarray[0][j] = minn(array[0][j], minarray[0][j - 1]);
            else if (j == 0) minarray[i][0] = minn(array[i][0], minarray[i - 1][0]);
            else {
                long smaller = minn(minarray[i - 1][j], minarray[i][j - 1]);
                minarray[i][j] = minn(smaller, array[i][j]);
            }

        }
    }

    long edgemax = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            if (edgemax < maxarray[i + 1][j + 1] - minarray[i][j]) edgemax = maxarray[i + 1][j + 1] - minarray[i][j ];
        }
    }
    cout << (edgemax / 2) << endl;
    return 0;
}
