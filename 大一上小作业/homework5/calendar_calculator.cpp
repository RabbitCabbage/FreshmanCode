#include <iostream>

using namespace std;

int main() {
    int counter = 0;
    for (int i = 1; i <= 9999; i++) {
        if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) {cout << i << endl;
            counter++;}
    }
    cout <<"total"<< counter << endl;//2424
    cout<<9999*365+2424<<endl;//3652059
    return 0;
}//
// Created by lu'ren'jia'd's on 2021/11/17.
//

