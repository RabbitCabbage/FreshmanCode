/*#include <iostream>

using namespace std;
int n, q, m;

int main() {
    cin >> n >> m;
    int array[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> q;
        int query[q], counter[q];
        for (int j = 0; j < q; ++j) {
            cin >> query[j];
        }
        int pointer_l = 0, pointer_r;
        int min = n;
        while (pointer_l < n) {
            pointer_r = pointer_l;
            while (pointer_r < n) {
                for (int k = 0; k < q; ++k) {
                    if (array[pointer_r] == query[k])
                        ++counter[k];
                }
                int fail = 0;
                for (int h = 0; h < q; ++h) {
                    if (counter[h] == 0)fail++;
                }
                if (fail == 0) {
                    if (pointer_r - pointer_l + 1 < min) min = pointer_r - pointer_l + 1;
                    break;
                }
                pointer_r++;
            }//这时就找到了一个pointer-r
            for (int j = 0; j < q; ++j) counter[j] = 0;
            pointer_l++;
        }
        cout << n << endl;
    }
    return 0;
}*/
#include<iostream>

using namespace std;
int n, m, q;

int main() {
    cin >> n >> m;
    int array[n];
    int counter[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }
    for (int j = 0; j < m; ++j) {
        for (int k = 0; k < n; k++) {
            counter[k] = 0;
        }
        cin >> q;
        int query[q];
        int length = n;
        for (int k = 0; k < q; ++k) {
            cin >> query[k];
        }
        int pointer_r = 0, pointer_l = 0;

        while (pointer_l < n ) {
            while (pointer_r < n) {
                int a = array[pointer_r];
                ++counter[a];
                int fail = 0;
                for (int i = 0; i < q; ++i) {
                    if (counter[query[i]] == 0)fail++;
                }
                if (fail == 0) {
                    if (length > (pointer_r - pointer_l + 1))length = (pointer_r - pointer_l + 1);
                    break;
                } else pointer_r++;
            }
            while (1) {
                int a = array[pointer_l];

                counter[a]--;
                //cout<<a<<" "<<counter[a]<<"hhhhhh"<<endl;
                int fail = 0;
                for (int i = 0; i < q; ++i) {
                    if (counter[query[i]] == 0)fail++;
                }
                if (fail == 0) {
                    pointer_l++;
                    if (length > (pointer_r - pointer_l + 1))length = (pointer_r - pointer_l + 1);
                    //cout<<length<<endl;
                } else {
                    pointer_l++;
                    if ((pointer_r+1) < n) pointer_r++;
                    break;
                }
            }
        }
        cout << length << endl;
    }
    return 0;
}
