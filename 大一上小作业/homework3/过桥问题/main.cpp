/*#include <iostream>
#include <set>

using namespace std;
set<int> s;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        s.insert(a);
    }
    const int size = s.size();
    int array[size], i = 0;
    set<int>::iterator it;
    for (it = s.begin(); it != s.end(); ++it) {
        array[i] = *it;
        ++i;
    }
    int time = 0;
    if (n == 2)cout << array[1] << endl;
    else if (n == 3)cout << array[0] + array[1] + array[2] << endl;
    else {
        if ((n - 2) % 4 == 0) {
            for (int j = 3; j < n; j += 2) {
                time += array[j];
            }
            time += (2*((n-2)/4) * array[1]);
        } else if ((n - 2) % 4 == 1) {
            for (int j = 4; j < n; j += 2) {
                time += array[j];
            }
            time += (2*((n-2)/4) * array[1]);
            time += (array[0] + array[1] + array[2]);
        } else if ((n - 2) % 4 == 2) {
            for (int j = 3; j < n; j += 2) {
                time += array[j];
            }
            time += ((2*((n-2)/4) + 3) * array[1]);
            time += array[0];
        } else if ((n - 2) % 4 == 3) {
            for (int j = 2; j < n; j += 2) {
                time += array[j];
            }
            time += ((2*((n-2)/4) + 3) * array[1]);
            time += array[0];
            time += array[0];

        }
        cout<<time<<endl;
    }
    return 0;
}*/
#include <iostream>
#include<algorithm>
int n;
using namespace std;
int main() {
    cin>>n;
     long long array[n];
    for (int a = 0; a <= n-1; ++a) {
        cin >> array[a];
    }
    sort(array,array+n);
    //time的i表示已经过去i个人，array的表示下标
    long long time[n+1];
    time[1]=array[0];
    time[2]=array[1];
    for(int i=1;i<n-1;i++){
        long long a=time[i]+array[1]*2+array[0]+array[i+1];
        long long b=time[i+1]+array[0]+array[i+1];
        time[i+2]=min(a,b);
    }
   cout<<time[n]<<endl;
    return 0;
}



