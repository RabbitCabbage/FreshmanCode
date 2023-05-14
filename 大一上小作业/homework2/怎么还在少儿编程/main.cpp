#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int A, B, C,I ;
    cin>>A>>B>>C;
    if (B < A){
        I = A;
        A = B;
        B = I;
    }
    if (C < A){
        I = A;
        A = C;
        C = I;
    }
    if (B > C){
        I = B;
        B = C;
        C = I;
    }
    char ch[4];
    cin>>ch;
    int ascii ,x1,x2,x3;

    ascii = ch[0];
    switch (ascii) {
        case 65:
            x1 = A;
            break;
        case 66:
            x1 = B;
            break;
        case 67:
            x1 = C;
            break;
    }
    ascii = ch[1];
    switch (ascii) {
        case 65:
            x2 = A;
            break;
        case 66:
            x2 = B;
            break;
        case 67:
            x2 = C;
            break;
    }
    ascii = ch[2];
    switch (ascii) {
        case 65:
            x3 = A;
            break;
        case 66:
            x3 = B;
            break;
        case 67:
            x3 = C;
            break;
    }
    cout<<x1<<" "<<x2<<" "<<x3<<endl;
    return 0;
}
