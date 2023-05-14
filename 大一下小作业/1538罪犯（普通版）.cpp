#include <iostream>

using namespace std;
const int maxn = 2e4 + 5;
const int maxm = 1e5 + 5;
int m, n;
struct cfl {
    int a, b;
    long long c;
};
cfl conflict[maxm];

void sort(cfl list[], int left, int right) {
    if (left >= right)return;
    int start = left, end = right;
    cfl pivot = list[start];
    while (left < right) {
        while (left < right && list[right].c <= pivot.c)right--;
        while (left < right && list[left].c >= pivot.c)left++;
        if (left < right) {
            cfl tmp = list[left];
            list[left] = list[right];
            list[right] = tmp;
        }
    }
    list[start] = list[left];
    list[left] = pivot;
    sort(list, start, left - 1);
    sort(list, left + 1, end);
}

int father[maxn]{0};
int enemy[maxn]{0};

int find_father(int x) {
    if (father[x] == x)return x;
//    else return father[x] = find_father(father[x]);
    else return father[x] = find_father(father[x]);
}

void merge(int x, int y) {
    x = find_father(x);
    y = find_father(y);
    if(x==y)return;
    else father[x] = y;
}

bool check(int x, int y) {
    x = find_father(x);
    y = find_father(y);
    return x == y;
}

int main() {
    scanf("%d %d\n", &n, &m);
    for (int i = 1; i <= n; ++i)father[i] = i;
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %lld", &conflict[i].a, &conflict[i].b, &conflict[i].c);
    }
    sort(conflict, 1, m);
    for (int i = 1; i <= m; ++i) {
        if (check(conflict[i].a, conflict[i].b)) {
            printf("%lld\n", conflict[i].c);
            return 0;
        }//说明这两个罪犯之间存在着更大的怨气，为了避免这个怨气，输出这个值
        else {
            if (enemy[conflict[i].a] == 0) {
                enemy[conflict[i].a] = conflict[i].b;
            } else {
                merge(conflict[i].b, enemy[conflict[i].a]);
                //吧b和a的敌人们（包括a在内）合并在一起，他们以后就不能一起出现了，不然元气值更大
            }
            if (enemy[conflict[i].b] == 0) {
                enemy[conflict[i].b] = conflict[i].a;
            } else {
                merge(conflict[i].a, enemy[conflict[i].b]);
            }
        }
    }
    printf("%lld\n", 0ll);
    return 0;
}