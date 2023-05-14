//
// Created by lu'ren'jia'd's on 2021/11/12.
//

#include<iostream>

using namespace std;
int m, n;

long long binary_search(int left, int right, long long like, long long cake[]);

int main() {
    cin >> m >> n;
    long long cake[m];
    for (int i = 0; i < m; ++i) {
        cin >> cake[i];
    }
    long long like, min = 0;
    for (int k = 0; k < n; ++k) {
        cin >> like;
        if (like > cake[m - 1])min += abs(like - cake[m - 1]);
        else if (like < cake[0]) min += abs(like - cake[0]);
        else min += binary_search(0, m-1, like, cake);
    }
    cout << min << endl;
    return 0;
}

long long binary_search(int left, int right, long long like, long long cake[]) {
    long long min;
    while (left - right != -1) {
        int mid = (left + right) / 2;
        if (cake[mid] == like)return 0;
        else if (cake[mid] < like)left = mid;
        else right = mid;
    }
    min = abs(cake[left] - like) < abs(cake[right] - like) ? abs(cake[left] - like) : abs(cake[right] - like);
    return min;
}