//
// Created by lu'ren'jia'd's on 2022/3/20.
//

#include<iostream>

using namespace std;
int n, k;

int main() {
    cin >> n >> k;
    int array[n];
    for (int i = 0; i < n; ++i)cin >> array[i];
    int max_queue[n + 1], max_head = 1, max_tail = 0;
    int min_queue[n + 1], min_head = 1, min_tail = 0;
    int max_answer[n], min_answer[n];
    for (int i = 0; i < n; ++i) {
        //we need the max of the array so the queue should be decreasing;
        //we need the min of the window so the queue should be increasing;
        while (max_head <= max_tail && array[max_queue[max_tail]] < array[i])--max_tail;
        while (min_head <= min_tail && array[min_queue[min_tail]] > array[i])--min_tail;
        max_queue[++max_tail] = i;
        min_queue[++min_tail] = i;
//        while (max_tail - max_head + 1 > k)++max_head;
//        while (min_tail - min_head + 1 > k)++min_head;//make the length of the window <= k
        //watch out!!!!!!!!!! this judgement is WRONG!!!!!!!
        //you need to judge the length of the window and it is queue[tail]-queue[head]
        //in the queue there are indexes and tail and head are actually the occupied room in queue;
        while (min_queue[min_tail] - min_queue[min_head] + 1 > k)min_head++;
        while (max_queue[max_tail] - max_queue[max_head] + 1 > k)max_head++;
        if (i >= k - 1) {
            max_answer[i] = array[max_queue[max_head]];
            min_answer[i] = array[min_queue[min_head]];
        }
    }
    for (int i = k - 1; i < n; ++i)cout << min_answer[i] << " ";
    cout << endl;
    for (int i = k - 1; i < n; ++i)cout << max_answer[i] << " ";
    cout << endl;
    return 0;
}