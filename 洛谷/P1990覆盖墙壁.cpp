//依然勾递推，要想明白各种可能出现的情况，有大规模到小规模
//递推递归的本质思想是一样的，有小规模到大规模，但是递推省时间】】】】】】】】很重要！！！
//你这个第一个版本的递归调用和斐波那契数列是一个道理，运行时间是灾难性的！！！！
#include <iostream>

using namespace std;

int even(int length);

int odd(int length);

int main() {
    int n;
    cin >> n;
    cout << even(n) << endl;
    return 0;
}

int even(int length) {
    if (length == 3)return 5;
    else if (length == 2)return 2;
    else if (length == 1 || length == 0)return 1;
    int result = 0;
    result += 1 * even(length - 1);
    result %= 10000;
    result += 1 * even(length - 2);
    result %= 10000;
    result += 1 * odd(length - 1);
    result %= 10000;
    return result;//odd的长度是有空白的长度，也就是最后一个其实有了一半了
}

int odd(int length) {
    if (length == 1)return 0;
    else if (length == 2)return 2;
    int result = 0;
    result += 1 * odd(length - 1);
    result %= 10000;
    result += 2 * even(length - 2);
    result %= 10000;
    return result;
}
//标答的话没有用递归，而是用了循环为基础的的递推
//记even[n],odd[n]

//依然勾递推，要想明白各种可能出现的情况，有大规模到小规模
//递推比递归省时间，防TLE从化递推做起
#include <iostream>

using namespace std;
int n;
int mod = 10000;

int main() {
    cin >> n;
    int even[n + 1], odd_up[n + 1], odd_down[n + 1];//记录这么长的墙有几种拼法，其中odd是指空了一块的也进上去比如 L 就是2
    even[0] = 0;
    even[1] = 1;
    even[2] = 2;
    even[3] = 5;
    odd_up[0] = 0;
    odd_up[1] = 0;
    odd_up[2] = 1;
    odd_down[0] = 0;
    odd_down[1] = 0;
    odd_down[2] = 1;
    for (int i = 3; i < n + 1; ++i) {//起点想明白，别用到了未初始化的量
        even[i] = 1 * even[i - 1] % mod + 1 * even[i - 2] % mod + 1 * odd_up[i - 1] % mod + 1 * odd_down[i - 1] % mod;
//        even[i] = 1 * even[i - 1] % mod + &2& * even[i - 2] % mod + 1 * odd[i - 1] % mod;
//上一行的2是错的，因为竖着的两块也包含在了竖着一块+竖着一块里，相当于这一部分被算了两次，所以改成上上一行
        even[i] %= mod;
        odd_up[i] = (1 * even[i - 2] % mod + 1 * odd_down[i - 1] % mod) % mod;
        odd_down[i] = (1 * even[i - 2] % mod + 1 * odd_up[i - 1] % mod) % mod;
    }
    cout << even[n] << endl;
    return 0;
}
//标答的话没有用递归，而是用了循环为基础的的递推
//记even[n],odd[n]