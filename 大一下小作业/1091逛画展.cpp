//
// Created by lu'ren'jia'd's on 2022/3/18.
//
#include <iostream>
#include <cstring>

using namespace std;
int n, m;//there is n pictures by m painters;
int main() {
    cin >> n >> m;
    int author[n];
    for (int i = 0; i < n; ++i)cin >> author[i];//the author of the picture;
    int numbers[m + 1];//in the window the number of someone's works;
    memset(numbers, 0, sizeof(numbers));
    int l = 0, r = 0, count = 0;
    //use count to count how many authors have covered;
    while (1) {
        if (numbers[author[r]] == 0)++count;
        ++numbers[author[r]];
//        cout<<"r = "<<r<<" author = "<<author[r]<<" count = "<<count<<endl;
        if (count == m)break;
        else ++r;
    }
    //then the l ~ r have covered all the authors then we need to move the l and r;
    int ans_l = l, ans_r = r, min = ans_r - ans_l + 1;
    //ready for the circle to find the answer;
    while (r < n) {
        //first move the left until the area is illegal;
        while (1) {
            --numbers[author[l]];//slide to right;
            if (numbers[author[l]] == 0) {
                ++l;
                --count;
                break;
            } else {
                ++l;
                if (r - l + 1 < min) {
                    min = r - l + 1;
                    ans_l = l;
                    ans_r = r;
                }
            }

        }
        //now the coverage has failed and we need to move the r;
        while (1) {
            ++r;
            if (r >= n)break;
            if (numbers[author[r]] == 0)count++;
            numbers[author[r]]++;
            if (count == m) {
                if (r - l + 1 < min) {
                    min = r - l + 1;
                    ans_r = r;
                    ans_l = l;
                }
                break;
            }
        }
    }
    cout << ans_l + 1 << " " << ans_r + 1 << endl;
    return 0;
}
