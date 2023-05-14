/*#include <iostream>

using namespace std;
int length;
const int NEGMAXi=-1e4+1;
int main() {
    int maxsum(int a[], int right, int left);
    cin >> length;
    int array[length];
    for (int k = 0; k < length; ++k) {
        cin >> array[k];
    }
   int a= maxsum(array, length - 1, 0) ;
    cout<<a<<endl;
    return 0;
}

int max3(int a, int b, int c) {
    int temp = (a > b ? a : b);
    return (temp > c ? temp : c);
}

int maxsum(int a[], int right, int left) {//right=length-1;
    if (left == right) return (a[left] > 0 ? a[left] : 0);
    if (right-left==1){
        int op=max3(a[left],a[right],a[left]+a[right]);
        return (op>0?op:0);
    }
    int center = (left + right) / 2;
    int left_max = maxsum(a, center, left);
    int right_max = maxsum(a, right, center+1);
    int semi_left_max = NEGMAXi, semi_right_max = NEGMAXi;
    int left_sum = 0, right_sum = 0;
    for (int i = left; i <= center; ++i) {
        left_sum += a[i];
        if (left_sum > semi_left_max)semi_left_max = left_sum;
    }
    for (int j = center + 1; j <= right; ++j) {
        right_sum += a[j];
        if (right_sum > semi_right_max)semi_right_max = right_sum;
    }
    return max3(left_max, right_max, semi_left_max + semi_right_max);
}*/
#include<iostream>
using namespace std;
int length;
int main(){
    cin>>length;
    int array[length];
    for (int k = 0; k < length; ++k) {
        cin >> array[k];
    }
    int sum=0;
    int max=0;
    for(int j=0;j<length;++j){
       if(sum>0) sum+=array[j];
       else sum=array[j];
       if(max<sum) max=sum;
    }
    cout<<max<<endl;
    return 0;
}

