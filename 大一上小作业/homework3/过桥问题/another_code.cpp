//
// Created by lu'ren'jia'd's on 2021/10/23.
//

#include<iostream>
#include<utility>
#include<algorithm>
using namespace std;
int n,m;

int main(){
    cin>>n>>m;
    pair<int,int>p[n];
    for(int i=0;i<n;++i){
        cin>>p[i].first;
    }
    for(int i=0;i<n;++i){
        cin>>p[i].second;
    }
    sort(p,p+n);
    int sum=0;
    if(m>n){
        for(int i=m;i>0;++i){
            sum+=
        }
    }
    return 0;
}