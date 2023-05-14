#include<iostream>
#include <string>
#include <cstring>

using namespace std;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int w, h;
int array[210][90]={0};
struct point {
    int x, y;
};

void bfs(int distance[][90], int x, int y);

int main() {
    pair<int, int> exit1;
    pair<int, int> exit2;
    bool used1 = false;
    cin >> w >> h;
    getchar();
    for (int i = 0; i < 2 * h + 1; i++) {
        string s;
        getline(cin, s);
        for (int j = 0; j < 2 * w + 1; j++) {
            char ch = '\0';
            ch = s[j];
            if (ch == '-' || ch == '+' || ch == '|')array[i][j] = 1;
            else if (i == 0 || j == 0 || i == 2 * h || j == 2 * w) {
                if (!used1) {
                    exit1.first = i;
                    exit1.second = j;
                    used1 = true;
                } else {
                    exit2.first = i;
                    exit2.second = j;
                }
            }
        }
    }

    int distance1[210][90];
    int distance2[210][90];
    memset(distance1, -1, sizeof(distance1));
    memset(distance2, -1, sizeof(distance2));
    bfs(distance1, exit1.first, exit1.second);
    bfs(distance2, exit2.first, exit2.second);
    int max = 0;
    for (int i = 0; i < 210; ++i) {
        for (int j = 0; j < 90; j++) {
            distance1[i][j] = min(distance1[i][j], distance2[i][j]);
            if (distance1[i][j] > max)max = distance1[i][j];
        }
    }
    cout << (max+1)/2 << endl;
    return 0;
}

//x_column,y_row
void bfs(int distance[][90], int x, int y) {
    point points[210 * 90];
    distance[x][y] = 0;
    int front = 0, rear = 1;
    points[1] = (point) {x, y};
    while (front < rear) {
        point now = points[++front];
        for (int i = 0; i < 4; i++) {
            int now_x = now.x + dx[i], now_y = now.y + dy[i];
            if (now_x >= 0 && now_x <= 2 * h && now_y >= 0 && now_y <= 2 * w && !array[now_x][now_y] &&
                distance[now_x][now_y] == -1)//可以走并且没有走过
            {
                distance[now_x][now_y] = distance[now.x][now.y] + 1;
                points[++rear] = point{now_x, now_y};
            }
        }
    }
}//
// Created by lu'ren'jia'd's on 2021/11/20.
//
