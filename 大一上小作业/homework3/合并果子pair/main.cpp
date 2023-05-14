/*#include <iostream>
#include<set>

using namespace std;
multiset<int> fruit;

int main() {
    int n;
    long long energy = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        fruit.insert(a);

    }
    while (fruit.size() > 1) {
        multiset<int>::iterator it;
        it = fruit.begin();
        int b = *it, c = *(++it);
        energy += (b + c);
        cout<<(b+c)<<"hhhhhhhhhh"<<energy<<endl;
        fruit.erase(b);
        fruit.erase(c);
        fruit.insert(b + c);
        cout<<fruit.size()<<endl;
    }
    cout << energy << endl;
    return 0;
}*/
/*#include<iostream>
#include<set>

using namespace std;
struct fruit {
    int index;
    int num;
};

bool operator<(const fruit &l, const fruit &r) {
    if (l.num == r.num)
        return l.index < r.index;
    else return l.num < r.num;
}

set<fruit> s;

int main() {
    int n;
    int energy=0;
    cin >> n;
    int index = 0;
    for (int i = 0; i < n; ++i, index++) {
        fruit f{};
        f.index = i;
        cin >> f.num;
        s.insert(f);
    }
    while(s.size()>1) {
        set<fruit>::iterator it;
        it=s.begin();
        fruit f1=*it;
        fruit f2=*(it++);
        fruit f3{index+1 ,f1.num+f2.num};
        index++;
        energy+=(f1.num+f2.num);
        s.erase(f1);
        s.erase(f2);
        s.insert(f3);
    }
    cout<<energy<<endl;
    return 0;
}*/
#include <iostream>
#include<set>

using namespace std;
int n;
set<pair<long long,long long>> s;

int main() {
    long long energy = 0;
    cin >> n;
    pair<long long,long long> p[n];
    int index = 0;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].first;
        p[i].second = index;
        index++;
        s.insert(p[i]);
    }
    while (s.size() > 1) {
        set<pair<long long,long long>>::iterator it;
        it = s.begin();
        pair<long long,long long> p1 = *it;
        s.erase(p1);
        it=s.begin();
        pair<long long,long long> p2 = *it;
        s.erase(p2);
        pair<long long,long long> p3;
        p3.second = ++index;
        p3.first = p1.first + p2.first;
        energy += p1.first + p2.first;
        s.insert(p3);
        //cout<<"  "<<s.size()<<endl;
    }
    cout << energy << endl;
    return 0;
}