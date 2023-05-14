#include<iostream>
#include<algorithm>

using namespace std;
int n;

int Cn2(int);

int main() {
    long long sum = 0;
    cin >> n;
    int tmp, max = 0;
    int lateral[5001] = {0};

    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        lateral[tmp]++;
        if (tmp > max)max = tmp;
    }
    for (int i = 2; i <= max; ++i) {
        if (lateral[i] >= 2) {
            for (int j = 1; j < i; ++j) {
                if (lateral[j] >= 1) {
                    int k = i - j;
                    if (lateral[k] >= 1 && k <= j) {//这里必须判k比j小，因为3、4和4、3结果重复了！！！！
                        if (k == j) {
                            if (lateral[k] >= 2) {
                                sum += Cn2(lateral[j]) * Cn2(lateral[i]);
                                sum %= 1000000007;
//                                cout << i << " " << i << " " << j << " " << k << endl;
                            }
                        } else {
                            if (lateral[k] >= 1) {
                                sum += lateral[j] * Cn2(lateral[i]) * lateral[k];
                                sum %= 1000000007;
//                                cout << i << " " << i << " " << j << " " << k << endl;
                            }
                        }
                    }
                }
            }
        }
    }

    cout << sum << endl;
    return 0;
}

int Cn2(int k) {
    return k * (k - 1) / 2 % 1000000007;
}
//刚刚学习了如果想保证K<=J，还可以枚举j的时候让它枚举到<=(i/2)还可以减少时间复杂度！！！！！！！！//
// Created by lu'ren'jia'd's on 2022/2/16.
//

