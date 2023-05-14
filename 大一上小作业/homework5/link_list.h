

template<typename ValueType>
class MyList {
    struct link_node {
        link_node *before = nullptr;
        link_node *after = nullptr;
        ValueType value;
    };
    link_node *head;
    link_node *rear;
    int size_ = 0;
public:

    MyList() {
        //主要是产生一个空链表，便于后续插入
        head = new link_node;
        rear = head;
        //此时均为最初始状态，记得初始化
    }

    MyList(MyList &&obj) noexcept//右值引用，可以对它赋值
    {
        if (obj.head == obj.rear) {
            head = new link_node;
            rear = head;
        } else {
            head = new link_node;
            rear = obj.rear;
            size_ = obj.size_;
            head->after = obj.head->after;//找到第一个
            (head->after)->before = head;
            obj.head->after = nullptr;
            obj.rear = obj.head;
        }
    }

    MyList(const MyList &obj) {
        head = new link_node;
        rear = head;
        size_ = obj.size_;
        link_node *ptr = obj.head->after;//找到第一个
        while (ptr != nullptr) {
            link_node *right_before = rear;//记录下来上一个
            rear = new link_node;//正在创建的
            rear->value = ptr->value;
            rear->before = right_before;
            rear->after = nullptr;
            right_before->after = rear;
            ptr = ptr->after;
        }
    }

    ~MyList() {
        link_node *p = head;
        while (p != nullptr) {
            link_node *now_delptr = p;
            p = p->after;
            delete now_delptr;
        }
    }

    void push_back(const ValueType &value) {
        size_++;
        auto *temp = new link_node;
        temp->before = rear;
        temp->after = nullptr;
        rear->after = temp;
        temp->value = value;
        rear = temp;//记得每次都把rear确实是指在最后面的
    }

    void pop_back() {
        size_--;
        link_node *delptr = rear;
        rear = rear->before;
        rear->after = nullptr;
        delete delptr;
    }

    void push_front(const ValueType &value) {
        size_++;
        if (size_ - 1 == 0) {
            auto *temp = new link_node;
            temp->value = value;
            temp->before = head;
            head->after = temp;
            rear = temp;
        } else {
            auto *temp = new link_node;
            temp->value = value;
            auto first = head->after;
            temp->after = first;
            temp->before = head;
            first->before = temp;
            head->after = temp;
        }
    }

    void pop_front() {
        size_--;
        if (size_ == 0) {
            link_node *first = head->after;
            head->after = nullptr;
            rear = head;
            delete first;
        } else {
            link_node *first = head->after;
            link_node *second = first->after;
            head->after = second;
            second->before = head;
            delete first;
        }
    }

    ValueType &front() const {
        return (head->after)->value;
    }

    ValueType &back() const {
        return rear->value;
    }

    void insert(int index, const ValueType &value) {//新建的节点成为第index的，index是零base
        if (size_ == 0) {
            size_++;
            auto *temp = new link_node;
            head->after = temp;
            temp->before = head;
            temp->value=value;
            temp->after = nullptr;
            rear = temp;
        } else {
            size_++;
            if (index == size_ - 1) {
                auto *temp = new link_node;
                temp->value = value;
                temp->after = nullptr;
                temp->before = rear;
                rear->after = temp;
                rear = temp;
            } else {
                link_node *ptr = head->after;
                int code = 0;
                while (code != index) {
                    code++;
                    ptr = ptr->after;
                }
                //退出循环时的ptr刚刚好指向要被替代的那个
                auto *temp = new link_node;
                temp->value = value;
                link_node *right_before = ptr->before;
                right_before->after = temp;
                temp->before = right_before;
                temp->after = ptr;
                ptr->before = temp;
            }
        }
    }

    void erase(int index) {
        size_--;
        if (size_ == 0) {
            link_node *ptr = head->after;
            head->after = nullptr;
            rear = head;
            delete ptr;
        } else {

            link_node *ptr = head->after;
            int code = 0;
            while (code != index) {
                ptr = ptr->after;
                code++;
            }
            //退出循环时的ptr刚刚好指向要erase的那个
            if (ptr == rear) {
                rear = ptr->before;
                rear->after=nullptr;
            } else {
                link_node *right_after = ptr->after;
                link_node *right_before = ptr->before;
                right_before->after = right_after;
                right_after->before = right_before;
            }
            delete ptr;
        }
    }

    int size() const {
        return size_;
    }

    bool empty() const {
        if (rear == head)return true;
        else return false;
    }

    void clear() {
        link_node *p = head->after;
        while (p != nullptr) {
            link_node *now_delptr = p;
            p = p->after;
            delete now_delptr;
        }
        head->after = nullptr;
        rear = head;
        size_ = 0;
    }

    void link(const MyList &obj) {
        if (obj.size_ == 0) {}
        else if (head == obj.head) {
            size_ *= 2;
            link_node *ptr = head->after;
            auto *copy_head = new link_node;
            link_node *copy_rear = copy_head;
            while (ptr != nullptr) {
                link_node *right_before = copy_rear;
                copy_rear = new link_node;
                copy_rear->value = ptr->value;
                copy_rear->after = nullptr;
                copy_rear->before = right_before;
                right_before->after = copy_rear;
                ptr = ptr->after;
            }
            rear->after = copy_head->after;
            (copy_head->after)->before = rear;
            rear = copy_rear;
            delete copy_head;
        } else {
            link_node *ptr = obj.head->after;//找到第一个
            while (ptr != nullptr) {
                link_node *right_before = rear;//记录下来上一个
                rear = new link_node;//正在创建的
                rear->value = ptr->value;
                rear->before = right_before;
                rear->after = nullptr;
                right_before->after = rear;
                ptr = ptr->after;
            }
            size_ += obj.size_;
        }
    }

    MyList cut(int index) {
        if (index >= size_) {
            MyList latter;
            return latter;

        } else if (index == 0) {
            MyList latter;
            latter.head->after = head->after;
            (head->after)->before = latter.head;
            latter.rear = rear;
            head->after = nullptr;
            rear = head;
            latter.size_ = size_;
            size_ = 0;
            return latter;
        } else {
            link_node *ptr = head->after;
            int code = 0;
            while (code != index) {
                ptr = ptr->after;
                code++;
            }
            MyList latter;
            latter.head->after = ptr;
            latter.rear = rear;
            //将原有的后半部分截掉
            link_node *rear_now = ptr->before;
            ptr->before = latter.head;
            rear_now->after = nullptr;
            rear = rear_now;
            latter.size_ = size_ - index;
            size_ = index;
            return latter;
        }
    }
};

#include <iostream>

using namespace std;

int main() {

    return 0;
}