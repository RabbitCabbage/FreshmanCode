//
// Created by lu'ren'jia'd's on 2021/11/15.
//

#include <iostream>
#include <vector>
#include <algorithm>

const long long MOD = 1e9 + 7;
using namespace std;
int n, m;
long long array_[30][30];
struct matrix {
    int rank = 0;
    int code = 0;
};

int standard_process(long long array[][30]);

vector<matrix> MV;

bool operator==(const matrix &lhs, const matrix &rhs) {
    if (lhs.rank == rhs.rank) return true;
    else return false;
}

//bool compare_rank(const matrix &lhs, const matrix &rhs) {
//    if (lhs.rank < rhs.rank)return true;
//    else return false;
//}
//
//bool compare_code(const matrix &lhs, const matrix &rhs) {
//    if (lhs.code < rhs.code)return true;
//    else return false;
//}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        matrix m1;
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; ++k) {
                long long d;
                cin >> d;
                array_[j][k] = d;
//                if (d < 0)array_[j][k] = (array_[j][k] % MOD + MOD) % MOD;
//                else
//                array_[j][k] = d % MOD;
            }
        }
        m1.code = i + 1;
        //对矩阵做行列变换化为标准型，以判断是否等价
        m1.rank = standard_process(array_);
        MV.push_back(m1);
    }//把矩阵放到vector里面了，已经是标准型
//    sort(MV.begin(), MV.end(), compare_rank);
    auto ptr = unique(MV.begin(), MV.end());
    //   sort(MV.begin(), ptr, compare_code);
    vector<matrix>::iterator pointer;
    int counter = 0;
    for (pointer = MV.begin(); pointer != ptr; pointer++) {
        counter++;
    }
    cout << counter << endl;
    for (pointer = MV.begin(); pointer != ptr; pointer++) {
        cout << pointer->code << " ";
    }
    cout << endl;
    return 0;
}

void swap_row(int i, int j, long long array[][30]) {
    for (int k = 0; k < m; ++k) {
        long long temp = array[i][k];
        array[i][k] = array[j][k];
        array[j][k] = temp;
    }
}

int standard_process(long long array[][30]) {
    int rank = 0;
    for (int i = 0; i < m - 1; ++i) {
        int j = i;
        for (; j < m; ++j) {//如果全部一列0
            if (array[j][i] != 0) {
                if (j != i)swap_row(j, i, array);
                break;
            }
        }
        if (j < m) {
            //用第i行去消元
            for (int k = i + 1; k < m; ++k) {
                long long before = array[k][i];
                for (int h = i; h < m; ++h) {
                    if (h == i)array[k][h] = 0;
                    else {
                        array[k][h] = array[k][h] * array[i][i] - array[i][h] * before;
//                        if (array[k][h] < 0)array[k][h] = ((array[k][h] % MOD) + MOD) % MOD;
//                        else
                        array[k][h] %= MOD;
                    }

                }
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            if (array[i][j]) {
                rank++;
                break;
            }
        }
    }
    cout << "RANK: " << rank << endl;
    return rank;
}