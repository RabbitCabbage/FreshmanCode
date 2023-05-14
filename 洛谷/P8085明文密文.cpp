//
// Created by lu'ren'jia'd's on 2022/3/6.
//

#include <iostream>
#include <map>
#include <string>

using namespace std;

//感觉这个题目主要难点在于将字符串单元进行转化
//思路打开之后发现这个转化可以转成
int code[1000009];
int decode[1000009];
int code_former_appear[1000009];
int decode_former_appear[1000009];
int len_decode, len_code;
map<string, int> used;
map<int, int> code_former_loc, decode_former_loc;
const int inf = -19260817;

int main() {
    string tmp;
    for (;; ++len_decode) {
        cin >> tmp;
        if (tmp == "$")break;
        else {
//            cout<<"处理第"<<len_decode<<"个数"<<endl;
            if (used.find(tmp) != used.end()) {
                decode[len_decode] = used[tmp];//转在了int数组里，
//                cout<<"这个数是"<<decode[len_decode]<<endl;
//                cout<<decode[len_decode]<<"这个数这次是在"<<len_decode<<"位置出现"<<endl;
//                cout<<"上一次在"<<decode_former_loc[decode[len_decode]]<<"出现"<<endl;
                decode_former_appear[len_decode] = decode_former_loc[decode[len_decode]];
                decode_former_loc[decode[len_decode]] = len_decode;
            } else {
                used[tmp] = used.size() + 1;
                decode[len_decode] = used.size();
//                cout<<"这个数是"<<decode[len_decode]<<endl;
                decode_former_loc[decode[len_decode]] = len_decode;//记住现在所出现的位置
//                cout<<decode[len_decode]<<"这个数这次是在"<<len_decode<<"位置出现"<<endl;
//                cout<<"上一次在"<<inf<<"出现"<<endl;
                decode_former_appear[len_decode] = inf;//预处理它的前一个出现的位置

            }
        }
    }
    used.clear();
    for (;; ++len_code) {
        cin >> tmp;
        if (tmp == "$")break;
        else {
            if (used.find(tmp) != used.end()) {
                code[len_code] = used[tmp];//转在了int数组里，

                code_former_appear[len_code] = code_former_loc[code[len_code]];
                code_former_loc[code[len_code]] = len_code;
            } else {
                used[tmp] = used.size() + 1;
                code[len_code] = used.size();

                code_former_loc[code[len_code]] = len_code;//记住现在所出现的位置
                code_former_appear[len_code] = inf;//预处理它的前一个出现的位置

            }
        }
    }
    decode_former_loc.clear();
    code_former_loc.clear();
    //经过预处理，现在code、decode数组里面存的是去重之后的数字代表字符单元
    // 而在appearrance里面存的是这个字符之前出现是在哪里，没出现过的记成了INF。
    //所以现在appear[i]代表的是之前这个字符在哪里出现过了

//    for (int i = 0; i < len_decode; ++i)cout << decode_former_appear[i] << " ";
//    cout << endl;
//    for (int i = 0; i < len_decode; ++i)cout << decode[i] << " ";
//    cout << endl;
//    for (int i = 0; i < len_code; ++i)cout << code_former_appear[i] << " ";
//    cout << endl;
//    for (int i = 0; i < len_code; ++i)cout << code[i] << " ";
//    cout << endl;

    int next[len_code + 1];
    int j = 0, k = -1;
    next[j] = k;
    while (j < len_code) {
        int distance_k, distance_j;
        if (code_former_appear[k] == inf)distance_k = inf;
        else distance_k = k - code_former_appear[k];
        if (code_former_appear[j] == inf)distance_j = inf;
        else distance_j = j - code_former_appear[j];
        if (k == -1 || distance_j == distance_k) {
            ++j, ++k;
            next[j] = k;
        } else k = next[k];
    }
//    for (int i = 0; i < len_code; ++i)cout << next[i] << " ";
//    cout << endl;

    j = 0;
    k = 0;
    while (j < len_decode && k < len_code) {
        //实时判断前一个位置是不是超出了比较范围
        int range = j - k;//if less than range, that is out of the comparing range
        if (k == -1) {
            ++j, ++k;
            continue;
        }
        int last_decode_appear, last_code_appear = code_former_appear[k];//明文的是否出现的范围要时时更新
        if (decode_former_appear[j] < range)last_decode_appear = inf;
        else last_decode_appear = decode_former_appear[j];
        int distance_k, distance_j;
        if (last_code_appear == inf)distance_k = inf;
        else distance_k = k - last_code_appear;
        if (last_decode_appear == inf)distance_j = inf;
        else distance_j = j - last_decode_appear;
        if (distance_k == distance_j)++j, ++k;
        else k = next[k];
    }
    cout << j - k +1<< endl;
    return 0;
}
