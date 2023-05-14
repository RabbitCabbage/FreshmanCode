#include <iostream>

using namespace std;

int main() {
    int a, b, c, d, e, num, result;
    for (a = 1; a <= 9; ++a) {
        for (b = 0; b <= 9; ++b) {
            for (c = 0; c <= 9; ++c) {
                for (d = 1; d <= 9; ++d) {
                    for (e = 1; e <= 9; ++e) {
                        num = a * 1000 + b * 100 + c * 10 + d;
                        result = d * 1000 + c * 100 + b * 10 + a;
                        if (num * e == result && a != b && a != c && a != d && a != e && b != c && b != d && b != e &&
                            c != e && c != d && d != e) {
                            cout << a << " " << b << " " << c << " " << d << " " << e << endl;

                        }

                    }
                }
            }
        }
    }
    return 0;
}
