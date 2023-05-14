//遇到不连续的结成一组，遇到相同的结成一组，尽量让每一组都达到最长 (X)
//这会有个问题就是，如果有1 1 1 2 2 2 3 3 3，明明可以分到一组，但是被分到了了很多个里面 (X)
//不妨令每一次画线都从最左边一列开始。
//每次都画到底，可以吗？
//显然，大多数情况下这不是最优解。最后可能会剩下一个方块“一枝独秀”：(V)!!!!
//如果右边一列的高度**不低于**当前列，则连接右边一列最下方的方块。反之，停止画线。
//这样，最靠左的一个“峰”相较其右边一列的高度差就不断减小，直到相同。如此反复。记录所画所有线的最短长度，即为答案。
//高度降为 0 后直接删除，便于计算。
#include <iostream>
#include <map>

using namespace std;
int n;
map<long long, int> tongji;

int main() {
    cin >> n;
    long long array[n];
    int min = n, every_length = 1;
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
        if (tongji.count(array[i]))++tongji[array[i]];
        else tongji[array[i]] = 1;
    }
    //统计一下各自有多少个，然后再按刚才的思路，尽可能大的截出每一组
    map<long long, int>::iterator next;
    while (1) {
        auto ptr = tongji.begin();
        while (ptr->second == 0 && ptr != tongji.end())++ptr;
        if (ptr == tongji.end())break;

        for (; ptr != tongji.end();) {
            --(ptr->second);

            next = ++ptr;
            --ptr;
            if (next != tongji.end())while (next->second == 0 && next != tongji.end())next++;
            if (next == tongji.end()) {
                if (every_length < min)min = every_length;
                every_length = 1;
                break;
            }

            if (ptr->first == (next->first) - 1 && ptr->second + 1 <= next->second) {//如果后面的太低，就会导致你自己这列的剩到最后
                every_length++;
//                --(next->second);
                ptr = next;
            } else {
                if (every_length < min)min = every_length;
                every_length = 1;
                //ptr = next;这里是错的，不能接着画了，因为按照这个始终往高处画线的想法，可能要回去，因此这里break掉
                break;
            }
        }
    }
    cout << min << endl;
    return 0;
}