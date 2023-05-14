#include<iostream>

using namespace std;
const int maxn = 5e5 + 5;
int n, m;

enum tag_state {
    //不能只用布尔来表示tag，因为如果用布尔值表示tag，不是全占满就会被清空，其实不是，有可能是不变的
    no_tag, occupied, vacant
};
struct node {
    int l, r;//分别代表从左边可以用多少，从右边可以用多少
    int max;//是指总共剩下多少连续的空间可以用
    tag_state lazytag = no_tag;//是说这一段有没有被占满,如果是打了tag即是说这一段都被占满了，都是我还没有往下更新
};
node tree[maxn << 2];

//每一个结点的值相当于是这个节点的lazytag，表示这一段是不是全部被占着
//如果说标记被打上true，说明这一段全部被占用了
void push_up(int p, int l, int r) {
    int mid = (l + r) >> 1;
    tree[p].l = tree[p << 1].l;
    if (tree[p].l == mid - l + 1)tree[p].l += tree[p << 1 | 1].l;
    tree[p].r = tree[p << 1 | 1].r;//父节点的左右最多走多少取决于子节点,但是要额外考虑子节点不够长的情况
    if (tree[p].r == r - mid)tree[p].r += tree[p << 1].r;
    tree[p].max = tree[p << 1].r + tree[p << 1 | 1].l;//父节点中间的最大值取决于两段子节点的最大值或者是他自己中间拼成的最大值
    if (tree[p << 1].max > tree[p].max)tree[p].max = tree[p << 1].max;
    if (tree[p << 1 | 1].max > tree[p].max)tree[p].max = tree[p << 1 | 1].max;
}

void build(int p, int l, int r) {
    if (l == r) {
        tree[p].l = tree[p].r = tree[p].max = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p, l, r);
}

void push_down(int p, int l, int r) {
    if (tree[p].lazytag == no_tag)return;
    else if (tree[p].lazytag == occupied) {
        //说明这一段已经全部被占了
        tree[p << 1].l = tree[p << 1].r = tree[p << 1].max = 0;
        tree[p << 1 | 1].l = tree[p << 1 | 1].r = tree[p << 1 | 1].max = 0;
    } else if (tree[p].lazytag == vacant) {
        //说明都没占,因为是从上往下的肯定是全部的都没被占
        int mid = (l + r) >> 1;
        tree[p << 1].l = tree[p << 1].r = tree[p << 1].max = mid - l + 1;
        tree[p << 1 | 1].l = tree[p << 1 | 1].r = tree[p << 1 | 1].max = r - mid;
    }
    tree[p << 1].lazytag = tree[p << 1 | 1].lazytag = tree[p].lazytag;
    tree[p].lazytag = no_tag;
}

void update(int cl, int cr, int p, int l, int r, tag_state tag) {
    if (cl <= l && cr >= r) {
        tree[p].lazytag = tag;
        //不能只用布尔来表示tag，因为如果用布尔值表示tag，不是全占满就会被清空，其实不是，有可能是不变的
        if (tree[p].lazytag == occupied) {
            //说明这一段已经全部被占了
            tree[p].l = tree[p].r = tree[p].max = 0;
        } else if (tree[p].lazytag == vacant) {
            //说明都没占,因为是从上往下的肯定是全部的都没被占
            tree[p].l = tree[p].r = tree[p].max = r - l + 1;
        }
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, l, r);
    if (cl <= mid)update(cl, cr, p << 1, l, mid, tag);
    if (cr >= mid + 1)update(cl, cr, p << 1 | 1, mid + 1, r, tag);
    push_up(p, l, r);
}

//询问这内部是否还有一段连续的长度为d的区间
bool query(int d, int p) {
    if (tree[p].max < d)return false;
    return true;
}

int start(int d, int p, int l, int r) {
    if (l == r)return l;
    //先从左边找
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    int s;
    if (tree[p << 1].max >= d) {
        s = start(d, p << 1, l, mid);
        update(s, s + d - 1, 1, 1, n, occupied);
        return s;
    }
    //否则的话就是不够，，有可能可以横跨右侧来找
    if (tree[p << 1].r + tree[p << 1 | 1].l >= d) {
        int left_part = tree[p << 1].r;
        s = mid - left_part + 1;
        update(s, s + d - 1, 1, 1, n, occupied);
        return s;
    }
    //就是全部在右边
    s = start(d, p << 1 | 1, mid + 1, r);
    update(s, s + d - 1, 1, 1, n, occupied);
    return s;
}

int main() {
    scanf("%d %d", &n, &m);
    build(1, 1, n);
    for (int i = 0; i < m; ++i) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int d;
            scanf("%d", &d);
            if (query(d, 1)) {
                printf("%d%c", start(d, 1, 1, n), '\n');
            } else printf("%d%c", 0, '\n');
        } else {
            int l, d;
            scanf("%d %d", &l, &d);
            update(l, l + d - 1, 1, 1, n, vacant);
        }
    }
    return 0;
}