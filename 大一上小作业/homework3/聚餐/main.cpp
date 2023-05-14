#include <iostream>
#include<cmath>
#include<sstream>
#include<string>

using namespace std;
int n, m, t;

int transfer(bool array[], int length);

int main() {
    cin >> t;
    for (int h = 0; h < t; h++) {
        cin >> n >> m;
         getchar();
        int like_[m], dislike_[m];//存放压缩后的int
        for (int k = 0; k < m; ++k) {
            bool like[n], dislike[n];
            for (int j = 0; j < n; j++) {
                like[j] = false;
                dislike[j] = false;
            }
            stringstream ss;
            string s;
            getline(cin,s);
            ss << s;
            int a;
            while (ss >> a) {
                if (a > 0) like[abs(a) - 1] = true;
                else if (a < 0) dislike[abs(a) - 1] = true;
            }
            like_[k] = transfer(like, n);
            dislike_[k] = transfer(dislike, n);
        }

        int satisfied = 0, counter;
        for (int i = 0; i < pow(2, n) ; ++i) {
            counter = 0;
            for (int w = 0; w < m; ++w) {
                if (((i & like_[w]) !=0) ||((~i & dislike_[w]) != 0))++counter;
                else break;
            }
            if (counter == m){
                satisfied++;
                break;
            }
        }
        if (satisfied > 0) cout << "Bingo!" << endl;
        else cout << "Sigh..." << endl;
    }
    return 0;
}

int transfer(bool array[], int length) {
    int result = 0;
    for (int i = 0; i < length; ++i) {
        result = result | (array[length - 1 - i] << i);
    }
    return result;
}