#include <iostream>
#include <cmath>

#define Pi 3.14159265358979323846
using namespace std;

double x(double t) {
    return 16 * pow(sin(t), 3);
}

double y(double t) {
    return 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t);
}

void print(int x, int y) {

}

int main() {
    int number = 2000;
    for (int j = 0; j < 60; ++j, number -= 30) {
        double step = (2 * Pi) / number;
        double t = 0;
        cout << "x=[";
        for (int i = 0; i < number; ++i) {
            cout << (int) (x(t) * number) << ',';
            t += step;
        }
        cout << (int) (x(t) * number) << "]\n";
        cout << "y=[";
        for (int i = 0; i < number; ++i) {
            cout << (int) (y(t) * number) << ',';
            t += step;
        }
        cout << (int) (y(t) * number) << "]\n";
        cout << "scatter(x,y,'Marker','*','LineWidth',1,'MarkerEdgeColor'";
        double a, b, c;
        cin >> a >> b >> c;
        cout << ",[" << a << "," << b << "," << c << "]";
        cout << ",'MarkerFaceColor'";
        cout << ",[" << a << "," << b << "," << c << "])\n" << endl;
        cout << "hold on" << endl;
    }
    cout << "hold off" << endl;
    return 0;
}
