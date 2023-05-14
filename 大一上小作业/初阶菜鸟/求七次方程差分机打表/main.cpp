#include <iostream>
#include <cmath>

using namespace std;

int f(int x) {
    int f = pow(x, 4) +2* pow(x, 3)+3*pow(x,2)+4*x+5;
            return f;
}

int main() {
    int array[20];
    for (int i = 0; i < 20; ++i) array[i] = f(i + 1);
    for (int k = 20; k >= 1; --k) {
        for (int j = 1; j <= k; ++j) {
            array[j - 1] = array[j] - array[j - 1];
        }
        cout << array[0] << endl;
    }


    return 0;
}
