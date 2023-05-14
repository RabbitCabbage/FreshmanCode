#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int studentsnum = 0;
    double sum = 0;
    double gradesarray[30];
    cout << "请输入各个学生的成绩，输入结束请输入-1" << endl;
    int i = 0;
    while (true) {
        cin >> gradesarray[i];
        if (gradesarray[i] == -1) break;
        sum += gradesarray[i];
        ++studentsnum;
        ++i;
    }
    double average = sum / studentsnum;
    double square = 0, squaresum = 0;
    for (int j = 0; j < studentsnum; ++j) {
        double every = pow((gradesarray[j] - average), 2);
        squaresum += every;

    }
    square = squaresum / studentsnum;
    cout << "平均分为：" << average << endl;
    cout << "方差为：" << square << endl;
    return 0;
}
