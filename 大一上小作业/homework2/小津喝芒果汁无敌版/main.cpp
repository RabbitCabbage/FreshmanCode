#include <iostream>

int beishu = 0;
using namespace std;

int main() {
    cin>>beishu;
    int mongo[beishu];
    for (int i = 0; i < beishu; ++i) {
        cin >> mongo[i];
    }
    int max = 0;
    for (int j = 0; j < beishu; ++j) {
        if (mongo[j] >= max) max = mongo[j];
    }
    cout << max;
    return 0;
}
