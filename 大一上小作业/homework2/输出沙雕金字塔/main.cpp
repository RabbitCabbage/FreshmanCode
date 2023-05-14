#include <iostream>
using namespace std;
void printstars (int a){
    for ( int i = 1; i <= a; i++){
        for ( int j = 1; j <= a - i; j ++){
            cout<<" ";
        }
        for ( int k = 1; k <= 2 * i - 1; k ++){
             cout<< "6";
        }
        cout << endl;
    }

}
int main() {
    int num;
    cin>>num;
    printstars (num);


    return 0;
}

