#include "src.hpp"
using namespace std;

int main()
{
    int days=0;
    cin>>days;
    for(int i=0;i<days;++i)
    {
        int a,b;
        cin>>a>>b;
        getItem(a,b);
        int half=factory[1]();
        int remain=factory[0]();
        int product=factory[2]();
        printf("%d %d %d\n",remain,half,product);
    }
    return 0;
}//
// Created by lu'ren'jia'd's on 2021/11/12.
//

