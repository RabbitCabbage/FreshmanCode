#include <iostream>
#include <algorithm>

struct cow {
    int h;
    int w;
    long long z;
};

bool compare_height(cow a, cow b) {
    return a.h < b.h;
}

bool compare_weight(cow a, cow b) {
    return a.w < b.w;
}

using namespace std;
int N, A, B;
long long C;
int main() {
    int max=0;
    int minh, minw;
    cin >> N;
    cin >> A >> B >> C;
    cow array[N];
    for (int i = 0; i < N; ++i) {
        cin >> array[i].h >> array[i].w;
        array[i].z = array[i].h * A + array[i].w * B;
    }

    for (int i = 0; i < N; ++i) {
        sort(array, array + N , compare_height);
        minh = array[i].h;
        sort(array + i, array + N , compare_weight);//把i后面的排序
        for (int j = i; j < N; ++j) {
            minw = array[j].w;
            long long z = C + minh * A + minw * B;
            int counter=0;
            for (int k=j;k<N;++k){
                if(array[k].z<=z)counter++;
            }
            if(counter>max) max=counter;
        }
    }
cout<<max<<endl;
    return 0;
}
