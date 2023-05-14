//
// Created by lu'ren'jia'd's on 2022/3/20.
//

#include <iostream>
#include <cstring>
using namespace std;
int n;

int main() {
    cin >> n;
    long long array[n];
    for (int i = 0; i < n; ++i)cin >> array[i];
    int stack[n + 1], top = 0;
    int answer[n];
    memset(stack,-1,sizeof(stack));
    //when the stack is empty top is 0;
    //to find the number behind me we should search from the rear;
    //to find the element bigger than myself
    // so the stack should be decreasing;
    for (int i = n - 1; i >= 0; --i) {
        while (top && array[stack[top]] < array[i])top--;
        answer[i] = stack[top];
        stack[++top] = i;
    }
    for (int i = 0; i < n; ++i)cout << answer[i] + 1 << " ";
    cout << endl;
    return 0;
}
//单调栈的典型应用，P6510奶牛排队
//用一个单调递减栈（可以要求其中的元素相等）
//找到在自己之前的，比自己更大或者相等的k，左端点肯定是出现在这之后
//再维护一个单调递增的栈，这样站内的元素就可以严格单调增，
//并且同样小的更加靠后出现的会被记录
//在这个单调递增栈内进行二分，找到那个比k大一点点的作为左端点
