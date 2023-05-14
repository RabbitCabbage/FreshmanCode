#include <iostream>

int main() {
    using namespace std;
    int array[10];
    int x, m;
    cin >> x >> m;
    for (int i = 0; i < m; i++) {
        int op, num;
        cin >> op >> num;
        switch (op) {
            case 0:
                x = num;
                array[0]=x;
                break;
            case 1:
                x += num;
                array[1]=x;
                break;
            case 2:
                x -= num;
                array[2]=x;
                break;
            case 3:
                x *= num;
                array[3]=x;
                break;
            case 4:
                x /= num;
                array[4]=x;
                break;
            case 5:
                x %= num;
                array[5]=x;
                break;
            case 6:
                num = 0;
                array[6]=x;
                x--;
                break;
            case 7:
                num = 0;
                --x;
                array[7]=x;
                break;
            case 8:
                num = 0;
                array[8]=x;
                x++;
                break;
            case 9:
                num = 0;
                ++x;
                array[9]=x;
                break;


        }

    }
    for(int j=0;j<m;++j) cout<<array[j]<<endl;

    return 0;
}
