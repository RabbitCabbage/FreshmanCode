//
// Created by lu'ren'jia'd's on 2022/2/24.
//

#include <iostream>

using namespace std;
int n, l, k;

int main() {
    cin >> l >> n >> k;
    int distance[n];
    for (int i = 0; i < n; ++i) {
        cin >> distance[i];
    }
    int shortest = l / (n + k) - 1;
    int low = shortest, high = l, mid;
    while (low + 1 < high) {
        mid = (low + high + 1) / 2;
        //现在假设的是隔mid，检查两地之间的距离，如果大于mid就铺设一个，铺设distance/mid个
        int count = 0;
        for (int i = 0; i < n - 1; ++i) {
            int dis = distance[i + 1] - distance[i];
            count += dis / mid;
            if (dis % mid == 0)--count;
            // 如果两路标之间的的距离正好是mid的倍数，要减去正好和最后一个路标重合的路标 （小学奥数）
        }
        if (count > k)//说明吧这个距离太小了，得大一点
            low = mid;
        else high = mid;
    }
    cout << high << endl;
    return 0;
}