#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

ifstream input; // 题目的输入文件
ifstream output; // 用户输出

const int maxn = 1e5 + 10;
int T, n, dat[maxn], a[9][9];
char str[100];
double realScore = 0;

inline double calScore(int curScore) {
    double res;
    if (curScore == 0)
        res = 0;
    else if (curScore == n)
        res = 1;
    else if (curScore < sqrt(n))
        res = log(curScore) / (2 * log(n));
    else
        res = ((n + 3 * curScore) / 4.0 - sqrt(n)) / (n - sqrt(n));
    return res;
}

void judge() {
    input >> T;
    input >> n;
    for (int i = 0; i < n; i++)
        input >> dat[i];

    int curScore = 0;
    while (curScore < n) {
        int p;
        output >> p;
        if ((dat[curScore] == 3 || dat[curScore] >= 6) && p >= 9 || dat[curScore] == 5 && p >= 8) {
            realScore = calScore(curScore);
            throw ("position is not valid.");
        }

        --p;
        if (dat[curScore] == 1) {
            if (a[8][p])break;
            a[8][p] = 2;
        } else if (dat[curScore] == 2) {
            if (a[8][p] || a[7][p])break;
            a[8][p] = a[7][p] = 2;
        } else if (dat[curScore] == 3) {
            if (a[8][p] || a[8][p + 1])break;
            a[8][p] = a[8][p + 1] = 2;
        } else if (dat[curScore] == 4) {
            if (a[8][p] || a[7][p] || a[6][p])break;
            a[8][p] = a[7][p] = a[6][p] = 2;
        } else if (dat[curScore] == 5) {
            if (a[8][p] || a[8][p + 1] || a[8][p + 2])break;
            a[8][p] = a[8][p + 1] = a[8][p + 2] = 2;
        } else if (dat[curScore] == 6) {
            if (a[8][p] || a[7][p] || a[8][p + 1] || a[7][p + 1])break;
            a[8][p] = a[7][p] = a[7][p + 1] = 2;
        } else if (dat[curScore] == 7) {
            if (a[8][p + 1] || a[7][p] || a[8][p] || a[7][p + 1])break;
            a[8][p + 1] = a[7][p] = a[7][p + 1] = 2;
        } else if (dat[curScore] == 8) {
            if (a[8][p] || a[7][p] || a[8][p + 1])break;
            a[8][p] = a[7][p] = a[8][p + 1] = 2;
        } else if (dat[curScore] == 9) {
            if (a[8][p] || a[8][p + 1] || a[7][p + 1])break;
            a[8][p] = a[8][p + 1] = a[7][p + 1] = 2;
        }
        //todo
        std::cout << p << std::endl;
        for (int i = 8; i >= 0; i--) {
            for (int j = 0; j < 9; j++)
                printf("%d ", a[i][j]);
            printf("\n");
        }
        std::cout << std::endl;
        ++curScore;

        int drop = 10;
        for (int j = 0; j < 9; ++j)
            for (int i = 0; i < 9; ++i)
                if (a[i][j] == 2) {
                    int w = -1;
                    for (int k = 0; k < 9; ++k)
                        if (a[k][j] == 1)
                            w = k;
                    if (i - w - 1 < drop)
                        drop = i - w - 1;
                    break;
                }
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                if (a[i][j] == 2) {
                    a[i][j] = 0;
                    a[i - drop][j] = 1;
                }

        for (int i = 0; i < 9;) {
            bool flag = true;
            for (int j = 0; j < 9; ++j)
                if (a[i][j] == 0) {
                    flag = false;
                    break;
                }
            if (flag) {
                for (int j = i + 1; j < 9; ++j)
                    for (int k = 0; k < 9; ++k)
                        a[j - 1][k] = a[j][k];
                for (int j = 0; j < 9; ++j)
                    a[8][j] = 0;
            } else
                ++i;
        }
    }

    for (int i = 8; i >= 0; i--) {
        for (int j = 0; j < 9; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }

    if (curScore < n) {
        std::cout << "这里停止了 " << curScore << std::endl;
        realScore = calScore(curScore);
        throw ("piece does not fit.");
    } else {
        realScore = 1.0;
    }
}

int main(int argc, char *argv[]) {

    try {
        input.open(argv[1]); // 题目的输入文件
        output.open(argv[2]); // 用户输出


        // fscanf , fprintf
        try {
            judge();
            printf("Your score: %lf\n", realScore);
            // score << realScore << endl ;
            // message << "ok." << endl ;
        } catch (const char *s) {
            printf("%s\n", s);
            printf("Your score: %lf\n", realScore);
            // score << realScore << endl;
            // message << s << endl;
        }

        input.close();
        output.close();
    } catch (...) {
        return -1;
    }

    return 0;
}
