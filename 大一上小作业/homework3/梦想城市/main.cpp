/*#include <iostream>

using namespace std;
int n, m;

int main() {
    cin >> n >> m;
    int initial[n], adder[n];
    for (int i = 0; i < n; ++i) {
        cin >> initial[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> adder[i];
    }
    int adder[m][n];
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            adder[j][i] = initial[i] + adder[i] * j;
        }
    }
    int max = 0, benefit = 0;
    for (int k = m - 1; k >= 0; --k) {
        int h, max_index = 0;
        for (h = 0; h < n; ++h) {
            if (adder[k][h] > max) {
                max = adder[k][h];
                max_index = h;
            } else if (adder[k][h] == max) {
                //此时的max_index 还是上一次的max
                if (adder[k - 1][max_index] > adder[k - 1][h])
                    max_index = h;
            }
        }
        benefit += max;
        max = 0;
        for (int j = 0; j < m; ++j) {
            adder[j][max_index] = 0;
        }
    }
    cout << benefit << endl;
    return 0;
}
#include<iostream>

using namespace std;
int n, m;
int f[2500][2500];

int main() {
    cin >> n;
    cin >> m;
    int initial[n], adder[n];
    for (int i = 0; i < n; ++i) {
        cin >> initial[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> adder[i];
    }
    for (int b = 0; b <= n - 1; ++b) {
        int exchangetimes = 0;//记录交换次数，如果接下来的一次检索里买有进行交换，就可以停止
        for (int c = 0; c <= n - 1 - b - 1; ++c) {
            if (adder[c] > adder[c + 1]) {
                int temp2 = adder[c];
                adder[c] = adder[c + 1];
                adder[c + 1] = temp2;
                int temp1 = initial[c];
                initial[c] = initial[c + 1];
                initial[c + 1] = temp1;
                exchangetimes++;
            }
        }
        if (exchangetimes == 0) break;
    }//升序排列
    if (m >= n) {
        int sum = 0;
        for (int i = m, j = n - 1; i >= 1 && j >= 0; --i, --j) {
            sum += initial[j] + adder[j] * (i - 1);
        }
        cout << sum << endl;
    } else {
        for (int  k= 0; k < n; ++k) {
            f[0][k] = initial[0];
        }
        for (int j = 1; j < m; ++j) {
            for (int i = 1; i < n; ++i) {

                int a = f[i - 1][j - 1] + initial[i] + adder[i] * j;
                int b = f[i - 1][j];
                f[i][j] = max(a, b);
            }
        }
        //该return什么东西
        cout << f[n-1][m-1] << endl;
    }
    return 0;
}

int max(int a, int b) {
    return (a > b ? a : b);
}*/
#include<iostream>
#include<algorithm>

int m, n;
using namespace std;

int main() {
    cin >> n >> m;
    pair<int, int> p[n];

    for (int i = 0; i < n; ++i) {
        cin >> p[i].second;
    }//b is first based for comparing;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].first;
    }
    sort(p, p + n);
    if (m > n) {
        long long result = 0;
        for(int i=0;i<n;++i){
            result+=(p[i].second+p[i].first*(m-n+i));
        }
        cout << result << endl;
    } else {
        long long f[m + 1][n + 1];
        for (int i = 0; i < n + 1; ++i) {
            f[0][i] = 0;
        }
        for (int j = 1; j < m + 1; ++j) {
            f[j][0] = 0;
        }
        //j代表的是树，树是排好序的
        for (int j = 1; j < n+1; ++j) {//i j is 1 -based
            for (int i = 1; i < m+1; ++i) {
                long long a = f[i - 1][j - 1] + p[j - 1].first * (i - 1) + p[j - 1].second;
                long long b = f[i][j - 1];
                f[i][j] = max(a, b);
            }
        }
        cout << f[m][n] << endl;
    }
    return 0;
}