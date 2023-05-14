//
// Created by lu'ren'jia'd's on 2022/4/3.
//

#include <iostream>
#include <cstring>

const int maxn = 1e5 + 5;
const int maxs = 1e6 + 5;//相当于是trei树的总结点数
const int maxt = 1e6 + 5;
using namespace std;
int n;

char letter[maxt];//书信文本
char namelist[maxn][10000];//暂时认为每个名字长度是10000
int tree[maxs][27]{0};//所有名字建立一颗树
int fail[maxs]{-1};//失配数组，指向的是适配后要去的节点
bool matched[maxs]{false};
int total = 1;
bool mark[maxs];//每一个节点都要有

void insert(char name[10000])//把一个名字放入树
{
    int u = 0;
    int len = strlen(name);
    for (int i = 0; i < len; ++i) {
        int v = name[i] - 'a';
        if (tree[u][v] == 0) {
            tree[u][v] = total;
//            mark[total] = false;
            ++total;
        }
        u = tree[u][v];
    }
//    mark[u] = true;
    matched[u] = true;
    //这里不再用普通的mark数组
    //因为mark数组只能标记到这一位的时候是不是这个字符串的末尾
    //但是我们为了找到在长字符串中出现过的短字符串，必须要把之前出现过的也记下来
}

void get_next_for_t(int t) {
    for (int i = 0; i < 26; ++i) {
        if (tree[t][i]) {
            int previous = fail[t];
            //如果t没匹配上，就要回到fail【t】，从这里再往i的分叉走，看这个分叉能不能走
            while (previous != -1 && tree[previous][i] == 0)previous = fail[previous];
            if (previous == -1)fail[tree[t][i]] = 0;//回溯到根部
            else fail[tree[t][i]] = tree[previous][i];
            matched[tree[t][i]] = (matched[tree[t][i]] || matched[tree[previous][i]]);
            //标记较长的字符串里面是否已经出现过较短的字符串
            get_next_for_t(tree[t][i]);
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> namelist[i];
        insert(namelist[i]);
    }
    get_next_for_t(0);
    cin >> letter;
    int i = 0, j = 0;//从根节点开始进行回溯
    bool flag = false;
    while (1) {
        if (tree[j][letter[i] - 'a']) {//如果说可以匹配上，就都往后走一个
            j = tree[j][letter[i] - 'a'];
            ++i;
        } else {//否则的话就没配上，就得往回走
            j = fail[j];
            if (j == -1) {
                //如果说这些都没配上，就得重新来一遍
                ++i, j = 0;
                if (letter[i] == '\0')break;
            }
        }
        if (matched[j]) {//如果配完这个到了,或者说在这个长字符串里已经有较短的字符串了，就说明可以了；
            flag = true;
            break;
        }
        if (letter[i] == '\0')break;
    }
    if (flag)cout << "valar morghulis" << endl;
    else cout << "valar dohaeris" << endl;
    return 0;
}