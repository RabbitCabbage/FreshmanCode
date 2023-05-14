//你都写递归函数了，那肯定是一个分支跑完才能跑下一个分支
//一直把广搜写成深搜，怕不是有什么大病，记着只要是有可能的结果就得做完!!!!!!做完!!!!!!!!!!!!才能到下一层!!!!!!!!!!!!!!
#include <iostream>

using namespace std;
int n, a, b;

//楼层是1base，所以从数组里面取数要-1
int result(int current, int *k, bool *vis) {
    static int count = 0;
    int up = current + k[current - 1], down = current - k[current - 1];
    ++count;
    if (up == b || down == b)return count;
    else if (up >= 1 && up <= n && up != a && !vis[up - 1]) {
        vis[up - 1] = true;
        result(up, k, vis);//同样的错误，不是广度搜索，这里其实又是把一个分支走到底的深度搜索！！！！！！！！！！
    } else if (down >= 1 && down <= n && down != a && !vis[down - 1]) {
        vis[down - 1] = true;
        result(down, k, vis);
    } else return -1;
}

int main() {
    cin >> n >> a >> b;
    if (a == b) {
        cout << 0 << endl;
        return 0;
    }
    int k[n];
    bool vis[n];
    for (int i = 0; i < n; ++i) {
        cin >> k[i];
        vis[i] = false;
    }
    vis[a - 1] = true;
    cout << result(a, k, vis) << endl;
    return 0;
}


#include <iostream>
#include <queue>

using namespace std;
int n, a, b;

//limit exceeded主要原因就是你这个判断方法太慢，你是说回到原来出发的地方，其实只要这个楼层之前到过，就已经说明问题了
int main() {
    cin >> n >> a >> b;
    if (a == b) {
        cout << 0 << endl;
        return 0;
    }
    int k[n];
    bool vis[n];
    for (int i = 0; i < n; ++i) {
        cin >> k[i];
        vis[i] = false;
    }
    queue<pair<int, int>> q;
    q.push({a, 0});
    int count = 0;
    vis[a - 1] = true;//别忘了初始化！！
    while (!q.empty()) {
        int current = q.front().first;
        count = q.front().second;//到达这一层已经按了多少下键
        q.pop();
        int up = current + k[current - 1], down = current - k[current - 1];
        ++count;
        if (up == b || down == b)break;
//        else if (up >= 1 && up <= n && !vis[up - 1]) {
//            q.push({up, count});
//            vis[up - 1] = true;
//        } else if (down >= 1 && down <= n && !vis[down - 1]) {
//            q.push({down, count});
//            vis[down - 1] = true;
//错了！！！！！！！！！！！！，不是else的关系啊！！！！！！，up要进队列，down也要进队列！！！！！！！！！，这样才是广搜啊！！！！！！！！！！！
        if (up >= 1 && up <= n && !vis[up - 1]) {
            q.push({up, count});
            vis[up - 1] = true;
        }
        if (down >= 1 && down <= n && !vis[down - 1]) {
            q.push({down, count});
            vis[down - 1] = true;
        }
        count = -1;//没有找到答案而退出循环就是-1
    }
    cout << count << endl;
    return 0;
}