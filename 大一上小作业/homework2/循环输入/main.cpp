#include <iostream>
//主教好，我可能需要声明一下，我的这个程序有蒋来小姐姐的帮助，和韦中敬学长的指点
//并且它在我的本地跑到时候无法自动结束，
using namespace std;
int length;
int classify;

int main() {
    cin >> length;
    int array[length];
    for (int j = 0; j < length; ++j) {
        cin >> array[j];
    }
    while (cin >> classify) {
        int x, y, k;
        if (classify == 1) {
            cin >> x;
            cout << array[x] << endl;
        } else if (classify == 2) {
            cin >> k;
            for (; k >= 1; --k) {
                getchar();
                cin >> x >> y;
                array[x] = y;
            }

        } else if (classify == 3) {
            while (1) {
                int x, y;
                cin >> x >> y;
                array[x] = y;

                if (getchar() == '\n') break;

            }
        }
    }


    return 0;
}
