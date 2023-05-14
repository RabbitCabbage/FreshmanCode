// "Wrapper": src.hpp
#ifndef Wrapper_CPP_Wrapper_HPP
#define Wrapper_CPP_Wrapper_HPP

#include <string>
//你要接管地址，而不仅仅是复制一个

struct Wrapper {
    void (*before_)();

    void (*after_)();

    void (*function_)(std::string s);//第一个成员是一个函数指针，指向自己

    Wrapper *next= nullptr;
    Wrapper *next_forward= nullptr;
};

Wrapper *head = new Wrapper;//建立链表
Wrapper *rear = head;


Wrapper *create(void(*function_mem)(std::string), void(*before)(), void(*after)()) {
    if(head==nullptr){
        head=new Wrapper;
        rear=head;
    }
    auto pointer = new Wrapper;
    pointer->before_ = before;
    pointer->after_ = after;
    pointer->function_ = function_mem;
    pointer->next_forward = rear;
    rear->next = pointer;
    pointer->next = nullptr;
    rear = pointer;
    return pointer;
}

//  remove()
void remove(Wrapper *&function) {
    if (function->next == nullptr) {
        rear = function->next_forward;
        rear->next = nullptr;
    } else {
        Wrapper *right_before = function->next_forward;
        Wrapper *right_after = function->next;
        right_before->next = right_after;
        right_after->next_forward = right_before;
    }
    delete function;
}

// run()
void run(Wrapper *function, const std::string &s) {
    function->before_();
    function->function_(s);
    function->after_();
}

//destroy()剩下的也要d
void destroy() {
    Wrapper *p = head;
    while (p!= nullptr) {
        Wrapper *delptr = p;
        p = p->next;
        delete delptr;
    }
    head=nullptr;
}
//可能要调用两次destroy，如果一次调用就完全delete整个链表，就会重复delete，因此在非第一次调用的时候要重新建立head
#endif //Wrapper_CPP_Wrapper_HPP