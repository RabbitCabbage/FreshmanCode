//
// Created by lu'ren'jia'd's on 2021/12/1.
//

#ifndef UNTITLED4_QUICK_SORT_AND_SELECT_H
#define UNTITLED4_QUICK_SORT_AND_SELECT_H

void swap(int *one, int *another) {
    int tmp = *one;
    *one = *another;
    *another = tmp;
};

long partition(int *start, int *end, bool cmp(const int &x, const int &y)) {
    int pivot = *start;
    int *low = start, *high = end + 1;
    while (true) {
        while (low + 1 <= end && cmp(*(++low), pivot));
        while (high - 1 >= start && (!cmp(*(--high), pivot)));
        if (low >= high)break;
        else swap(low, high);
    }
    swap(high, start);
    return high - start;
};


void nth_element(int *start, int *find, int *end, bool cmp(const int &x, const int &y)) {
    int *original_start = start;
    end--;
    long to_find = find - start;
    long index;
    while (start < end) {
        long cut_index= partition(start, end, cmp);
        index = start + cut_index- original_start;
        if (index < to_find) {
            start += cut_index + 1;
        } else if (index > to_find) {
            end = start + cut_index - 1;
        } else break;
    }
}

//sort函数可以用nth_element
void sort(int *start, int *end, bool cmp(const int &x, const int &y)) {
    end--;
    if (start >= end)return;
    else {
        long index = partition(start, end, cmp);//这个partition函数就是把数组里面第一个元素放在他应该在的地方，并且返回这个位置的下标索引值
        sort(start, start + index - 1 + 1, cmp);
        sort(start + index + 1, end + 1, cmp);
    }
}

#endif //UNTITLED4_QUICK_SORT_AND_SELECT_H
