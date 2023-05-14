//
// Created by lu'ren'jia'd's on 2021/11/19.
//

#ifndef UNTITLED6_SHARE_PTR_H
#define UNTITLED6_SHARE_PTR_H

#include <map>

class shared_ptr {
    std::map<int *, int> counter_map;
    int *pointer=nullptr;
    int counter=0;
public:
    shared_ptr() : pointer(nullptr), counter(0) {};

    shared_ptr(const shared_ptr &q);

    shared_ptr(int *q);

    int &operator*() const;
    //重载*符号，返回一个int指针,然后解引用时候救出int,应该引用返回，因为可能要写入

    shared_ptr &operator=(shared_ptr &q);

    void reset();

    void reset(int *q);

    ~shared_ptr();
};

shared_ptr::shared_ptr(const shared_ptr &q) {//构造。由一个智能指针构造
    if (pointer != q.pointer) {
        pointer = q.pointer;
        counter = 1 + q.counter;
        counter_map[pointer] = counter;
    }
}

shared_ptr::shared_ptr(int *q) {//构造，由一个普通指针构造
    if (pointer != q) {
        pointer = q;
        if (counter_map.count(q))counter = counter_map[q] + 1;
        else counter = 1;
        counter_map[q] = counter;
    }
}


int &shared_ptr::operator*() const {
    return *pointer;
}

shared_ptr &shared_ptr::operator=(shared_ptr &q) {
    if (pointer != q.pointer) {
        if(counter==1){
            int* del =pointer;
            delete del;
            counter_map[pointer];
        }else{
            counter_map[pointer]--;
        }
        pointer = q.pointer;
        counter = ++q.counter;
        counter_map[pointer] = counter;
    }
    return (*this);
}

void shared_ptr::reset() {
    if (pointer != nullptr) {
        counter = counter_map[pointer];
        if (counter == 1) {
            counter_map.erase(pointer);
            int *del = pointer;
            delete del;
            pointer = nullptr;
            counter = 0;
        } else {
            counter_map[pointer]--;
            pointer = nullptr;
            counter = 0;
            //其他指针的counter是要减一的
        }
    }
}

void shared_ptr::reset(int *q) {
    if (pointer != q) {
        if (counter_map.count(q)) {
            counter = counter_map[pointer];
            if (counter == 1) {
                counter_map.erase(pointer);
                int *del = pointer;
                delete del;
                pointer = q;
                counter = ++counter_map[q];
            } else {
                counter_map[pointer]--;
                pointer = q;
                counter = ++counter_map[q];
                //其他指针的counter是要减一的
            }
        } else {
            counter = counter_map[pointer];
            if (counter == 1) {
                counter_map.erase(pointer);
                int *del = pointer;
                delete del;
                pointer = q;
                counter = 1;
                counter_map[q] = 1;
            } else {
                counter_map[pointer]--;
                pointer = q;
                counter = 1;
                counter_map[q] = 1;
                //其他指针的counter是要减一的
            }
        }
    }
}

shared_ptr::~shared_ptr() {
    //一个地址可能有多个指针指向，就会多次释放内存。要在map里面确认一下，总是让最后一个析构的指针负责delete
    if(pointer!=nullptr){
        if(counter_map[pointer]==1)delete pointer;
        else counter_map[pointer]--;
    }
}

#endif //UNTITLED6_SHARE_PTR_H
