//
// Created by lu'ren'jia'd's on 2022/3/13.
#include <iostream>
#include <cmath>

using namespace std;
int n, m, column;

int gcd(int a, int b);

int main() {
//    cin >> n >> m;
    scanf("%d %d", &n, &m);
    column = (int) log(n) / log(2) + 1;
    int array[n], f[n][column];
    for (int i = 0; i < n; ++i) {
//        cin >> array[i];
        scanf("%d", &array[i]);
        f[i][0] = array[i];
    }
    for (int j = 1; j <= log(n) / log(2) + 1; ++j) {
        for (int i = 0; i + (1 << j) - 1 <= n; ++i) {
            f[i][j] = gcd(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
//            cout << "i = " << i << " j = " << j << " " << "f[i][j] = " << f[i][j] << endl;
        }
    }
    for (int i = 0; i < m; ++i) {
        int left, right, result;
//        cin >> left >> right;
        scanf("%d %d", &left, &right);
        --left, --right;
        if (left == right) {
            result = array[left];
        } else {
            int x = (int) (log(right - left + 1) / log(2));
            //two x cover the whole range of the array from left to right;
//            cout << "left = " << left << " right = " << right << " x = " << x << " gcd " << f[left][x]
//                 << " the start point = " << left + (1 << (x)) - 1 << " the value = " << f[left + (1 << (x)) - 1][x]
//                 << endl;
            result = gcd(f[left][x], f[right - (1 << (x)) + 1][x]);
        }
//        cout << result << ' ';
        printf("%d%c", result, ' ');
        int count = 0, prior_left = left, prior_right = right;
        right = n - 1;
        if (left < right - 1) {
            while (left < right - 1) {
                int mid = (left + right) / 2;
                int res;
                if (prior_left == mid)res = array[prior_left];
                else {
                    int y = (int) (log(mid - prior_left + 1) / log(2));
                    //two y cover the whole range of the array from left to right;
                    res = gcd(f[prior_left][y], f[mid - (1 << (y)) + 1][y]);
                }
                //the gcd of the array will be decreasing as the index increase;
                //so binary search;
                if (res <= result)//the range should extend to the front
                    right = mid;
                else left = mid;
            }
            //from the right and including the right;
            //this is the smallest range of the result;
            //check the left is ok or not;
            if (left == prior_left) {
                if (array[left] == result)count = left;
                else count = right;
            } else {
                int z = (int) (log(left - prior_left + 1) / log(2));
                //two y cover the whole range of the array from left to right;
                if (gcd(f[prior_left][z], f[left - (1 << (z)) + 1][z]) == result)count = left;
                else count = right;
            }
//            cout << "left range: " << right << endl;
            right = n - 1;
            while (left < right - 1) {
                int mid = (left + right) / 2;
                int res;
                if (prior_left == mid)res = array[prior_left];
                else {
                    int y = (int) (log(mid - prior_left + 1) / log(2));
                    //two y cover the whole range of the array from left to right;
                    res = gcd(f[prior_left][y], f[mid - (1 << (y)) + 1][y]);
                }
                //the gcd of the array will be decreasing as the index increase;
                //so binary search;
                if (res < result)//the range should extend to the front
                    right = mid;
                else left = mid;
                //now right is the biggest range of the result;
            }
            int z = (int) (log(right - prior_left + 1) / log(2));
            //two y cover the whole range of the array from left to right;
            if (gcd(f[prior_left][z], f[right - (1 << (z)) + 1][z]) == result)left = right;
//            cout << "right range: " << left << endl;
            printf("%d%c", left - count, '\n');
        } else if (left == n - 1) printf("%d%c", 0, '\n');
        else {
            if (right == n - 1)printf("%d%c", 0, '\n');
            else printf("%d%c", (int) (gcd(array[left], array[n - 1]) == result), '\n');
        }
    }
    return 0;
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

