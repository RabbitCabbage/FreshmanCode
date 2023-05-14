//
// Created by lu'ren'jia'd's on 2021/11/3.
//

#include<iostream>
#include<sstream>

using namespace std;
int k, n;

int main() {
    cin >> n >> k;
    bool occupied[n];
    int vaccant_code[n], j = 0;
    stringstream ss;
    getchar();
    for (int i = 0; i < n; ++i) {
        char sequence = getchar();
        ss.clear();
        ss << sequence;
        ss >> occupied[i];
        if (!occupied[i]) {
            vaccant_code[j] = i;
            ++j;
        }
    }
    int begin = 0, john = 0, distance_min = n;
    for (; begin <= j - k - 1; ++begin) {
        john = begin;
        while (john >= begin && john <= begin + k) {
            int left = vaccant_code[john] - vaccant_code[begin];
            int right = vaccant_code[begin + k] - vaccant_code[john];
            if (distance_min > max(left, right))distance_min = max(left, right);
            ++john;
        }
    }
    cout << distance_min << endl;
    return 0;
}