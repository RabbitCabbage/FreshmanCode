#include <iostream>
#include <string>

using namespace std;
int m, n;//m台机器，n个工件
int main() {
    int time = 0;
    cin >> m >> n;
    bool occupied[m][100000];//第m台机器在某某时间是否有事
    for (int i = 0; i < m; ++i)occupied[i][0] = false;
    int last_time[n], doing[n];//每个工件上一步做完是什么时候,正在处理第几步
    for (int i = 0; i < n; ++i)last_time[i] = 0, doing[i] = -1;
    int sequence[m * n];
    for (int i = 0; i < n * m; ++i) {
        cin >> sequence[i];
        sequence[i]--;
    }
    int machine[n][m], cost[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j){
            cin >> machine[i][j];
            machine[i][j]--;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)cin >> cost[i][j];
    }
    //每一个工件的每一个工序都要从上一次做完之后尽可能早的进入处理
    int ware_now;//现在考虑处理的工件
    for (int i = 0; i < m * n; ++i) {
        ware_now = sequence[i];
        doing[ware_now]++;
        //考虑从正在处理工件的最后时间，看是否有机器可以处理，考虑正在处理步骤
        while (true) {
            int k;
            for (k = 0; k < cost[ware_now][doing[ware_now]]; ++k, ++last_time[ware_now]) {
                if (occupied[machine[ware_now][doing[ware_now]]][last_time[ware_now]]) {
                    while (occupied[machine[ware_now][doing[ware_now]]][last_time[ware_now]])last_time[ware_now]++;
                    break;//跳到下一个可能的时间段再来找一次
                }
            }
            if (k == cost[ware_now][doing[ware_now]]) {
                for (int q = 1; q <= cost[ware_now][doing[ware_now]]; ++q)
                    occupied[machine[ware_now][doing[ware_now]]][last_time[ware_now] - q] = true;
                if (last_time[ware_now] > time)time = last_time[ware_now];
                break;//一直找到这样的一段时间再停止,并且此时lasttime已经更新了//todo
            }
        }
    }
    cout << time << endl;
    return 0;
}