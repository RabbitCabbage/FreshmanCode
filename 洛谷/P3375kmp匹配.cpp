//
// Created by lu'ren'jia'd's on 2022/3/4.
//
#include<iostream>
#include <cstring>

using namespace std;
char s1[1000009], s2[1000009];
int len2;

//而 KMPKMP 的精髓在于，对于每次失配之后，我都不会从头重新开始枚举
// ，而是根据我已经得知的数据，从某个特定的位置开始匹配；
int main() {
    cin >> s1 >> s2;
    len2 = strlen(s2) + 1;
    int next[len2];
    next[0] = {-1};
    int k = -1, i = 0;//从第一个字符开始比较，k表示的是回跳值
    //初始回跳值设置为-1，，之后回跳的每一个都是上一次比较相同的地方
    while (s2[i] != '\0') {
        //想向后移一位，于是就得看这位是否可以匹配
        if (k == -1)//说明是初始状态,或者说是上一次回跳回到了最初起点
        {
            ++i, ++k;//跳到下一位，准备开始比较
            next[i] = k;
//            cout<<"quq "<<k;
            continue;
        }
        if (s2[k] == s2[i]) {
            ++i, ++k;
            next[i] = k;
//            cout<<"quq "<<k;
        } else k = next[k];//会跳到前面可以出现匹配的地方，
        // 如果前面也没有配，就会跳回0的-1，说明是，再达到这一列都是0
    }
    //现在可以进行s1,s2的匹配，如果说s2的哪个字符匹配不上了，就让s2通过next数组回跳
    //就相当于这个长一点的匹配不上了，我就去找短一点的前面的匹配
    //直观上来看就是，将s2向右移动到了恰好前面的都匹配，后面未知，以继续进行
    int j = 0;
    k = 0;
    while (s1[j] != '\0') {
        if (s2[k] == s1[j])++j, ++k;
        else {
            if (k == 0)++j;//不能再往前回溯了
            else k = next[k];
        }
        if (s2[k] == '\0') {
            //说明找到了，就得把结果记上了，并且重新设置kj
            cout << j - strlen(s2) + 1 << endl;//1-base
            k = next[k];//既然后面的已经匹配了，为什么不用啊
        }
    }
    //next这里是求出到s2最后一位多一个，目的是便于满足题目要求
    for (int q = 1; q <= strlen(s2); ++q)cout << next[q] << ' ';
    cout << endl;
    return 0;
}
