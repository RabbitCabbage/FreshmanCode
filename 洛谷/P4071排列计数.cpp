//
// Created by lu'ren'jia'd's on 2022/6/29.
//

#include <iostream>

using namespace std;
const long long mod = 1e9 + 7;
/*错排：
 * 递推式：总共有n个元素需要错排，
 * 那么如果考虑其中的1和i两个元素，如果说i放到1的位置1也放到i的位置，
 * 剩下n-2个元素去错排，
 * 如果说1没有放到i的位置,剩下n-1个元素去错排，
 * D[n]=(D[n-1]+D[n-2])*(n-1)
 */

/*费马小定理：
 * p是质数，a是任意自然数，则pow(a,p) = a mod p;
 * pow(a,p-1) = 1 mod p;
 */

/* 逆元的运算：
 * 我们要mod一个数，加减乘的过程中都可以mod，但是除法不能mod
 * 所以我们要用到逆元，要求Cnk的话要用 除法 即 n!/(n-m)!*m!
 * 那我们就要找到k!的逆元，
 * a*pow(a,p-2) = 1 mod p;
 * a的逆元就是pow(a,p-2)
 * 逆元存在的条件是a小于p并且p是质数，这样a就存在模p意义下的逆元
 *
 */
/*Lucas 定理*/
const int maxn = 1e6 + 2;
long long D[maxn];
long long Inv[maxn];
long long K[maxn];
int n, m, t;

long long Pow(long long a, long long p) {
    long long res = 1;
//    for (int i = 0; i < p; ++i) {
//        res *= a;
//        res %= mod;
//    }
    while (p) {
        //如果p是一个奇数，就用res去乘，然后把p/2
        if (p & 1)res = a * res % mod;
        //如果p是一个偶数，就用a平方，把p/2
        a = a * a % mod;
        p >>= 1;
    }
    return res;
}

int main() {
    D[1] = 0, D[2] = 1;
    for (int i = 3; i < maxn; ++i) {
        D[i] = (i - 1) * ((D[i - 1] + D[i - 2])) % mod;
    }
    K[1] = 1, K[0] = 1;
    for (int i = 2; i < maxn; ++i) {
        K[i] = (K[i - 1] * i) % mod;
    }
    Inv[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        Inv[i] = Pow(K[i], mod - 2);//计算逆元，K[i]的逆元
    }
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        scanf("%d %d", &n, &m);
        if (n - m == 1) {
            printf("%d\n", 0);
            continue;
        }
        if (n - m == 0) {
            printf("%d\n", 1);
            continue;
        }
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (m == 0) {
            printf("%lld\n", D[n]);
            continue;
        }
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        long long res = 1;
        res = (res * K[n]) % mod;
        res = (res * Inv[m]) % mod;
        res = (res * Inv[n - m]) % mod;
        res = (res * D[n - m]) % mod;
        printf("%lld\n", res);
    }
    return 0;
}