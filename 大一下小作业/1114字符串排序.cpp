//
// Created by lu'ren'jia'd's on 2022/4/13.
//
#include <iostream>
#include <cstring>

using namespace std;
const int maxn = 1e5 + 5;
int n, m;
enum state {
    up, down, no_tag
};
struct node {
    int number[26]{0};
    state tag = no_tag;//如果说tag==true子树的字母分布需要修改
};
node tree[maxn << 4];
char str[maxn];

void push_up(int p);

void build(int p, int l, int r);

void push_down(int p, int l, int r);

void query(int part[26], int ql, int qr, int p, int l, int r);

void update(int part[26], int nl, int nr, int p, int l, int r, state s);

void dfs_print(int p, int l, int r);

int main() {
    scanf("%d %d", &n, &m);
    scanf("%s", str);
    build(1, 0, n - 1);
    for (int i = 0; i < m; ++i) {
        int l, r, op;
        scanf("%d %d %d", &l, &r, &op);
        //注意是0-base
        if (op == 1) {
            //不能两小段分别去排，如果要排的话，也要想把两小段的字母数量更新掉
            //更新两小段的字母不能放在push——down，只要更新过这一段，就得把字母更新好
            int part[26]{0};
            query(part, l - 1, r - 1, 1, 0, n - 1);//先把字母重新分配
            update(part, l - 1, r - 1, 1, 0, n - 1, up);//再打标记说更新的事
        } else if (op == 0) {
            int part[26]{0};
            query(part, l - 1, r - 1, 1, 0, n - 1);
            update(part, l - 1, r - 1, 1, 0, n - 1, down);
        }
    }
    dfs_print(1, 0, n - 1);
    return 0;
}

void push_up(int p) {
    for (int i = 0; i < 26; ++i)
        tree[p].number[i] = tree[p << 1].number[i] + tree[p << 1 | 1].number[i];
}

void build(int p, int l, int r) {
    if (l == r) {
        tree[p].number[str[l] - 'a'] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}

void push_down(int p, int l, int r) {
    if (tree[p].tag == no_tag)return;
    //修改p的两个儿子的字母分布，并且给他俩打上tag
    //左边一共就tot个字母，从父节点中拿出tot个字母给他
    if (tree[p].tag == up) {
        int mid = (l + r) >> 1, tot = mid - l + 1, i = 0, j = 0;
        while (j < 26 && i + tree[p].number[j] <= tot) {
            i += tree[p].number[j];
            tree[p << 1].number[j] = tree[p].number[j];
            tree[p << 1 | 1].number[j] = 0;
            ++j;
        }
        if (j < 26) {
            //说明tree[p].number[j]没加上，全加上超了
            tree[p << 1].number[j] = tot - i;
            tree[p << 1 | 1].number[j] = tree[p].number[j] - tot + i;
        }
        ++j;
        for (; j < 26; ++j) {
            tree[p << 1].number[j] = 0;
            tree[p << 1 | 1].number[j] = tree[p].number[j];
        }
        tree[p << 1].tag = tree[p << 1 | 1].tag = up;
        tree[p].tag = no_tag;
    } else if (tree[p].tag == down) {
        int mid = (l + r) >> 1, tot = mid - l + 1, i = 0, j = 25;
        while (j >= 0 && i + tree[p].number[j] <= tot) {
            i += tree[p].number[j];
            tree[p << 1].number[j] = tree[p].number[j];
            tree[p << 1 | 1].number[j] = 0;
            --j;
        }
        if (j >= 0) {
            //说明tree[p].number[j]没加上，全加上超了
            tree[p << 1].number[j] = tot - i;
            tree[p << 1 | 1].number[j] = tree[p].number[j] - tot + i;
        }
        --j;
        for (; j >= 0; --j) {
            tree[p << 1].number[j] = 0;
            tree[p << 1 | 1].number[j] = tree[p].number[j];
        }
        tree[p << 1].tag = tree[p << 1 | 1].tag = down;
        tree[p].tag = no_tag;
    }
}

void query(int part[26], int ql, int qr, int p, int l, int r) {
    if (ql <= l && qr >= r) {
        for (int i = 0; i < 26; ++i)part[i] += tree[p].number[i];
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid)query(part, ql, qr, p << 1, l, mid);
    if (qr >= mid + 1)query(part, ql, qr, p << 1 | 1, mid + 1, r);
}

void update(int part[26], int nl, int nr, int p, int l, int r, state s) {
    if (nl <= l && nr >= r) {
        tree[p].tag = s;//此序列中的字母已经重新排过了，只不过它下面的节点还不知道
        if (s == up) {
            int j = 0, i = 0;
            memset(tree[p].number, 0, sizeof(tree[p].number));
            while (j < r - l + 1 && i < 26) {
                if (part[i] == 0)++i;
                else {
                    if (j + part[i] < r - l + 1) {
                        tree[p].number[i] += part[i];
                        j += part[i];
                        part[i] = 0;
                    } else break;
                }
            }
            //刚才的i可没加
            if (i < 26) {
                tree[p].number[i] += r - l + 1 - j;
                part[i] -= r - l + 1 - j;
            }
        } else if (s == down) {
            int j = 0, i = 25;
            memset(tree[p].number, 0, sizeof(tree[p].number));
            while (j < r - l + 1 && i >= 0) {
                if (part[i] == 0)--i;
                else {
                    if (j + part[i] < r - l + 1) {
                        tree[p].number[i] += part[i];
                        j += part[i];
                        part[i] = 0;
                    } else break;
                }
            }
            if (i >= 0) {
                tree[p].number[i] += r - l + 1 - j;
                part[i] -= r - l + 1 - j;
            }
        }
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (nl <= mid)update(part, nl, nr, p << 1, l, mid, s);
    if (nr >= mid + 1)update(part, nl, nr, p << 1 | 1, mid + 1, r, s);
    push_up(p);
}

void dfs_print(int p, int l, int r) {
    if (l == r) {
        int letter = 0;
        for (; letter < 26; ++letter) {
            if (tree[p].number[letter] != 0) break;
        }
        printf("%c", 'a' + letter);
        return;
    }
    if (tree[p].tag == up) {
        for (int i = 0; i < 26;) {
            if (tree[p].number[i] == 0) {
                ++i;
                continue;
            }
            printf("%c", 'a' + i);
            tree[p].number[i]--;
        }
        return;
    }
    if (tree[p].tag == down) {
        for (int i = 25; i >= 0;) {
            if (tree[p].number[i] == 0) {
                --i;
                continue;
            }
            printf("%c", 'a' + i);
            tree[p].number[i]--;
        }
        return;
    }
    int mid = (l + r) >> 1;
    dfs_print(p << 1, l, mid);
    dfs_print(p << 1 | 1, mid + 1, r);
}

