#include <iostream>

using namespace std;
int n, m;
long long sum = 0;

int main() {
    cin >> n;
    cin >> m;
    int array1[n], array2[n];
    int counter[n+1];
    counter[n]=0;
    long long jiecheng[n];
    for (int i = 1; i <= n; ++i) {
        cin >> array1[i-1];
        counter[i-1] = 0;
        if (i == 1) jiecheng[0] = 1;
        else {
            jiecheng[i - 1] = jiecheng[i - 2] * (i - 1);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < array1[i]; j++) {
            if (!counter[j]) sum += jiecheng[n - i - 1];
        }
        counter[array1[i]]++;
    }
    sum++;
    sum += m;
    for (int i = 0; i <= n; ++i)counter[i] = 0;
    long long mod = sum - 1;
    for (int i = 1; i <= n; i++) {
        long long k = mod / jiecheng[n - i];
        mod = mod % jiecheng[n - i];
        for (int j = 1; j <= n; ++j) {
            if (!counter[j]) {
                if (!k) {
                    counter[j] = 1;
                    array2[i-1] = j;
                    break;
                }
                --k;
            }
        }
    }
for(int a=0;a<n-1;++a)cout<<array2[a]<<" ";
cout <<array2[n-1]<<endl;
    return 0;
}
