#ifndef FACTORY
#define FACTORY

#include <cstdio>
#include <iostream>

/** You can not use other libraries.*/

static int a_[2000]{0}, b_[2000]{0}, product_[2000]{0}, half_[2000]{0};
static int remain_a = 0, remain_b = 0,break_down=0;


void getItem(int a, int b) {
    static int day = 0;
    a_[day] = a;
    b_[day] = b;
day++;
}

int factory1() {
    static int day = 0;
    int half;
    if (day == 0) half = 0;
    else half = half_[day - 1];
    product_[day] = half;
    day++;
    return half;
}

int factory0() {
    static int day = 0;
    int a = a_[day] + remain_a+break_down;
    int b = b_[day] + remain_b+break_down;//这是今天进货后的总量
    int remain = abs(a - b);
    if (a == b) {
        remain_a = 0;
        remain_b = 0;
        half_[day]=a;
    }
    else {
        int less = (a < b ? a : b);
        half_[day]=less;
        if (a < b) {
            remain_a = 0;
            remain_b = b - less;
        }
        else {
            remain_b = 0;
            remain_a = a - less;
        }
    }
    day++;
    return remain;
}

int factory2() {
    static int day = 0;
    int product;
    if (day == 0)product = 0;
    else {
        product = (int) (product_[day - 1] * 0.95);
        break_down=product_[day-1]-product;
    }

    day++;
    return product;
}

int (*factory[3])() ={factory0, factory1, factory2};

#endif