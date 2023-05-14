//
// Created by lu'ren'jia'd's on 2021/11/3.
//

#include <iostream>

using namespace std;
int m, n;
int binarysearch(int left, int right, int array[], int query);
int main() {
    cin >> n >> m;
    int array[n];
    for (int i = 0; i < n; ++i)cin >> array[i];
    for (int j = 0; j < m; ++j) {
        int query;
        cin >> query;
        if (array[n - 1] < query)cout << -1<<endl;
        else {
            int ans= binarysearch(0,n-1,array,query);
            cout<<array[ans]<<endl;
        }
    }
    return 0;
}

int binarysearch(int left, int right, int array[], int query) {
    int ans;
    if (left == right) {
        if (array[left] >= query)ans = left;
        else ans = left + 1;
    } else {
        int mid = (left + right) / 2;
        if (array[mid] == query)ans = mid;
        else if (array[mid] > query)ans = binarysearch(left, mid, array, query);
        else if (array[mid] < query)ans = binarysearch(mid + 1, right, array, query);
    }
    return ans;
}