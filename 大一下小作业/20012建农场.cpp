//
// Created by lu'ren'jia'd's on 2022/3/19.
//
#include <iostream>
#include <cstring>

using namespace std;
int n;

//void print_stack(int top, int *stack, char name[]) {
//    cout << name << ": ";
//    for (int i = 1; i <= top; ++i)cout << stack[i] << " ";
//    cout << endl;
//}

int main() {
    cin >> n;
    int height[n];
    for (int i = 0; i < n; ++i)cin >> height[i];
    int top = 0, stack[n + 1];//in the beginning the stack is empty;
    int top_less = 0, stack_less[n + 1];
    memset(stack, 0, sizeof(stack));
    //we need to find the first element that appears before i
    // and is bigger than i or equal to i ;
    // so we need a stack that is decreasing
    // so the bigger or equal is throw out of stack
    int NoLessThan[n], Less[n], max_length = 0;
    for (int i = 0; i < n; ++i) {
        while (top && height[stack[top]] < height[i])--top;
        while (top_less && height[stack_less[top_less]] >= height[i])--top_less;
        if (top != 0)NoLessThan[i] = stack[top];
        else NoLessThan[i] = -1;
        if (top_less != 0)Less[i] = stack_less[top_less];
        else Less[i] = -1;
        stack_less[++top_less] = i;
        stack[++top] = i;
//        print_stack(top, stack, "decreasing_stack");
//        print_stack(top_less, stack_less, "increasing_stack");

        //the first element no less than me and appears before me;
        int the_first_nlt_index = NoLessThan[i];
//        cout << "the_first_nlt_index: " << NoLessThan[i] << endl;
        //find the index that is bigger than this in the increasing stack
        // in the increasing stack the repeated ones have been eliminated
        int left = 1, right = top_less;
        while (left < right) {
            int middle = (left + right) / 2;
            if (stack_less[middle] == the_first_nlt_index + 1)break;//middle is the answer;
            else if (stack_less[middle] < the_first_nlt_index + 1)left = middle + 1;
            else right = middle;
        }
        if (stack_less[(left + right) / 2] >= the_first_nlt_index + 1 && i - stack_less[(left + right) / 2] + 1 > max_length)
            max_length = i - stack_less[(left + right) / 2] + 1;
//        cout << "max_length: " << max_length << endl;
    }
    cout << max_length << endl;
    return 0;
}


