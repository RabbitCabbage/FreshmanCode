#include <iostream>
using namespace std;
int main() {
    cout << "请输入一个整数" << endl;
    int num,max;
    cin >> num ;
    for ( int i = 1; i < num ; i++) {
        if ( num % i == 0){
            max = i;
        }

    }
    cout <<"输入数据的最大因子为"<< max << endl;
    cout << " 请输入两个整数" << endl;
    int num1, num2, mod,result;
     cin >> num1 >> num2;
     for (; num1 != 0 && num2 != 0;){
         if ( num1 < num2 ){
             mod = num2 % num1;
             num2 = num1;
             num1 = mod;
         }
         else {
             mod = num1 % num2;
             num1 = num2;
             num2 = mod;
         }
     }
     cout << "两个数的最大公因数为：";
     if ( num1 == 0) cout << num2 << endl;
     else cout << num1<< endl;

     cout << "请输入两个整数："<< endl;
    cin >> num1 >> num2;
    for (; num1 != 0 && num2 != 0;){
        if ( num1 < num2 ){
            result = num2 - num1;
            num2 = num1;
            num1 = result;
        }
        else {
            result = num1 - num2;
            num1 = num2;
            num2 = result;
        }
    }
    cout << "两个数的最大公因数为：";
    if ( num1 == 0) cout << num2 << endl;
    else cout << num1<< endl;


    return 0;
}
