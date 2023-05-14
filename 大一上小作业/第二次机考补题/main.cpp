#include<iostream>

using namespace std;
int m, n, a, b;

bool check(long long answer, long long sum[][500]);

int main() {
    freopen(".out", "w", stdout);
    cin >> n >> m >> a >> b;
    long long array[n][m], sum[n][500];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> array[i][j];
            if (i == 0 && j == 0)sum[i][j] = array[i][j];
            else if (i == 0)sum[i][j] = sum[i][j - 1] + array[i][j];
            else if (j == 0)sum[i][j] = sum[i - 1][j] + array[i][j];
            else { sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + array[i][j]; }//前缀和
        }
    }
    long long sum_max = sum[n - 1][m - 1];


//二分法寻找合适的答案，二分答案；
    long long left = 0, right = sum_max;
    while (right - left > 1) {
        long long mid = (left + right) / 2;
        bool check_answer = check(mid, sum);
        if (check_answer)left = mid;
        else right = mid;
    }
    cout << left << endl;
    return 0;
}

bool check(long long answer, long long sum[][500]) {
    bool check_answer;
    int row_high = 0, row_low = 0;
    int column = 0, column_left = 0;
    int count_b, count_a = 0;
    while (1) {
        long long sum_use[m];
        for (int j = 0; j < m; ++j) {
            if (row_low == row_high) {
                if (row_low == 0)sum_use[j] = sum[0][j];
                else sum_use[j] = sum[row_low][j] - sum[row_low - 1][j];
            } else {
                if (row_high == 0)sum_use[j] = sum[row_low][j];
                else sum_use[j] = sum[row_low][j] - sum[row_high - 1][j];
            }

        }
        //求出需要用到的形式的前缀和；
        count_b = 0;
        while (1) {
            if (column == m) {
                column = 0;
                column_left = 0;
                break;
            }
            long long temp;
            if (column_left == 0)temp = sum_use[column];
            else temp = sum_use[column] - sum_use[column_left];

            if (temp < answer)
                column++;
            else {
                count_b++;
                column_left = column;
                column++;
            }
        }
        if (count_b >= b) {
            count_a++;
            row_low++;
            row_high = row_low;
        } else {
            row_low++;
        }
        if (row_low == n)break;
    }
    if (count_a >= a)check_answer = true;
    else check_answer = false;
    return check_answer;
}

