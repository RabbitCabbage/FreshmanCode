//
// Created by lu'ren'jia'd's on 2022/5/27.
//

//有s个无线通信装置说明可以有s个村庄没有代价直接相连
//那么我们把边排序之后跑一遍kruskal就可以了，并且跑到p-s条边就可以停止了
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;
const int maxp = 5e2 + 5;
int s, p;
int x[maxp];
int y[maxp];
struct edge {
    int from, to;
    long long value;//这个是边长长度的平方
} e[maxp * maxp];//每两个村庄之间都会有道路，因此应该是cn2
int total = 0;

void sort(edge array[], int l, int r) {
    if (l >= r)return;
    int start = l, end = r;
    edge pivot = array[start];
    while (l < r) {
        while (l < r && array[r].value >= pivot.value)r--;
        while (l < r && array[l].value <= pivot.value)l++;
        if (l < r) {
            edge tmp = array[l];
            array[l] = array[r];
            array[r] = tmp;
        }
    }
    array[start] = array[l];
    array[l] = pivot;
    sort(array, start, l - 1);
    sort(array, l + 1, end);
}

void add(int from, int to, long long value) {
    total++;
    e[total].to = to;
    e[total].value = value;
    e[total].from = from;
}

int father[maxp];

void init() {
    for (int i = 0; i < maxp; ++i)father[i] = i;
}

int find_father(int x_) {
    if (father[x_] == x_)return x_;
    else return father[x_] = find_father(father[x_]);
}

void unit(int x_, int y_) {
    x_ = find_father(x_);
    y_ = find_father(y_);
    father[x_] = y_;
}

bool check(int x_, int y_) {
    return find_father(x_) == find_father(y_);
}

long long kruskal() {
    sort(e, 1, total);//总共有total条边，错不了
    long long answer=0;
    init();
    //开始从小到大找这些边，我们需要连p-1条边
    //现在已经有s条边相当于已经连上了，就只需要p-s-1条边
    int num = 0;
    for (int i = 1; num <= p - s - 1 && i <= total; ++i) {
        //我们的本意是过了这total条边，
        //但是同时还记上数，当已经全部联通的时候就可以break了
        int from = e[i].from, to = e[i].to;
        if (check(from, to))continue;
        else {
            num += 1;
            unit(from, to);
            //cout << "connect " << from << " " << to << " at cost " << e[i].value << endl;
            if (e[i].value > answer)answer = e[i].value;
        }
    }
    return answer;
}

int main() {
    scanf("%d %d", &s, &p);
    for (int i = 1; i <= p; ++i) {
        scanf("%d %d", &x[i], &y[i]);
    }
    for (int i = 1; i <= p; ++i) {
        for (int j = i + 1; j <= p; ++j) {
            long long square = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
            add(i, j, square);
            //cout << "add edge " << i << " " << j << " " << square << endl;
        }
    }
    long long answer_square = kruskal();
    printf("%.2lf", sqrt(answer_square));
    return 0;
}