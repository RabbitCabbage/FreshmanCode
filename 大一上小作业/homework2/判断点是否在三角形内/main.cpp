#include <iostream>

using namespace std;

double max(double x, double y) {
    double k = 0;
    if (x > y) k = x;
    else k = y;
    return k;
}

double min(double x, double y) {
    double k = 0;
    if (x < y) k = x;
    else k = y;
    return k;
}

int main() {
    double x1, x2, x3, x, y1, y2, y3, y;
    cin >> x1 >> y1;
    cin >> x2 >> y2;
    cin >> x3 >> y3;

    cin >> x >> y;
    if (
            ((x1 - x2) * (y2 - y3) == (x2 - x3) * (y1 - y2)) ||
            (((x3 - x1) * (y - y1) - (y3 - y1) * (x - x1) == 0) && (x >= min(x1, x3)) && (x <= max(x1, x3))) ||
            (((x2 - x1) * (y - y1) - (y2 - y1) * (x - x1) == 0) && (x >= min(x1, x2)) && (x <= max(x1, x2)) ||
             (((x2 - x3) * (y - y3) - (y2 - y3) * (x - x3) == 0) && (x >= min(x2, x3)) && (x <= max(x2, x3))))
            )
        cout << "false" << endl;
    else if (((x3 - x1) * (y - y1) - (y3 - y1) * (x - x1)) * ((x3 - x1) * (y2 - y1) - (y3 - y1) * (x2 - x1)) > 0 &&
             ((x2 - x1) * (y - y1) - (y2 - y1) * (x - x1)) * ((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) > 0 &&
             ((x2 - x3) * (y - y3) - (y2 - y3) * (x - x3)) * ((x2 - x3) * (y1 - y3) - (y2 - y3) * (x1 - x3)) > 0)
        cout << "inside" << endl;
    else cout << "outside" << endl;

    return 0;
}
