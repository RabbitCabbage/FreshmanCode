#include <iostream>
#include <cmath>
//感觉截断误差挺大的，在3以后不可忽略。
using namespace std;

int qiujiecheng(int a) {
    int jiecheng = 1;
    for (int i = a; i >= 1; --i) {
        jiecheng *= i;
    }
    return jiecheng;

}

int main() {
    //求e^x
    int x = 1;
    cout << "请输入正整数x(如果希望结束函数计算请输入0)" << endl;
    while (x != 0) {
        double add, sum = 1;
    cin >> x;
        int i = 1;
        do {
            add = (pow(x, i)) / qiujiecheng(i);
            sum += add;
            ++i;
        } while (add >= 0.000001);
        cout << " e ^ x = " << sum << endl;
    }

    return 0;
}
