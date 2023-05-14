#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class CircleSet {
    friend istream &operator>>(istream &in, CircleSet &obj);

private:
    struct Circle {
        long long x, y, r;

        Circle(long long _x = 0, long long _y = 0, long long _r = 0) : x(_x), y(_y), r(_r) {}
    };

    int count;//集合中圆的数目
    Circle *circles;//集合中所有圆
public:
    CircleSet(int n) : count(n) {
        circles = new Circle[n];
    }

    ~CircleSet() { delete[]circles; }

    long long &operator[](int p) {
        return circles[p].r;
    }

    bool checkContaining(int p, int q) {
        long long outer_r = circles[p].r;
        long long inner_r = circles[q].r;
        long long outer_x = circles[p].x;
        long long inner_x = circles[q].x;
        long long outer_y = circles[p].y;
        long long inner_y = circles[q].y;
        if (outer_r > inner_r &&
            pow((inner_x - outer_x), 2) + pow((inner_y- outer_y), 2) < pow((outer_r - inner_r), 2))
            return true;
        else return false;
    }

    int getCircleContainingQ(int q) {
        long long min =9223372036854775807;
        for (int i = 0; i < count; ++i) {
            if (checkContaining(i,q)) {
                min = (min < circles[i].r ? min : circles[i].r);
            };

        }
        return min;
    }
};

istream &operator>>(istream &in, CircleSet &obj) {
    for (int i = 0; i < obj.count; ++i) {
        in >> obj.circles[i].x >> obj.circles[i].y >> obj.circles[i].r;
    }
    return in;
}

int main() {
    int n, m, type;
    cin >> n >> m;
    CircleSet set(n);
    cin >> set; //输入集合中的所有圆
    while (m--) {
        int type, p, q;
        cin >> type;
        if (type == 1) {
            //do nothing
        } else if (type == 2) {
            for (int i = 0; i < n; ++i) {
                cout << set[i] << ' ';
            }
            cout << endl;
        } else if (type == 3) {
            cin >> p >> q;
            cout << set.checkContaining(p, q) << endl;
        } else if (type == 4) {
            cin >> q;
            cout << set.getCircleContainingQ(q) << endl;
        }
    }
    return 0;
