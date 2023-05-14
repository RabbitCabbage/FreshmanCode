//cstdio, iostream, cmath, cstring
#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char str[1000009];
    cin >> str;
    int length = strlen(str);
    char sub[1000009], tmp[1000009];
    int i;
    for (i = 1; i < length; ++i) {
        strncpy(sub, str, i);//子串的长度此时为i，我们要看i的长度是否可以
        int j = strlen(sub) - 1;
        for (int k = length - 1; j >= 0; --j, --k) {
            if (sub[j] != str[k])break;//说明不一样，要增加子串长度
        }
        if (j == -1)break;//说明比对到最后也是一样的
    }
    if (i == length)return 0;
    //否则的话就是得到了第一个匹配成功的长度
    cout << i << endl;
    strcpy(tmp, sub);//上一次的子串
    for (int j = i; j < length; ++j) {//即将拼进去的就是str[i]
        int last_length = strlen(sub);
        tmp[j] = str[j];//增加一个字符
        int k;
        for (k = 0; k < last_length; ++k) {
            if (tmp[strlen(tmp) - 1 - k] != sub[last_length - 1 - k])break;
        }
        if (k == last_length) {//说明后面的几个字符时可以比对上的，再比对前几个
            int tmp_length = strlen(tmp);
            int q = 0;
            for (int p = length - tmp_length; q < tmp_length - last_length; ++q, ++p) {
                if (tmp[q] != str[p])break;
            }
            if (q == tmp_length - last_length) {
                cout << tmp_length << endl;
//                cout<<tmp<<endl;
                strcpy(sub, tmp);
            }
        }
    }
    return 0;
}//
// Created by lu'ren'jia'd's on 2022/2/28.
//

#include <iostream>
#include <cstring>

using namespace std;
char t[1000009];
int next__[1000009];
int result[1000000];
int scale=0;
void GetNext() {
    memset(next__, -1, sizeof(next__));
    int j = 0, k = -1;
    next__[j] = k;
    ++j;
    while (t[j] != '\0') {
        if (k == -1 || t[j] == t[k]) {
            ++j;
            ++k;
            next__[j] = k;
//            cout << j << " " << next__[j] << endl;
        } else k = next__[k];
    }
    //下面再倒回去用递归找,已经知道了最大的长度是next__[n]
    int last = next__[strlen(t)];
    result[0]=strlen(t);
    result[1]= last;
    scale=2;
    while (1) {
        if (next__[last] > 0) {
            result[scale]=next__[last];
            scale++;
            last = next__[last];
        } else break;
    }

}

int main() {
    cin >> t;
    GetNext();
    for(int i=scale-1;i>=0;--i)cout<<result[i]<<endl;
    return 0;
}