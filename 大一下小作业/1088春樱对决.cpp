//
// Created by lu'ren'jia'd's on 2022/2/28.
//

//cstdio, iostream, cmath, cstring
#include <iostream>

using namespace std;
int n, m;

int solve(int scale, int start, bool direction);

int main() {
    cin >> n >> m;
    cout << solve(n, 1, true) << endl;
    return 0;
}

//direction == 1 表示向右寻找
int solve(int scale, int start, bool direction) {
    if (scale == 1)return 1;
    int remove;//todo 这个是马上要会被去掉的,那么下一次就从start开始报数，start报的是1
    if (direction) {//向右
        if (scale - start + 1 >= m)//说明不用拐弯直接到头
            remove = start + m - 1;
        else {
            int loop = (m - (scale - start + 1)) / (scale - 1), remain = (m - (scale - start + 1)) % (scale - 1);
            if (loop % 2 == 0) {
                remove = scale - remain;
                direction = false;
            } else {
                remove = remain + 1;
                direction = true;
            }
        }
    } else {
        if (start >= m)remove = start - m + 1;
        else {
            int loop = (m - start) / (scale - 1), remain = (m - start) % (scale - 1);
            if (loop % 2 == 0) {
                remove = remain + 1;
                direction = true;
            } else {
                remove = scale - remain;
                direction = false;

            }
        }
    }
//    cout << "remove number " << remove << endl;
    //如果删除了之后继续向右报数，那么下一个继续报数的就是现在在第remove位上的人；
    // 但是如果接下来是继续向左报数，那么start也即是下一个会继续报数的将是remove-1；、
    //如果刚刚删除的是最后一个，那么remove将比下一个规模还大一，就要进行修正，如果刚刚删除的是第一个，仍然要进行修正
    int start_next;
    if (remove == scale) {
        start_next = scale - 1;//上次删除了的是最后一个，因此此处开始的位置已经超出了规模，要修正开始的人和方向；
        direction = false;
    } else if (remove == 1) {
        start_next = 1;
        direction = true;
    } else if (direction)start_next = remove;
    else start_next = remove - 1;
    int id = solve(scale - 1, start_next, direction);
    if (id >= remove)return id + 1;
    else return id;
}
