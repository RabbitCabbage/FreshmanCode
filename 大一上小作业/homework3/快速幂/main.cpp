#include <iostream>
using namespace std;
int main() {
    int base,power;
    cin>>base>>power;
    long long int result=1;
    while(power!=1){
        if(power%2==0){
            power/=2;
            base=(base*base)%2019;
        }
        else{
            power/=2;
            result*=base;
            result%=2019;
            base=(base*base)%2019;
        }
    }
    result*=base;
    cout<<(result%2019)<<endl;
    return 0;
}
