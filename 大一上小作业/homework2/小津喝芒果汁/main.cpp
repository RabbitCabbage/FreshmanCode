#include <iostream>

using namespace std;
int beishu;

int main() {

    cin >> beishu;
    int average = 0;
    int mongo[beishu];
    for (int i = 0; i < beishu; ++i) {
        cin >> mongo[i];
    }

    int renshu;
    for (renshu = 1; renshu <= beishu; renshu++) {
        for (int qishi = 0; qishi <= beishu - renshu; qishi++) {
            int sum = 0;
            for (int counter = qishi; counter - qishi <= renshu - 1; ++counter) {
                sum += mongo[counter];
            }
            if (average < (sum / renshu))average = (sum / renshu);

        }


    }
    cout << average << endl;
    return 0;
}
