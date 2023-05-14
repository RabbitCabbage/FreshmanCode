//int main() {
//    MyList<string> b;
//    for (int i = 0; i < 5; ++i) {
//        b.push_back("trtrtrtr");
//    }
//    MyList<string> stringA_(b);
//    cout << stringA_.empty() << "string_A" << endl;
//    cout << "sizeof" << b.size() << endl;
//    cout << "sizeofA" << stringA_.size() << endl;
//    b.pop_front();
//    cout << "sizeof" << b.size() << endl;
//    b.pop_back();
//    cout << "sizeof" << b.size() << endl;
//    b.push_back("wewewewe");
//    cout << "sizeof" << b.size() << endl;
//    cout << b.back() << endl;
//    b.push_front("frfrrfrfr");
//    cout << "sizeof" << b.size() << endl;
//    cout << b.front() << endl;
//
//    MyList<int> mylist;
//    for (int i = 1; i <= 10; i++)
//        mylist.push_back(i);
//    cout << "sizeof" << mylist.size() << endl;
//    MyList<int> tmp(move(mylist.cut(5)));
//    cout << "sizeof" << mylist.size() << endl;
//    mylist.link(tmp);
//    cout << "sizeof" << tmp.size() << endl;
//    cout << "sizeof" << mylist.size() << endl;
//    mylist.erase(4);
//    cout << mylist.size() << endl;
//    mylist.link(mylist);
//    cout << mylist.size() << endl;
//    mylist.insert(17, 898989);
//    cout << "17位s" << mylist.back() << endl;
//    mylist.clear();
//    cout << mylist.size();
//    MyList<int> copy(mylist);
//    copy.link(copy);
//    cout << copy.size() << endl;
//    for (int i = 1; i <= 10; i++)
//        mylist.push_back(i);
//    cout << "sizeof" << mylist.size() << endl;
//    MyList<int> latter = mylist.cut(0);
//    cout << latter.size() << endl;
//    cout << mylist.size() << endl;
//    mylist.insert(0, 0);
//    mylist.insert(0, 0);
//    mylist.insert(0, 0);
//    mylist.insert(0, 0);
//    mylist.insert(0, 0);
//    mylist.insert(0, 0);
//    mylist.link(mylist.cut(0));
//    cout<<mylist.size()<<endl;
//#include <Link.h>
#include <iostream>

using namespace std;

int main() {
    MyList<int> a;
    a.push_back(1);
    a.push_back(2);
    cout << a.front() << "\n";
    cout << a.back() << "\n";
    a.push_back(3);
    cout << a.back() << "\n";
    a.push_front(0);
    cout << a.front() << "\n";
    a.insert(2, 5555);

    a.erase(2);
    a.pop_front();
    a.pop_back();
    a.clear();
    a.push_back(1);
    a.push_back(2);
    cout << a.front() << "\n";
    cout << a.back() << "\n";
    a.push_back(3);
    cout << a.back() << "\n";
    a.push_front(0);
    cout << a.front() << "\n";
    a.insert(2, 5);
    a.erase(2);
    a.pop_front();
    a.pop_back();
    MyList<int> b;
    b.push_back(1);
    b.push_back(2);
    b.push_front(-1);
    a.link(b);
    // MyList<int> c(b);

    MyList<int> c(a.cut(2));
    c.push_back(1);
    c.push_back(9);
    MyList<int> d(c.cut(2));
    d.push_back(10);
    c.link(d);
    cout << c.size() << "\n";
    c.clear();
    cout << c.size() << "\n";


//        MyList<int> a;
//        a.push_back(1);
//        a.push_back(2);
//        a.push_back(3);
//        a.push_front(0);
//        a.insert(2,5);
//        a.insert(3,10);
//        a.insert(4,6);
//        a.link(a);
//        MyList<int> b(a.cut(7));
//        MyList<int> c(b.cut(2));
//        a.link(a);
//        a.link(b);
//        a.link(c);
//        c.link(a);
//        MyList<int> d(c.cut(c.size()));
//        a.link(c.cut(8).cut(3));

//    a.link(a);
//    // a.link(b);
//    a.insert(0, 1);
//    a.clear();
//    a.insert(0, 2);
//    a.pop_back();
//    a.insert(0, 8);
//    a.pop_front();
//    a.push_front(8);
//    a.clear();
//    a.push_back(9);
//    a.erase(0);
//    // b.link(a);
//    cout << a.size() << endl;//0
//    a.push_back(1);
//    cout << a.size() << endl;//i
//    a.push_back(8);
//    cout << a.size() << endl;//2
//    a.insert(0, 3);
//    cout << a.size() << endl;//3
//    cout << a.front() << endl;//3
//    a.insert(2, 4);
//    cout << a.size() << endl;//4
//    cout << a.back() << endl;//8
//    a.insert(4, 2);
//    cout << a.back() << endl;//2
//    MyList<int> b(a);
//    cout << b.size() << endl;//5
//    b.link(b);
//    cout << b.size() << endl;//10
//    cout << b.back() << endl;//2
//    MyList<int> c(b.cut(10));
//    cout << "c  size  :" << c.size() << endl;//1
//   // cout << c.front() << " " << c.back() << endl;//2 2
//    cout << "b  size  :" << b.size() << endl;//9
////    cout << b.back() << endl;
////    cout << b.size() << endl;//9
////    b.insert(6, 99);
////    cout << b.back() << endl;//8
////    b.pop_back();
////    cout << b.back() << endl;//4
////    b.pop_back();
////    cout << b.back() << endl;//1
////    b.pop_back();
////    cout << b.back() << endl;//99
////    b.pop_back();




    for (int i = 0; i < 8; i++) {
        a.push_back(i);
    }
    a.insert(8, 999);
    cout << a.back() << endl;

    return 0;
}

MyList<int> mylist;
for (int i = 1; i <= 10; i++)
mylist.push_back(i);
cout << "sizeof" << mylist.size() << endl;
MyList<int> tmp(move(mylist.cut(10)));
tmp.link(tmp);
MyList<int> a, d;
a.insert(0, 1);
a.clear();
a.insert(0, 2);
a.pop_back();
a.insert(0, 8);
a.pop_front();
a.push_front(8);
a.clear();
a.push_back(9);
a.erase(0);

MyList<int> c(a.cut(0));

cout << c.size() << endl;
cout << d.size() << endl;
c.link(d);
c.insert(0, 8);
c.insert(1, 9);
c.erase(1);
//
// Created by lu'ren'jia'd's on 2021/11/21.
//

