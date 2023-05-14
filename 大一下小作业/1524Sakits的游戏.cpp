//此题主要思路和unique函数，数据离散化的思路来自尹良升同学的讲解
//线段树二分，以及权值线段树的实现思路来自thu张朋乐同学的讲解
//read函数是机考给的快读模板
//我写的快排没有随机化好像会T，先用着std::sort
//特别注明 鸣谢 qwqqq

#include <iostream>
#include <algorithm>

using namespace std;

//权值线段树
const int maxn = 4e5 + 5;//这是数据离散化
const int maxq = 1e5 + 5;
int n;
enum tag_state {
    killed, no_tag
    //只要tag的是部分被打，说明留下来的肯定是最小的那个，剩了一部分,所以每次除了检查tag，还要检查是不是留下了几个最小的
};

inline long long read() {                 // read in a int and return
    char ch = getchar();
    long long x = 0, f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

//void sort(long long a[], int l, int r) {
//    if (l >= r)return;
//    int start = l, end = r;
//    long long chosen = a[l];
//    while (start < end) {
//        while (a[end] >= chosen && start < end)--end;
//        while (a[start] <= chosen && start < end)++start;
//        if (start < end) {
//            long long tmp = a[start];
//            a[start] = a[end];
//            a[end] = tmp;
//        }
//    }
//    a[l] = a[start];
//    a[start] = chosen;
//    sort(a, l, start - 1);
//    sort(a, start + 1, r);
//}

int unique(long long a[], int l, int r) {
    int i = l, j = 1;
    long long tmp = a[l];
    a[j] = a[i];
    while (i <= r) {
        while (a[i] == tmp)++i;
        if (i <= r) {
            a[++j] = a[i];
            tmp = a[i];
        }
    }
    return j;
}

struct node {
    long long sum0;//它的值代表是此区间内原本boss的和，便于消除tag
    long long sum;//表示的被删除之后的所有boss的和
    long long max_w;
    long long min_w;//区间里面出现的boss的最大和最小，用于找首个比自己更大的boss
    int first_num;//为了解决打了一半的,要记一下这个区间的最小值剩了了几个
    int total;//是这个区间内的boss总数目
    tag_state tag = no_tag;

};
struct operation {
    int op;
    long long w, k;
};
node tree[maxn << 2];
long long boss[maxn];
int number[maxn]{0};
operation query[maxq];

void push_up(int p) {
    tree[p].sum0 = tree[p << 1].sum0 + tree[p << 1 | 1].sum0;
    tree[p].sum = tree[p << 1].sum + tree[p << 1 | 1].sum;
    tree[p].first_num = tree[p << 1].first_num;
    if (tree[p << 1 | 1].max_w != -1)tree[p].max_w = tree[p << 1 | 1].max_w;
    else tree[p].max_w = tree[p << 1].max_w;
    if (tree[p << 1].min_w != -1)tree[p].min_w = tree[p << 1].min_w;
    else tree[p].min_w = tree[p << 1 | 1].min_w;
    tree[p].total = tree[p << 1].total + tree[p << 1 | 1].total;
}

void build(int p, int l, int r) {
    if (l == r) {
        tree[p].sum0 = boss[l] * number[l];//记录这个点的boss值的和
        tree[p].sum = boss[l] * number[l];
        tree[p].first_num = number[l];
        tree[p].total = number[l];
        //我们要把这个东西维护成存在的最大和最小，
        if (tree[p].total > 0)tree[p].max_w = tree[p].min_w = boss[l];
        else tree[p].max_w = tree[p].min_w = -1;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}

//在线段树上找到首个比自己大 (或者相等!!!!!!!!!!的) 的，作为下一次要达到的目标
//他返回的是，那个节点在数组中的下标索引值
int find_goal(long long w, int p, int l, int r) {
    if (l == r) {
        if (boss[l] >= w && tree[p].total > 0)return l;
        else return -1;
    }
    int mid = (l + r) >> 1;
    if (tree[p << 1].max_w != -1 && tree[p << 1].max_w >= w)return find_goal(w, p << 1, l, mid);
    else return find_goal(w, p << 1 | 1, mid + 1, r);
}

//找到现在我可以打的boss的开始，也即是find_prey函数想要的右端点
int find_start(long long w, int p, int l, int r) {
    if (l == r) {
        if (boss[l] < w && tree[p].total > 0)return l;
        else return -1;
    }
    int mid = (l + r) >> 1;
    if (tree[p << 1 | 1].min_w != -1 && tree[p << 1 | 1].min_w < w)return find_start(w, p << 1 | 1, mid + 1, r);
    else return find_start(w, p << 1, l, mid);
}

long long query_sum(int ql, int qr, int p, int l, int r) {
    long long res = 0;
    if (tree[p].tag == killed) {//打了不下放的标签，因此走到标签就不应该再往下走了
        if (ql <= l)return tree[p].first_num * boss[l];
        else return 0;
    }
    if (ql <= l && qr >= r) {
        return tree[p].sum;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) res += query_sum(ql, qr, p << 1, l, mid);
    if (qr >= mid + 1) res += query_sum(ql, qr, p << 1 | 1, mid + 1, r);
    return res;
}

int query_number(int ql, int qr, int p, int l, int r) {
    int res = 0;
    if (tree[p].tag == killed) {//打了不下放的标签，因此走到标签就不应该再往下走了
        if (ql <= l)return tree[p].first_num;
        else return 0;
    }
    if (ql <= l && qr >= r) {
        return tree[p].total;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) res += query_number(ql, qr, p << 1, l, mid);
    if (qr >= mid + 1) res += query_number(ql, qr, p << 1 | 1, mid + 1, r);
    return res;
}

//根据目前的战斗力，以及目标达到战斗力的差值，作为delta，现在要找到一段可以打的boss，
//用引用返回，返回的tl，tr，num分别是说
//需要打的这段区间的左右端点，还有最小的那个可能打不完，剩下了num个
//num 是第一个最小值如果剩下的话，剩下了多少个，tot就是总共这个区间里打了多少个，便于统计
void find_prey(long long w, long long delta, int &tl, int &tr, int &num, int &tot, long long &sum) {
    //要在线段树二分找到这段值
    tr = find_start(w, 1, 1, n);//要打的最大的boss的下标索引
    //接下来就是固定tr，去二分找tl&num,要找到使得总和大于delta的最大的tl
    if (tr == -1) {
        tot = -1;
        return;
    }
    int start = 1, end = tr, mid = (1 + tr + 1) >> 1;
    sum = query_sum(1, tr, 1, 1, n);
    if (sum < delta) {
        tot = -1;
        return;
    }
    sum = query_sum(mid, tr, 1, 1, n);
    //要实现最大，就得在sum==delta的时候往后找
    while (start < end) {
        if (sum >= delta)start = mid;//应该往后找，并且这个可能成为答案
        else end = mid - 1;//应该往前找，并且，这个不可能成为答案
        mid = (start + end + 1) >> 1;
        sum = query_sum(mid, tr, 1, 1, n);
    }
    tl = mid;
    //现在应该考虑，tl不打完应该可能也够，剩下的是num
    num = (int) ((sum - delta) / boss[tl]);
    sum -= num * boss[tl];//并且写好总共打的战力总值
    tot = query_number(tl, tr, 1, 1, n);
    tot -= num;//这个就是打的数目
}

//dldr是说从dl到dr的这么多要被删除，并且没有删除完，，还剩下了num个
void update(int dl, int dr, int num, int p, int l, int r) {
    if (dl <= l && dr >= r) {
        if (dl == l) {
            tree[p].sum = num * boss[l];
            tree[p].tag = killed;
            tree[p].first_num = num;
            tree[p].total = num;
            if (tree[p].total == 0)tree[p].min_w = tree[p].max_w = -1;
            else tree[p].min_w = tree[p].max_w = boss[l];
        } else {
            tree[p].sum = 0;
            tree[p].first_num = 0;
            tree[p].total = 0;
            tree[p].min_w = tree[p].max_w = -1;
            tree[p].tag = killed;
        }
        return;
    }
    int mid = (l + r) >> 1;
    if (dl <= mid)update(dl, dr, num, p << 1, l, mid);
    if (dr >= mid + 1)update(dl, dr, num, p << 1 | 1, mid + 1, r);
    push_up(p);
}

void restore(int p, int l, int r) {
    tree[p].tag = no_tag;//push_up的时候没有处理tag，虽然等会儿会处理值的问题
    if (tree[p].sum == tree[p].sum0)return;
    if (l == r) {
        tree[p].sum = tree[p].sum0;
        tree[p].first_num = number[l];
        tree[p].tag = no_tag;
        tree[p].total = number[l];
        if (tree[p].total == 0)tree[p].min_w = tree[p].max_w = -1;
        else tree[p].min_w = tree[p].max_w = boss[l];
        return;
        //因为标签没有下放，所以到了tag==killed的就可以停止了，不用再往下走修改了
        //但是有可能标签打在了两段上
    }
    int mid = (l + r) >> 1;
    restore(p << 1, l, mid);
    restore(p << 1 | 1, mid + 1, r);
    push_up(p);
}

//修改：把index位加加或减减
void modify(int p, int l, int r, long long w, int k) {
    if (l == r) {
        tree[p].first_num += k;
        tree[p].sum0 += boss[l] * k;
        tree[p].sum += boss[l] * k;
        tree[p].total += k;
        if (tree[p].total == 0)
            tree[p].max_w = tree[p].min_w = -1;
        else tree[p].max_w = tree[p].min_w = boss[l];
        number[l] += k;
        return;
    }
    int mid = (l + r) >> 1;
    if (w <= boss[mid])modify(p << 1, l, mid, w, k);
    else modify(p << 1 | 1, mid + 1, r, w, k);
    push_up(p);
}

void show_tag(int p, int l, int r) {
    if (tree[p].tag == killed)cout << p << " killed" << endl;
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    show_tag(p << 1, l, mid);
    show_tag(p << 1 | 1, mid + 1, r);
}

int main() {
    n = read();
    long long tmp[n + 1];
    int count = 0, q;
    for (int i = 1; i <= n; ++i)tmp[i] = read(), boss[++count] = tmp[i];
    q = read();
    int real_q;
    for (real_q = 1; real_q <= q; ++real_q) {
        if (cin >> query[real_q].op) {
            if (query[real_q].op == 1) {
                query[real_q].w = read();
                query[real_q].k = read();
            } else query[real_q].w = read(), boss[++count] = query[real_q].w;
        } else break;
    }
    sort(boss + 1, boss + count + 1);
    count = unique(boss, 1, count);
    sort(tmp + 1, tmp + n + 1);
    for (int i = 1, j = 1; i <= n;) {
        while (boss[j] != tmp[i]) {
            ++j;
        }
        while (boss[j] == tmp[i]) {
            ++i;
            ++number[j];
        }
    }
    n = count;
    build(1, 1, n);
    for (int i = 1; i < real_q; ++i) {
        if (query[i].op == 1) {
            long long w0 = query[i].w, w1 = query[i].k;
            if (w0 >= w1) { printf("%d%c", 0, '\n'); }
            else {
                int ans = 0;
                while (1) {
                    long long goal = find_goal(w0, 1, 1, n);
                    //void find_prey(long long w, long long delta, int &tl, int &tr, int &num, int &tot,long long &sum)
                    int tl, tr, num, tot;
                    long long sum;
                    //我下一个要达到的，要么是下个目标boss的值+1，要么就是题目询问的值
                    long long next_w;
                    if (goal == -1)next_w = w1;//说明已经没有比自己相等或者更大的了，就把w1作为目标吧
                    else next_w = ((w1 < boss[goal] + 1) ? w1 : boss[goal] + 1);
                    find_prey(w0, next_w - w0, tl, tr, num, tot, sum);
                    if (tot == -1) {
                        ans = -1;
                        break;
                    }
                    ans += tot;
                    w0 += sum;
                    update(tl, tr, num, 1, 1, n);
                    if (w0 >= w1)break;
                }
                if (ans == -1)printf("%d%c", -1, '\n');
                else printf("%d%c", ans, '\n');
                restore(1, 1, n);
//                show_tag(1, 1, n);
            }
        } else if (query[i].op == 2) {
            long long w = query[i].w;
            modify(1, 1, n, w, 1);
        } else {
            long long w = query[i].w;
            modify(1, 1, n, w, -1);
        }
    }
    return 0;
}
