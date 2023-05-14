#include <iostream>

using namespace std;

int main() {
    char type[10] = {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'};
    cin >> type;
    int typenumber;
    if (type[4] == 'x') typenumber = 0;
    else if (type[5] == 'x') typenumber = 2;
    else if (type[8] == 'x') typenumber = 1;
    int m, n;
    cin >> m >> n;
    switch (typenumber) {
        case 0:
            int intarray[20000];
            for (int im = 0; im < m; ++im) cin >> intarray[im];
            for (int in = m; in < n + m; ++in) cin >> intarray[in];
            for (int i = 0; i < m + n; ++i) cout << intarray[i]<<" ";
          cout<<endl;


            break;
        case 1:
            double doublearray[20000];
            for (int jm= 0; jm< m; ++jm) cin >> doublearray[jm];
            for (int jn= m; jn < n + m; ++jn) cin >> doublearray[jn];
            for (int j= 0; j< m + n; ++j) cout << doublearray[j]<<" ";
          cout<<endl;


            break;
        case 2:
            char charlearray[20000];
            for (int km = 0; km < m; ++km) cin >> charlearray[km];
            for (int kn = m; kn < n + m; ++kn) cin >> charlearray[kn];
            for (int k = 0; k < m + n; ++k) cout << charlearray[k]<<" ";
          cout<<endl;


            break;
    }
    return 0;
}
