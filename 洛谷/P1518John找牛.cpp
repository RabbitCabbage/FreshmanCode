#include<iostream>


using namespace std;

int main() {
//    pair<int, int> north{-1, 0}, east{0, 1}, south{1, 0}, west{0, -1}, step[4];
//    step[0] = north;
//    step[1] = east;
//    step[2] = south;
//    step[3] = west;
    int xx[4] = {-1, 0, 1, 0}, yy[4] = {0, 1, 0, -1};
    int time = 0;
    bool field[10][10];
//    pair<int, int> farmer, cow, farmer_initial, cow_initial, cow_future, farmer_future;
    int farmer_x, farmer_y, cow_x, cow_y, farmer_initial_x, farmer_initial_y, cow_initial_x, cow_initial_y, cow_future_x, cow_future_y, farmer_future_x, farmer_future_y;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            char grid;
            cin >> grid;
            if (grid == '*')field[i][j] = false;
            else if (grid == '.')field[i][j] = true;
            else if (grid == 'C') {
                field[i][j] = true;
                cow_x = i, cow_y = j;
                cow_initial_x = i, cow_initial_y = j;
            } else if (grid == 'F') {
                field[i][j] = true;
                farmer_x = i, farmer_y = j;
                farmer_initial_x = i, farmer_initial_y = j;
            }
        }
    }
    int direction_f = 0, direction_c = 0;
    while (cow_x != farmer_x || cow_y != farmer_y) {
        if (cow_x == cow_initial_x && cow_initial_y == cow_y &&
            farmer_x == farmer_initial_x && farmer_initial_y == farmer_y && time > 0 &&
            direction_c == 0 && direction_f == 0) {
            time = 0;
            break;
        }
        time++;//一分钟过去了，下面让他们各自运动
        cow_future_x = cow_x + xx[direction_c];
        cow_future_y = cow_y + yy[direction_c];
        if (field[cow_future_x][cow_future_y] &&
            cow_future_x >= 0 && cow_future_x <= 9 &&
            cow_future_y >= 0 && cow_future_y <= 9) {
            cow_x = cow_future_x;
            cow_y = cow_future_y;
//            cout << "cow" << cow_x << " " << cow_y << endl;
        } else {
            ++direction_c %= 4;
//            cout<<"cow change direction: "<<direction_c<<endl;
        }
        farmer_future_x = farmer_x + xx[direction_f];
        farmer_future_y = farmer_y + yy[direction_f];
        if (field[farmer_future_x][farmer_future_y] &&
            farmer_future_x >= 0 && farmer_future_x <= 9 &&
            farmer_future_y >= 0 && farmer_future_y <= 9) {
            farmer_x = farmer_future_x;
            farmer_y = farmer_future_y;
//            cout << "farmer" << farmer_x << " " << farmer_y << endl;
        } else {
            ++direction_f %= 4;
//            cout<<"farmer change direction: "<<direction_f<<endl;
        }
    }
    cout << time << endl;
    return 0;
}
//题解启发：死循环不仅仅是农夫、奶牛同时回到了原处发点，而且方向也是原来的向北！！！！