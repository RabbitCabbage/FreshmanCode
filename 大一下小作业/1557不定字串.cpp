#include <iostream>
#include<cstring>

using namespace std;
int T, C;
int n, m;
const int maxn = 1e6 + 5;
const int maxm = 1e6 + 5;
const int maxC = 1e6 + 5;
const int inf = -2139062144;
int s[maxn];
int s_appear[maxn];
int nex[maxn];
int t[maxm];
int t_appear[maxm];
int former_appear[maxC];//记下i前一次出现是在何处
//former_appear记录的是i这个数上次出现在former_appear[i]处
//s_appear t_appear不一样，他们记录的是s_appear[i]记录的是与s[i]像同的数字上次出现在哪里
int answer[maxm];
int count;

void read(int &x) {
    x = 0;
    int f = 1;
    char c = getchar();
    while (!isdigit(c))
        f = (c == '-' ? -1 : 1), c = getchar();
    while (isdigit(c))
        x = x * 10 + c - '0', c = getchar();
    x *= f;
}

void get_next() {
    int k = -1, i = 0;//k表示的是回跳位置，i就是个遍历下标
    nex[i] = k;
    int dis_k, dis_i;
    if (s_appear[i] == inf)dis_i = inf;//如果s[i]之前没出现过，记一个特殊值
    else dis_i = i - s_appear[i];
    if (s_appear[k + 1] == inf)dis_k = inf;
    else dis_k = k + 1 - s_appear[k + 1];
    for (i = 1; i < n; ++i) {
        while (k >= 0 && dis_k != dis_i) {
            k = nex[k];
            if (s_appear[i] == inf)dis_i = inf;//如果s[i]之前没出现过，记一个特殊值
            else dis_i = i - s_appear[i];
            if (s_appear[k + 1] == inf)dis_k = inf;
            else dis_k = k + 1 - s_appear[k + 1];
        }
        if (dis_k == dis_i)k++;
        nex[i] = k;
    }
}


int main() {
    read(T);
    read(C);
    for (int i = 0; i < T; ++i) {
        count = 0;
        read(m);
        read(n);
        memset(former_appear, 1e7, sizeof(former_appear));
        for (int j = 0; j < m; ++j) {
            read(t[j]);
            --t[j];
            t_appear[j] = former_appear[t[j]];
            former_appear[t[j]] = j;
        }
        memset(former_appear, 1e7, sizeof(former_appear));
        for (int j = 0; j < n; ++j) {
            read(s[j]);
            --s[j];
            //现在要处理在前面出现的地方，第一次出现记为inf
            s_appear[j] = former_appear[s[j]];//接过上一次出现的地方
            former_appear[s[j]] = j;//记下这一次出现的地方
        }
        //我们要制定一套新的比较规则，那就是出现的pattern完全一样的数字串就是可以匹配上的
        //这个pattern的定义应该这么说，就是与在之前出现的相隔距离相等
        //现在利用刚刚记下的在自己之前出现的下标，开始求s的next数组
        get_next();
        //现在进行匹配过程
        int j = 0, k = -1;//j指向的是主串，k指向的是模式串
        //在t串里面找s串
        //记着每次比较的主串的起点，超过起点前的就相当于没出现
        for (; j < m; ++j) {
            int dis_k, dis_j;
            if (s_appear[k + 1] == inf)dis_k = inf;
            else dis_k = k + 1 - s_appear[k + 1];
            if (t_appear[j] == inf)dis_j = inf;
            else {
                //如果不在比较范围内，就不能算出现过
                if (j - t_appear[j] > k + 1)dis_j = inf;
                else dis_j = j - t_appear[j];
            }
            while (k >= 0 && dis_j != dis_k) {
                k = nex[k];
                if (s_appear[k + 1] == inf)dis_k = inf;
                else dis_k = k + 1 - s_appear[k + 1];
                if (t_appear[j] == inf)dis_j = inf;
                else {
                    //如果不在比较范围内，就不能算出现过
                    if (j - t_appear[j] > k + 1)dis_j = inf;
                    else dis_j = j - t_appear[j];
                }
            }
            if (dis_j == dis_k)++k;
            if (k == n - 1) {
                answer[count++] = j - n + 2;
                k = nex[k];
            }
        }

        printf("%d\n", count);
        for (int q = 0; q < count; ++q)printf("%d ", answer[q]);
        printf("%c", '\n');
    }

    return 0;
}