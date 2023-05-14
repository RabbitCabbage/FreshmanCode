#include <iostream>
#include <cmath>


using namespace std;

int jiecheng(int n) {
    int result = 1;
    for (int i = n; i >= 1; --i) {
        result *= i;
    }
    return result;

}

long double f(long double x) {
    long double f = pow(x, 7) / jiecheng(7) + pow(x, 6) / jiecheng(6) + pow(x, 5) / jiecheng(5) + pow(x, 4) / jiecheng(4) +
               pow(x, 3) / jiecheng(3) + pow(x, 2) / 2 + x + 1;
    return f;
}

int main() {
    long double array[20];
    for (int i = 0; i < 20; ++i) array[i] = f((i + 1));
//做差，重新赋值给数组，再做差。。。。。我让它多做几次，取第七次就行
    for (int i = 19; i >= 1; --i) {
        for (int j = 1; j <= i; ++j) {
            array[j - 1] = array[j] - array[j - 1];
        }
        cout << array[0] << endl;
    }


    return 0;
}

