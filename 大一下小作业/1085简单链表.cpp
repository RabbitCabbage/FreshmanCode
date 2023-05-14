//
// Created by lu'ren'jia'd's on 2022/2/28.
//

//cstdio, iostream, cmath, cstring
#include <iostream>

using namespace std;
int n, m;
struct node {
    int data;
    node *next;
};

void Print(node *head);

int main() {
    cin >> n >> m;
    node *head = new node(node{0, nullptr});
    node *rear = head;
    for (int i = 0; i < n; ++i) {
        node *ptr = new node;
        cin >> ptr->data;
        rear->next = ptr;
        ptr->next = nullptr;
        rear = ptr;
        //Print(head);
    }
    //Print(head);
    for (int i = 0; i < m; ++i) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int x, y;
            cin >> x >> y;
            node *after_me = head;
            for (int i = 0; i < x; ++i)after_me = after_me->next;
            if (after_me->next == nullptr) {
                after_me->next = new node(node{y, nullptr});
            } else {
                node *add = new node(node{y, after_me->next});
                after_me->next = add;
            }
        } else if (opt == 2) {
            int x;
            cin >> x;
            node *after_me = head;//要删除的是这一个的下一个
            for (int i = 0; i < x - 1; ++i)after_me = after_me->next;
            if (after_me->next->next == nullptr) {
                delete after_me->next;
                after_me->next = nullptr;
            } else {
                node *del = after_me->next;
                after_me->next = del->next;
                delete del;
            }
        }
        //Print(head);
    }
    rear = head;
    while (rear->next != nullptr) {
        node *del = rear;
        rear = rear->next;
        delete del;
        cout << rear->data << " ";
    }
    delete rear;
    cout << endl;
    return 0;
}

void Print(node *head) {
    node *rear = head;
    while (rear->next != nullptr) {
        rear = rear->next;
        cout << rear->data << " ";
    }
    cout << endl;
    cout.flush();
    return;
}