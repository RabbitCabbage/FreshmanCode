#include <iostream>
using namespace std;
int main() {
    int num,i,sum = 0,count;
    for (num = 3; num <= 100;num +=2){
        count = 0;
        for (i = 1;i <= num;i += 2){
            if ( num % i == 0) count ++;

        }
        if ( count == 2) {
            sum += num;
            cout << num << endl;
        }
    }
    cout << sum << endl;
    return 0;
}
