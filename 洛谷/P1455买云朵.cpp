//
// Created by lu'ren'jia'd's on 2022/6/29.
//

#include <iostream>
#include <cstring>

using namespace std;
const int maxn = 1e4 + 5;
const int maxm = 2e8 + 5;
int n, m, w;
int father[maxn];
int price[maxn];
int value[maxn];
int cloud_price[maxn];
int cloud_value[maxn];
bool flag[maxn];
//long long dp[maxn][maxm];//表示决定到第i个物品的时候,用了j的钱能得到到的最大值
long long dp[maxm];//表示决定到第i个物品的时候,用了j的钱能得到到的最大值
//这里只用一个数组进行回滚
void init() {
    for (int i = 0; i < maxn; ++i)father[i] = i;
}

int find(int x) {
    if (father[x] == x)return x;
    else return father[x] = find(father[x]);
}

void unit(int x, int y) {
    x = find(x), y = find(y);
    if (x == y)return;
    else {
        father[y] = x;
        price[x] += price[y];
        value[x] += value[y];
    }

}

int main() {
    memset(flag, false, sizeof(flag));
    init();
    scanf("%d %d %d", &n, &m, &w);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &price[i]);
        scanf("%d", &value[i]);
        //std::cout << i << std::endl;
    }
    for (int i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        unit(x, y);
        //std::cout << i << std::endl;
    }
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        int fa = find(i);
        if (!flag[fa]) {
            cloud_price[count] = price[fa];
            cloud_value[count] = value[fa];
            flag[fa] = true;
            count++;
            //std::cout << count << std::endl;
        }
    }
    //std::cout << count << std::endl;
    //现在总共是有count个捆绑销售的云朵，再来一次背包dp
    memset(dp, 0, sizeof(0));
    //std::cout << cloud_price[0] << std::endl;
    dp[cloud_price[0]] = cloud_value[0];
    //std::cout << "here" << std::endl;
    for (int i = 1; i < count; ++i) {
        //这里为什么是倒序的dp
        //因为如果不用二维数组，使用同一个数组，后面的用前面的更新
        //如果这里正序的话，前面的改了后面无法继续更新
        //std::cout << i << std::endl;
        for (int j = w; j >= cloud_price[i]; j--)
//            dp[i][j] = max(dp[i - 1][j - cloud_price[i]] + cloud_value[i], dp[i - 1][j]);
            dp[j] = max(dp[j - cloud_price[i]] + cloud_value[i], dp[j]);
    }
    printf("%lld\n", dp[w]);
    return 0;
}