//
// Created by lu'ren'jia'd's on 2022/6/1.
//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v;
    cout << "capacity " << v.capacity() << " size " << v.size() << endl;
    v.push_back(1);
    cout << "capacity " << v.capacity() << " size " << v.size() << endl;
    v.push_back(2);
    cout << "capacity " << v.capacity() << " size " << v.size() << endl;
    v.push_back(3);
    cout << "capacity " << v.capacity() << " size " << v.size() << endl;
    v.push_back(2);
    cout << "capacity " << v.capacity() << " size " << v.size() << endl;
    v.push_back(3);
    cout << "capacity " << v.capacity() << " size " << v.size() << endl;
    v.push_back(2);
    cout << "capacity " << v.capacity() << " size " << v.size() << endl;
    v.push_back(3);
    cout << "capacity " << v.capacity() << " size " << v.size() << endl;
    v.resize(5);
    for (auto i = v.begin(); i != v.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
    v.reserve(10000);
    cout << "capacity " << v.capacity() << " size " << v.size() << endl;
    for (auto i = v.begin(); i != v.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
    v.reserve(10);
    cout << "capacity " << v.capacity() << " size " << v.size() << endl;
    return 0;
}