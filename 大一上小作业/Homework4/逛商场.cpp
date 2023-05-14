//
// Created by lu'ren'jia'd's on 2021/11/3.
//

#include <iostream>
#include <algorithm>

using namespace std;
int m, n;

int binarysearch(int left, int right, int query, int good_sum[]);

int main() {
    cin >> n >> m;
    int good[n], good_sum[n], query;
    for (int j = 0; j < n; ++j) {
        cin >> good[j];
        if (j == 0) good_sum[j] = good[j];
        else good_sum[j] = good_sum[j - 1] + good[j];
    }
    for (int i = 0; i < m; ++i) {
        cin >> query;
        //二分法找到连续的区间
        if (query <= good_sum[0])cout << 1 << " " << query << endl;
        else {
            int answer = binarysearch(0, n - 1, query, good_sum);
            cout << answer + 1 << " " << query - good_sum[answer - 1] << endl;
        }
    }

    return 0;
}

int binarysearch(int left, int right, int query, int good_sum[]) {
    int ans;
    if (right - left > 1) {
        int mid = (left + right) / 2;
        if (good_sum[mid] > query)ans = binarysearch(left, mid, query, good_sum);
        else if (good_sum[mid] < query) ans = binarysearch(mid, right, query, good_sum);
        else if (good_sum[mid] == query) ans = mid;
    } else ans = right;//ans就是摊位编号，o-base
    return ans;
}
