//
// Created by lu'ren'jia'd's on 2021/12/3.
//

#include <bits/stdc++.h>

struct node {
    int value;
    node *next;
};

class LinkList {
private:
    node *head, *rear;
public:
    LinkList() {
        head = new node;
        rear = head;
        head->next = nullptr;
    }

    ~LinkList() {
        node *ptr = head->next;
        delete head;
        while (ptr != nullptr) {
            node *del = ptr;
            ptr = ptr->next;
            delete del;
        }
    }

    void push(int x);

    int getKth(int k);

    void merge(LinkList *l);
};

void LinkList::push(int x) {
    if (head->next == nullptr) {
        node *tmp = new node;
        tmp->value = x;
        head->next = tmp;
        tmp->next = nullptr;
        rear = tmp;
    } else {
        node *ptr = head;
        while (ptr->next != nullptr) {
            if (ptr->next->value >= x)break;
            else ptr = ptr->next;
        }
        node *tmp = new node;
        tmp->value = x;
        if (ptr->next == nullptr) {
            //append
            rear->next = tmp;
            rear = tmp;
            tmp->next = nullptr;
        } else {
            tmp->next = ptr->next;
            ptr->next = tmp;
        }
    }
}

int LinkList::getKth(int k) {
    int counter = 0, kth;
    node *ptr = head->next;
    while (ptr != nullptr) {
        if (counter == k) {
            kth = ptr->value;
            break;
        } else {
            ptr = ptr->next;
            counter++;
        }
    }
    if (ptr == nullptr)return -1;
    else return kth;
}

void LinkList::merge(LinkList *l) {
    node *l_first = l->head->next;
    node *first = head->next;
    if (l_first == nullptr) return;
    else if (first == nullptr) {
        head->next = l->head->next;
        rear = l->rear;
        l->rear = l->head;
        l->head->next = nullptr;
    } else {
        //用本链表的一次遍历，实现另一个链表所有元素插入
        node *ptr = head;
        node *pickout = l->head->next;
        while (ptr->next != nullptr && pickout != nullptr) {
            while (pickout != nullptr && ptr->next->value >= pickout->value) {
                //插入ptr  ptr->next之间
                node *picknext = pickout->next;
                pickout->next = ptr->next;
                ptr->next = pickout;
                pickout = picknext;
            }
            ptr = ptr->next;
        }
        if (pickout == nullptr) {
            l->head->next = nullptr;
            return;
        } else {
            rear->next = pickout;
            rear = l->rear;
            l->head->next = nullptr;

        }
    }
}

class LinkListArray {
private:
    int len;
    LinkList **lists;

public:
    LinkListArray(int n) : len(n) {
        lists = new LinkList *[n];
        for (int i = 0; i < n; ++i) lists[i] = new LinkList;
    }

    ~LinkListArray() {
        for (int i = 0; i < len; ++i) {
            delete lists[i];
        }
        delete[]lists;
    }

    void insertNumber(int n, int x) {
        lists[n]->push(x);
    }

    int queryNumber(int n, int k) {
        return lists[n]->getKth(k);
    }

    void mergeLists(int p, int q) {//把q连接到p后面，并且把q清空
        lists[p]->merge(lists[q]);
    }
};

int main() {
    int len, m;
    scanf("%d%d", &len, &m);
    LinkListArray a = LinkListArray(len);
    for (int i = 0, op, s1, s2; i < m; ++i) {
        scanf("%d%d%d", &op, &s1, &s2);
        if (op == 0) {
            a.insertNumber(s1, s2);
        }
        if (op == 1) {
            printf("%d\n", a.queryNumber(s1, s2));
        }
        if (op == 2) {
            a.mergeLists(s1, s2);
        }
    }
    return 0;
}