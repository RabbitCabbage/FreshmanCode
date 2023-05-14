#include <iostream>

const int maxn = 2e3 + 5;
int height[maxn][maxn];
struct area {
    int ht;
    int wd;
    int pos;//表示的是在这一行中是第几个
};
area stack[maxn];
int n, m;
using namespace std;

long long calc(int x) { return (x * (x + 1) >> 1); }

int main() {
    cin >> n >> m;//n行m列
    for (int j = 1; j <= m; ++j) height[0][j] = 0;
    for (int i = 1; i <= n; ++i) {
        char tmp;
        for (int j = 1; j <= m; ++j) {
            cin >> tmp;
            if (tmp == '#')height[i][j] = 0;
            else height[i][j] = height[i - 1][j] + 1;
        }
    }
    long long total = 0, addition, last_ans;
    for (int i = 1; i <= n; ++i) {
        int top = 0;//每一行处理成一个栈
        addition = 0, last_ans = 0;
        for (int j = 1; j <= m; ++j) {
            stack[++top] = {height[i][j], 1, j};
            //让现在这一列进栈，记下它最多可以往上走的高度，
            // 以及他现在所代表的宽度，还有它的位置
            while (top > 1 && stack[top - 1].ht >= stack[top].ht) {
                //说明这一列前面有一列比自己更高的，
                //那么那个维护的addition就不能这么大了，得截掉一点
                addition -= calc(stack[top - 1].ht) * stack[top - 1].wd;//减去原本的高度
                addition += calc(stack[top].ht) * stack[top - 1].wd;//加上现在高度限制下应该有的高度
                //因为考虑的是前面的这些比自己高的矩形的截掉，所以称乘上的是前面矩形的宽度
                //而且每一次退栈还会往前走，不能一次把所有的都减掉，
                // 如果你这里减掉的是*calc(stack[top-1].wd),那么相当于减一次把前面的都减掉了，会出现多减了的问题
                last_ans -= (calc(stack[top - 1].ht) - calc(stack[top].ht)) *
                            (calc(stack[top - 1].wd) + stack[top - 1].wd * (j - stack[top].pos));
                //这一步是减去刚刚算得的总和被他俩的高度差截掉的那一部分
                //考虑高度的话就是 两个的高度calc相减
                //宽度的话，因为现在的栈顶元素本身也有宽度，作为基础宽度
                //假如这个基础宽度记为c，我们的想把stack[top-1]全部减掉的话，
                //宽度就应当是Σ(c+k),k遍历1到stack[top-1].wd
                //因此宽度乘上的结果是就是calc(stack[top-1].wd)+stack[top-1].wd*c
                //并且这个c应该用到stack里面的结构体来计算，c=j-stack[top].pos
                //stack[top].pos是我们所考虑的栈顶元素，它向前截断高度之后压缩了宽度，他压缩之后的左端点应该到了哪里
                stack[top - 1].ht = stack[top].ht;//都处理完之后，高度截下来
                stack[top - 1].wd += stack[top].wd;//宽度压缩到前面这个元素，top可以退栈
                top--;
            }
            //因为这一列的加入，真正产生的增加，要加上
            addition += calc(height[i][j]);
            last_ans += addition;
            total += last_ans;
        }
    }
    cout << total << endl;
    return 0;
}