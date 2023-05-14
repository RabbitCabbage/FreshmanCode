#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#ifndef BUG
#define DEBUG
#endif
#endif
using namespace std;

typedef pair<int, int> ppoint;
const int W = 38, H = 100;
int w, h;
char ddata[2 * H + 1][2 * W + 10];
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int dis[H][W] = {0};
ppoint st[2];
int totst = 0;
int ans = 1;
queue<ppoint> qu;

char rread() {
    char tmp;
    scanf("%c", &tmp);
    while (tmp != '+' && tmp != '-' && tmp != '|' && tmp != ' ')
        scanf("%c", &tmp);
    return tmp;
}

bool in_range(const int &, const int &, const int &);

bool exist_edge(const int &, const int &, const int &);

void get_st(const int &, const int &, const int &);

void find_st();

void bfs();

signed main() {
#ifndef ONLINE_JUDGE
    freopen("!input.txt", "r", stdin);
    // freopen("!output.txt","w",stdout);
#endif
    scanf("%d%d", &w, &h);
    for (int i = 0; i <= 2 * h; i++)
        for (int j = 0; j <= 2 * w; j++)
            ddata[i][j] = rread();
    find_st();
    bfs();
    printf("%d\n", ans);
    return 0;
}

bool in_range(const int &nowx, const int &nowy, const int &dir) {
    return ((0 <= nowx + dx[dir] && nowx + dx[dir] < h) && (0 <= nowy + dy[dir] && nowy + dy[dir] < w));
}

bool exist_edge(const int &nowx, const int &nowy, const int &dir) {
    return ddata[nowx * 2 + 1 + dx[dir]][nowy * 2 + 1 + dy[dir]] == ' ';
}

void get_st(const int &nowx, const int &nowy, const int &dir) {
    if (!dis[nowx][nowy] && exist_edge(nowx, nowy, dir)) {
        dis[nowx][nowy] = 1;
        qu.push({nowx, nowy});
#ifdef DEBUG
        printf("%d %d %d\n", nowx, nowy, dir);
#endif
    }
    return;
}

void find_st() {
    for (int i = 0; i < h; i++) //vertical
    {
        get_st(i, 0, 1);
        get_st(i, w - 1, 0);
    }
    for (int j = 0; j < w; j++) // cross
    {
        get_st(0, j, 3);
        get_st(h - 1, j, 2);
    }
    return;
}

void bfs() {
    while (!qu.empty()) {
        ppoint tmp_pos = qu.front();
        int nowx = tmp_pos.first, nowy = tmp_pos.second;
        for (int dir = 0; dir < 4; dir++)
            if (in_range(nowx, nowy, dir) && exist_edge(nowx, nowy, dir) && !dis[nowx + dx[dir]][nowy + dy[dir]]) {
                dis[nowx + dx[dir]][nowy + dy[dir]] = dis[nowx][nowy] + 1;
                qu.push({nowx + dx[dir], nowy + dy[dir]});
                ans = max(ans, dis[nowx][nowy] + 1);
            }
        qu.pop();
    }
}//
// Created by lu'ren'jia'd's on 2021/11/21.
//

