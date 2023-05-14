//
// Created by lu'ren'jia'd's on 2021/12/1.
//

#include <iostream>
#include "quick_sort_and_select.h"

int a[9] = {1, 5, 6, 2, 7, 3, 9, 4, 8};

bool cmp(const int &x, const int &y){return x > y;}

int main()
{
    nth_element(a, a + 8, a + 9, cmp);//find the 8th(0-base) greatest value in a with cmp as comparator
    std::cout << *(a + 5) << std::endl;// 4
    sort(a, a + 9, [](const int &x, const int &y){return x < y;});//comp is a lambda expression, which returns true if and only if x < y
    for (int i = 0;i < 9;++ i) std::cout << a[i] << " ";// 1 2 3 4 5 6 7 8 9
    std::cout << std::endl;
    return 0;
}