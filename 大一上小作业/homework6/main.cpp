#include <iostream>
#include"oj.h"

using namespace std;

int main() {
    ICPCJudger icpc(3, 3, "234234");
    cout << icpc.GetScore() << endl;
    icpc.Submit(4, 5, "234234");
    cout << icpc.GetScore() << endl;
    icpc.Submit(2, 2, "234");
    cout << icpc.GetScore() << endl;
    icpc.Submit(2, 2, "234234");
    cout << icpc.GetScore() << endl;
    icpc.Submit(2, 2, "234");
    cout << icpc.GetScore() << endl;
    OIJudger oi(6, 6, "345345  \n567567  \n");
    oi.Submit(5, 5, "345345\n567567\n");
    cout << oi.GetScore() << endl;
    oi.Submit(5, 5, "345345\n567567\n");
    cout << oi.GetScore() << endl;
    cout << "special judger" << endl;
    SpacialJudger sp(8.0, 8.0, 2.0, 2.0, "1111111");
    sp.Submit(8,8, "1111111");
    cout << sp.GetScore() << endl;
    sp.Submit(5, 5, "1111111");
    cout << sp.GetScore() << endl;
    sp.Submit(2, 2, "1111111");
    cout << sp.GetScore() << endl;

    return 0;
}