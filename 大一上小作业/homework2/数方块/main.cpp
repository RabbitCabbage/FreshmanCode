#include <iostream>

int hang_m, lie_n, cishu;
using namespace std;

int main() {
    cin >> hang_m >> lie_n >> cishu;
    int array[hang_m][lie_n];


    for (int hang_i = 1; hang_i <= hang_m; ++hang_i) {
        for (int lie_j = 1; lie_j <= lie_n; ++lie_j) {
            cin >> array[hang_i - 1][lie_j - 1];
        }
    }
    for (int cishu_k = 1; cishu_k <= cishu; ++cishu_k) {
        int sum = 0;
        int hang_quiery1, lie_quiery1, hang_quiery2, lie_quiery2;
        cin >> hang_quiery1 >> lie_quiery1 >> hang_quiery2 >> lie_quiery2;
        for (int hang = hang_quiery1; hang <= hang_quiery2; ++hang) {
            for (int lie = lie_quiery1; lie <= lie_quiery2; ++lie) {
                sum += array[hang - 1][lie - 1];
            }
        }
        cout << sum << endl;
    }

//来自董易昕学长提醒，自学前缀和；
//前缀和版本
   /* int hang_m, lie_n, cishu_k;
    cin >> hang_m >> lie_n >> cishu_k;
    int array[hang_m][lie_n];
    for (int i = 0; i < hang_m; ++i) {
        for (int j = 0; j < lie_n; ++j) {
            cin >> array[i][j];
        }
    }
    int SumArray[hang_m][lie_n];
    for (int y = 0; y < hang_m; ++y) {
        for (int x = 0; x < lie_n; ++x) {
            if (x == 0 && y == 0) SumArray[y][x] = array[y][x];
            else if (x == 0) SumArray[y][x] = SumArray[y - 1][x] + array[y][x];
            else if (y == 0) SumArray[y][x] = SumArray[y][x - 1] + array[y][x];
            else SumArray[y][x] = SumArray[y][x - 1] + SumArray[y - 1][x] - SumArray[y - 1][x - 1] + array[y][x];
        }
    }

    for (int k = 0; k < cishu_k; ++k) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int result;
        if (a == 1 && b == 1)result = SumArray[c - 1][d - 1];
        else if (a == 1)result = SumArray[c - 1][d - 1] - SumArray[c - 1][b - 2];
        else if (b == 1)result = SumArray[c - 1][d - 1] - SumArray[a - 2][d - 1];
        else
            result = SumArray[c - 1][d - 1] - SumArray[a - 2][d - 1] - SumArray[c - 1][b - 2] +
                     SumArray[a - 2][b - 2];

        cout << result << endl;
    }
*/

    return 0;
}
