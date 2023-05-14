#include <iostream>

int p, q;
using namespace std;

int main() {
    int m;
    cin >> p >> q >> m;
        int array[q - p + 1];
        for (int i = 0; i < (q - p + 1); ++i) {
            cin >> array[i];
        }
    for (int j = 0; j < m; ++j) {

        int option, x, k, y;
        cin >> option;
        if (option == 1) {
            cin >> x >> k;
            if (x < p || x > q) cout << "RE" << endl;
            else array[x - p] = k;
        } else {
            cin >> y;
            if (y < p || y > q) cout << "RE" << endl;
            else cout << array[y - p] << endl;
        }
    }
    return 0;
}
