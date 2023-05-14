#include <iostream>

using namespace std;

int main() {
    int time[1000];
    int m;
    cin >> m;
    for (int j = 0; j < m; ++j) {
        cin >> time[j];
    }


    int counter = 0;
    for (int k = 0; k < m; ++k) {
        if (time[k] > 13) ++counter;
    }


    if (counter == 0) {
        int i = 0, finalsum = 0, transfer = 0;
        while (1) {//sum是每次循环的部分和，total用来检测是否大于13
            int sum = 0;
            int total = 0;
            for (int h = i; h < m; ++h) {

                total += time[h];
            }
            if (total <= 13) {
                finalsum += total;
                break;
            } else {
                while (sum <= 13) {
                    sum += time[i];
                    transfer = sum;
                    ++i;
                }
                --i;
                finalsum += 20;
            }
        }

        cout << finalsum << endl;
    } else cout << "you died" << endl;

    return 0;
}
