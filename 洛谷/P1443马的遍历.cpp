#include <iostream>
#include <queue>

using namespace std;
int dx[8] = {1, 1, 2, 2, -1, -1, -2, -2};
int dy[8] = {2, -2, 1, -1, 2, -2, 1, -1};
int n, m;

//void OneStep(int x, int y, int **grim, int step) {
//    int newly_visited = 0;
//    for (int i = 0; i < 8; ++i) {
//        int x_now = x + dx[i], y_now = y + dy[i];
//        if (y_now < n && x_now < m && y_now >= 0 && x_now >= 0) {
//            if (grim[y_now][x_now] == -1) {
//                grim[y_now][x_now] = step;
//                newly_visited++;
//            }
//        }
//    }
//    if (newly_visited == 0)return;
//    for (int i = 0; i < 8; ++i) {
//        int x_now = x + dx[i], y_now = y + dy[i];
//        if (y_now < n && x_now < m && y_now >= 0 && x_now >= 0 && grim[y_now][x_now] == step) {
//            OneStep(x_now, y_now, grim, step + 1);
//        }
//    }
//}
////你这个实际上并不是广搜，你是可以先搜所有的第一步，但是从第二步开始，就又是在深度搜了真甜蜜sb
int main() {
    int x, y;
    cin >> n >> m >> x >> y;
    int **grim = new int *[n];
    for (int i = 0; i < n; ++i) {
        grim[i] = new int[m];
        for (int j = 0; j < m; ++j)grim[i][j] = -1;
    }
    grim[--y][--x] = 0;
    queue<pair<int, int>> q;
    q.push({x, y});
    while (!q.empty()) {
        x = q.front().first;
        y = q.front().second;
        q.pop();
        for (int i = 0; i < 8; ++i) {
            int x_now = x + dx[i], y_now = y + dy[i];
            if (y_now < n && x_now < m && y_now >= 0 && x_now >= 0 && grim[y_now][x_now] == -1) {
                q.push({x_now, y_now});
                grim[y_now][x_now] = grim[y][x]+1;
            }
        }

    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            printf("%-5d", grim[i][j]);
        cout << endl;
        delete []grim[i];
    }
    delete []grim;
    return 0;
}

