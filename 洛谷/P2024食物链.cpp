//
// Created by lu'ren'jia'd's on 2022/4/30.
//

#include <iostream>

const int maxn = 5e4 + 5;
const int maxk = 1e5 + 5;
int relation[maxn * 3];
//这是记录关系的数组，
//0~n the same type;n+1~2n the preditor,2n+1~3nprey
int n, k;

void init(int tot) {
    tot *= 3;
    for (int i = 0; i <= tot; ++i)
        relation[i] = i;
}

int find_father(int x) {
    if (relation[x] == x)return x;
    else return relation[x] = find_father(relation[x]);
}

bool check(int x, int y) {
    return find_father(x) == find_father(y);
}

void merge(int x, int y) {
    x = find_father(x), y = find_father(y);
    relation[x] = y;
}

int main() {
    scanf("%d %d", &n, &k);
    init(n);
    int count = 0;
    while (k--) {
        int rela, x, y;
        scanf("%d %d %d", &rela, &x, &y);
        if (x > n || y > n) {
            count++;
            continue;
        }
        if (x == y) {
            if (rela == 2)count++;
            continue;
        }
        if (rela == 1) {
            if (check(x, y + n) || check(x, y + 2 * n))
                count++;
            else {
                //xy确实是相同种类的
                merge(x, y);
                merge(x + n, y + n);
                merge(x + 2 * n, y + 2 * n);
            }
            continue;
        }
        if (rela == 2) {
            //现在说x会吃y，如果是假的话，x应该在y的同类或者食物里
            if (check(x, y) || check(x, y + 2 * n)) {
                ++count;
            } else {
                merge(x, y + n);//x是y的捕食者
                merge(x + 2 * n, y);//y是x的食物
                merge(y + 2 * n, x + n);//x的捕食者，也是y的食物
                //因为要形成三个动物的闭环
            }
        }
    }
    printf("%d\n", count);
    return 0;
}