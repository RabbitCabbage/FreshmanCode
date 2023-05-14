//
// Created by lu'ren'jia'd's on 2022/3/20.
//

#include <iostream>

using namespace std;
int n;

int main() {
    cin >> n;
    long long l[n], r[n];
    for (int i = 0; i < n; ++i)cin >> l[i] >> r[i];
    int queue[n + 1];
    int head = 1, tail = 0, max_length = 0, begin_index = 0;
    for (int i = 0; i < n; ++i) {
//        cout << "i: " << i << " ri: " << r[i] << endl;
        while (head <= tail && l[queue[tail]] < l[i]) {
            //when tail-- the element is actually small enough and can be the begging_index;
            tail--;
        }
        queue[++tail] = i;
        while (head <= tail && l[queue[head]] > r[i]) {
            //when the head need ++ this location is actually can't be begin_index;
            begin_index = queue[head] + 1;
            ++head;
        }
//        cout << "begin_index: " << begin_index << endl;
//        for (int j = head; j <= tail; ++j)cout << "index: " << queue[j] << " l: " << l[queue[j]] << endl;
        if (max_length < i - begin_index + 1) {
            max_length = i - begin_index + 1;
        }
//        cout << "the max: " << max_length << endl;
//        cout << endl;
    }
    cout << max_length << endl;
    return 0;
}