/*#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int x1, x2;
    cin >> x1 >> x2;
    int g1, g2, s1, s2, b1, b2, q1, q2;
    g1 = x1 % 10;
    g2 = x2 % 10;
    s1 = x1 % 100 / 10;
    s2 = x2 % 100 / 10;
    b1 = x1 % 1000 / 100;
    b2 = x2 % 1000 / 100;
    q1 = x1 / 1000;
    q2 = x2 / 1000;
    int g3, s3, b3, q3, c1, c2, c3;
    g3 = (g2 != g1);
    c1 = (g2 && g1);
    s3 = ((s1 != s2) != c1);
    c2 = (c1 + s1 + s2 >= 2 );
    b3 = ((b2 != b1) != c2);
    c3 = (c2 + b1 + b2 >= 2);
    q3 = ((q1 != q2) != c3);
int x3 = q3 * 1000 + b3 * 100 + s3 * 10 + g3;
 cout << q3 << b3 << s3 << g3 << endl;
return 0;}*/
//纯二进制版本
#include <iostream>

using namespace std;

int main() {
    bool g1, g2, s1, s2, b1, b2, q1, q2;
    char str1[5];
    cin >> str1;
    q1 = str1[0] - 48;
    b1 = str1[1] - 48;
    s1 = str1[2] - 48;
    g1 = str1[3] - 48;
    char str2[5];
    cin >> str2;
    q2 = str2[0] - 48;
    b2 = str2[1] - 48;
    s2 = str2[2] - 48;
    g2 = str2[3] - 48;
    bool g3, s3, b3, q3, c1, c2, c3;
    g3 = (g2 != g1);
    c1 = (g2 && g1);
    s3 = ((s1 != s2) != c1);
    c2 = (c1 + s1 + s2 >= 2);
    b3 = ((b2 != b1) != c2);
    c3 = (c2 + b1 + b2 >= 2);
    q3 = ((q1 != q2) != c3);
    cout << q3 << b3 << s3 << g3 << endl;
}


