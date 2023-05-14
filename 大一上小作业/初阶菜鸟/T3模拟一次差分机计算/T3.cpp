
#include <iostream>

using namespace std;

int re[9][6];

void Print() {
    for (int j = 1; j <= 5; ++j) {

        for (int i = 8; i >= 1; --i) {

                cout << re[i][j] << " ";
        }
        cout << endl;
    }
}


int main() {
    for (int j = 1; j <= 5; ++j) {
        for (int i = 8; i >= 1; --i)
            cin >> re[i][j];
    }
    //First Step:Add
    //todo
    for (int i= 1; i<= 7; i+= 2) {
        for (int j = 1; j <= 5; ++j) {
            re[i][j] = re[i][j] + re[i+1][j];
        }
    }
    Print();

    //Second Step:Carry
    //todo
    for (int i = 1; i <= 7; i+=2) {
        for (int j= 5 ;j >= 1; --j) {
            if (re[i][j] >= 10) {
                re[i][j] -= 10;
                re[i][j - 1]++;
            }
        }
    }

    Print();

    //Third Step:Add
    //todo
    for (int i= 2;i <= 6; i+= 2) {
        for (int j = 1; j <=5; ++j) {
            re[i][j] = re[i ][j] + re[i+1][j];
        }
    }
    Print();

    //Fourth Step:Carry
    //todo
    for (int i = 2; i <= 8; i+=2) {
        for (int j = 5; j >= 1; --j) {
            if (re[i][j] >= 10) {
                re[i][j] -= 10;
                re[i][j - 1]++;
            }
        }
    }


    Print();
    return 0;
}

