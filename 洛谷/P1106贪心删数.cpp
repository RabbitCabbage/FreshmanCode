//要想使得剩下的最小，把较小的数尽可能的往高位留
#include <iostream>

using namespace std;

int main() {
    int number[255];
    char bit;
    int i = 0, k;
    cin.get(bit);
    while (bit != ' ' && bit != '\n') {
        number[i] = bit - '0';
        ++i;
        cin.get(bit);
    }//此时有i位数
    cin >> k;//删去k位
    int rest = i - k, count = 0;
    int the_min_index = 0, the_min_bit = number[0], last_min_index = -1;
    bool flag = false;
    while (count<rest) {
        for (int j = the_min_index, q = 0; q <= k; ++q, ++j) {
            if (number[j] < the_min_bit) {
                the_min_bit = number[j];
                the_min_index = j;
            }
        }//找到了最小的首位
        //下面就是把前面the_min_index之前的全删掉就好了
        k -= the_min_index - last_min_index - 1;//以后还能删这么多个
        if (number[the_min_index])flag = true;
        if (flag)cout << number[the_min_index];
        count++;
        last_min_index = the_min_index;
        the_min_index++;//下一位数从这个开始找起
        the_min_bit = number[the_min_index];
    }
    //一边找一边输出，看看是不是输出出了问题
    if (!flag)cout << "0";
//    cout << endl;
    return 0;
}