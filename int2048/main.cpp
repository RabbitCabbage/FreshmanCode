#include <iostream>
#include"int2048.hpp"
using namespace std;

int main() {
    cout<<53*59<<endl;
    cout<<52*58<<endl;
    cout<<1371*11%3016<<endl;
    cout<<3016%13<<endl;
    sjtu::int2048 a,b,c;
    cin>>a;
    b=1;
    for (int i = 1; i <= 11; i++) {
        b*=a;
        c= b/3127;
        b=b-c*3127;
    }
cout<<b<<endl;

    cin>>a;
    b=1;
    for (int i = 1; i <= 1371; i++) {
        b*=a;
        c= b/3127;
        b=b-c*3127;
    }
    cout<<b<<endl;
    return 0;
}//
// Created by lu'ren'jia'd's on 2021/11/17.
//

