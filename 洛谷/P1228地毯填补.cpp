#include <iostream>

using namespace std;

//主要问题是：我现在会解最小规模，怎么样吧最小规模应用到较大的？怎么吧一个较大规模变成我会解得的小规模？
//答案是只要在最中心放一块毯子，就把没有公主的变成了有公主的
//分治法的精髓：就是尝试让大规模问题变成小规模，找到小规模的解法即可，通常用递归实现！！！
void break_down(int x, int y, int scale, int start_x, int start_y);

int main() {
    int k = 0, x, y;
    cin >> k;
    cin >> y >> x;//题目的坐标是从1开始的
    int scale = 1;
    for (int i = 0; i < k; ++i)scale *= 2;
    break_down(x, y, scale, 1, 1);
    return 0;
}

void break_down(int x, int y, int scale, int start_x, int start_y) {
    if (scale == 2) {
        if (x == start_x && y == start_y)cout << start_y + 1 << " " << start_x + 1 << " " << 1 << endl;
        else if (x == start_x + 1 && y == start_y)cout << start_y + 1 << " " << start_x << " " << 2 << endl;
        else if (x == start_x && y == start_y + 1)cout << start_y << " " << start_x + 1 << " " << 3 << endl;
        else cout << start_y << " " << start_x << " " << 4 << endl;
    } else if (x - start_x + 1 <= scale / 2 && y - start_y + 1 <= scale / 2) {
        cout << start_y + scale / 2 << " " << start_x + scale / 2 << " " << 1 << endl;
        break_down(x, y, scale / 2, start_x, start_y);
        break_down(start_x + scale / 2, start_y + scale / 2 - 1, scale / 2, start_x + scale / 2, start_y);
        break_down(start_x + scale / 2 - 1, start_y + scale / 2, scale / 2, start_x, start_y + scale / 2);
        break_down(start_x + scale / 2, start_y + scale / 2, scale / 2, start_x + scale / 2, start_y + scale / 2);
    } else if (x - start_x + 1 > scale / 2 && y - start_y + 1 <= scale / 2) {
        cout << start_y + scale / 2 << " " << start_x + scale / 2 - 1 << " " << 2 << endl;
        break_down(start_x + scale / 2 - 1, start_y + scale / 2 - 1, scale / 2, start_x, start_y);
        break_down(x, y, scale / 2, start_x + scale / 2, start_y);
        break_down(start_x + scale / 2 - 1, start_y + scale / 2, scale / 2, start_x, start_y + scale / 2);
        break_down(start_x + scale / 2, start_y + scale / 2, scale / 2, start_x + scale / 2, start_y + scale / 2);
    } else if (x - start_x + 1 <= scale / 2 && y - start_y + 1 > scale / 2) {
        cout << start_y + scale / 2 - 1 << " " << start_x + scale / 2 << " " << 3 << endl;
        break_down(start_x + scale / 2 - 1, start_y + scale / 2 - 1, scale / 2, start_x, start_y);
        break_down(start_x + scale / 2, start_y + scale / 2 - 1, scale / 2, start_x + scale / 2, start_y);
        break_down(x, y, scale / 2, start_x, start_y + scale / 2);
        break_down(start_x + scale / 2, start_y + scale / 2, scale / 2, start_x + scale / 2, start_y + scale / 2);
    } else {
        cout << start_y + scale / 2 - 1 << " " << start_x + scale / 2 - 1 << " " << 4 << endl;
        break_down(start_x + scale / 2 - 1, start_y + scale / 2 - 1, scale / 2, start_x, start_y);
        break_down(start_x + scale / 2, start_y + scale / 2 - 1, scale / 2, start_x + scale / 2, start_y);
        break_down(start_x + scale / 2 - 1, start_y + scale / 2, scale / 2, start_x, start_y + scale / 2);
        break_down(x, y, scale / 2, start_x + scale / 2, start_y + scale / 2);
    }
}