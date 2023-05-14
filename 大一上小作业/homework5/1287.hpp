//
// Created by lu'ren'jia'd's on 2021/11/17.
//

#ifndef UNTITLED6_1287_HPP
#define UNTITLED6_1287_HPP


class BigIndexArray {
public :
    struct num {
        long long index;
        long long value;
        num *next = nullptr;
    };
    num *head = new num;
    num *rear = head;

    ~BigIndexArray();

    long long &operator[](long long index);
};

long long &BigIndexArray::operator[](long long index) {
    num *ptr = head->next;
    while (ptr != nullptr) {
        if (ptr->index == index)break;
        else ptr = ptr->next;
    }
    if (ptr != nullptr) return ptr->value;
    else {
        ptr = new num;
        ptr->index = index;
        rear->next = ptr;
        rear = (num *&) ptr;//new idea
        return ptr->value;
    }
}

BigIndexArray::~BigIndexArray() {
    num *&ptr = head;
    while (ptr != nullptr) {
        num *&delptr = ptr;
        ptr = (num *&) ptr->next;//new idea
        delete delptr;
    }
}


#endif //UNTITLED6_1287_HPP
