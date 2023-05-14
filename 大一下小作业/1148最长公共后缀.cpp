//
// Created by lu'ren'jia'd's on 2022/3/31.
//
#include<iostream>
#include <cstring>

using namespace std;

int total = 1;//总结点数
int trie_tree[1000005][27]{0};
int EOS[50005];//end of the string,结束标记
int f[1000005][21]{0};
int depth[1000005]{0};

void add_word(char *c, int index) {
    int length = strlen(c);
    int u = 0;//现在正在处理的节点的编号
    for (int i = length - 1; i >= 0; --i) {
        int letter = c[i] - 'a';
        if (trie_tree[u][letter])u = trie_tree[u][letter];//此节点已经被用过了
        else {
            //此节点还没出现过，因此需要建立一下
            trie_tree[u][letter] = total;
            //在更新u之前应当更新祖先节点，方便lca
            depth[total] = depth[u] + 1;
            f[total][0] = u;
            for (int j = 1; j <= 20; ++j) {
                f[total][j] = f[f[total][j - 1]][j - 1];
            }
            u = trie_tree[u][letter];
            ++total;
        }
    }
    EOS[index] = u;//第 index个字符串的结束节点就是u；
}

int LCA(int x, int y) {
    if (depth[x] < depth[y])swap(x, y);
    for (int i = 20; i >= 0; --i) {
        if (depth[f[x][i]] >= depth[y])x = f[x][i];
    }
    if (x == y)return y;
    for (int i = 20; i >= 0; --i) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

int n, m;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        char c[10002];
        scanf("%s", &c);
        add_word(c, i + 1);
    }
    for (int i = 0; i < m; ++i) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            char c[10002];
            scanf("%s", &c);
            add_word(c, ++n);
        } else if (op == 2) {
            int q;
            scanf("%d", &q);
            int a, b, c;
            scanf("%d %d", &a, &b);
            int lca = LCA(EOS[a], EOS[b]);
            for (int j = 2; j < q; ++j) {
                scanf("%d", &c);
                lca = LCA(lca,EOS[c]);
            }
            printf("%d%c", depth[lca], '\n');
        }

    }
    return 0;
}
