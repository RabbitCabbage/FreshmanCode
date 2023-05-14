#include <iostream>
using namespace std;
int main() {
    int a;
    for (a = 7; a % 2 != 1 || a % 3 != 2 || a % 5 !=4 || a % 6!= 5;a += 7);
    cout << a <<endl;
    int xigua,pingguo,juzi;
    for ( xigua = 1; xigua <= 14; xigua ++){
        for ( pingguo = 1; pingguo * 3 + xigua * 10 < 150; pingguo ++){

            juzi = 150 - pingguo * 3 - xigua * 10;
            if ( xigua + pingguo + juzi == 100){
            cout << "西瓜买"<< xigua << "个"<<endl;
            cout << "苹果买"<< pingguo << "个"<<endl;
            cout << "橘子买"<< juzi << "个"<<endl;
            }
        }

    }
    return 0;
}
