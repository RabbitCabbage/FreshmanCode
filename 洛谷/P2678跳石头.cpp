//我们二分跳跃距离，然后把这个跳跃距离“认为”是最短的跳跃距离，然后去以这个距离为标准移石头。
// 使用一个judge判断这个解是不是可行解。
// 如果这个解是可行解，那么有可能会有比这更优的解，那么我们就去它的右边二分。
// 为什么去右边？答案是，这个区间是递增的 ，而我们求的是最短跳跃距离的最大值
// 再右边的值肯定比左边大，那么我们就有可能找到比这更优的解，直到找不到，那么最后找到的解就有理由认为是区间内最优解。
// 反过来，如果二分到的这个解是一个非法解，我们就不可能再去右边找了。因为性质，右边的解一定全都是非法解。
// 那么我们就应该去左边
////////////////////////////
//判断如果以这个距离为最短跳跃距离需要移走多少块石头，
//先不必考虑限制移走多少块，等全部拿完再把拿走的数量和限制进行比对，如果超出限制，那么这就是一个非法解，反之就是一个合法解，
#include <iostream>

using namespace std;
int n, m, l;

int main() {
    cin >> l >> n >> m;
    if (n == m) {
        cout << l << endl;
        return 0;
    }
    int distance[n + 2];
    for (int i = 1; i <= n; ++i)cin >> distance[i];
    distance[0] = 0, distance[n + 1] = l;
    int min = 1, max = l, mid;
    while (min + 1 < max) {
        mid = (min + max) / 2;
        int movable = 0;//可以移走的石头，只要他小于等于m就认为是合法的、
        //看需要移走多少块石头才能达到效果，使得最短距离大于mid
        int now_position = 0;
        while (now_position <= n) {
            int i;
            for (i = now_position + 1; i <= n + 1;) {
                if (distance[i] - distance[now_position] < mid)++i;
                else break;
            }
            //如果说i==n+1站在了终点的石头上，并且完成了mid的长度也是可以的,but i==n+2,就说明最后一块也要移走
            if (i == n + 2)movable = m + 1; //就不行了，连最后一块可以移走的也移走了
            movable += i - now_position - 1;
            now_position = i;
        }
        if (movable > m)max = mid;
        else min = mid;
    }
    cout << min << endl;
    return 0;
}