//
// Created by lu'ren'jia'd's on 2022/4/3.
//

#include <iostream>
#include <cstring>

using namespace std;
const int maxp = 2e3 + 5;
const int maxl = 2e5 + 5;
int ch[maxp][27]{0};//构建一棵trie树
int total = 1;
bool mark[maxp]{false};//记录这个节点是不是某个字符串的末尾；

void insert(char *c) {//构建一棵trie树
    int u = 0;
    int l = strlen(c);
    for (int i = 0; i < l; ++i) {
        int v = c[i] - 'A';
        if (ch[u][v] == 0) {
            ch[u][v] = total;
            mark[total] = false;
            ++total;
        }
        u = ch[u][v];
    }
    mark[u] = true;
}

bool find(char *c) {
    int u = 0;
    int l = strlen(c);
    for (int i = 0; i < l; ++i) {
        int v = c[i] - 'A';
        if (ch[u][v])u = ch[u][v];
        else return false;
    }
    return mark[u];
}

char s[maxl], tmp[77];
int s_len;
bool visited[maxl]{false};//记录在某个规模是否有解
int ans = -1;

void search(int k) {//找第k个规模以后的各种情况是否有解
    //现在我们认为ans规模是已经有解的
    if (k != -1 && visited[k])return;
    if (k != -1)visited[k] = true;
    //用i代表字符串的长度
    for (int i = 1; i <= s_len - k - 1 && i < 11; ++i) {
        char c[11]{'\0'};
        strncpy(c, s + k + 1, i);
        bool f = find(c);
        if (f) {
            if (k + i > ans) {
                ans = k + i;
            }
            search(k + i);
        }
    }

}

int main() {
    char c[12];
    while (1) {
        cin >> c;
        if (strcmp(".", c) == 0)break;
        else insert(c);
    }
    s[0] = '\0';
    while (cin >> tmp) {
        strcat(s, tmp);
    }
    s_len = strlen(s);
//    cout << s << endl;
//    cout << s_len << endl;
    search(-1);
    cout << ans + 1 << endl;
    return 0;
}