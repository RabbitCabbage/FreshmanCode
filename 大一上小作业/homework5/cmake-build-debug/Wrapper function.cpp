// "Wrapper": example.cpp
#include <bits/stdc++.h>
#include "src.hpp"
using namespace std;

void foo(string id) { cout << id << endl; }
void before() { cout << "before foo" << endl; }
void after() { cout << "after foo" << endl; }

int main(){
    Wrapper *f = create(foo, before, after);
    run(f, "Hello");
    Wrapper *g = create(foo, after, before);
    run(g, "World!");
    remove(g);
    destroy();
    return 0;
}//
// Created by lu'ren'jia'd's on 2021/11/15.
//

