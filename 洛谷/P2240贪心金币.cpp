#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;
int pile;

int main() {
    double max_w;
    cin >> pile >> max_w;
    struct gold {
        int m;
        int v;
        double price;

        bool operator<(const gold &r) const { return (price < r.price); }
    };
    gold gold_piles[pile];
    for (int i = 0; i < pile; ++i) {
        cin >> gold_piles[i].m >> gold_piles[i].v;
        gold_piles[i].price =( (double) gold_piles[i].v )/ gold_piles[i].m;
    }
    sort(gold_piles, gold_piles + pile);
//    for(int i=0;i<pile;++i)cout<<gold_piles[i].price<<endl;
    int sum_weight = 0;
    double sum_value = 0;
    while (sum_weight <= max_w && pile >= 0) {
        sum_weight += gold_piles[pile - 1].m;
        sum_value += (double) gold_piles[pile - 1].v;
        pile--;
    }
    if (sum_weight > max_w) {
        sum_weight -= gold_piles[pile].m;
        sum_value -= (double) gold_piles[pile].v;
        sum_value += (max_w - sum_weight) * gold_piles[pile].price;
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << sum_value << endl;
    } else {
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << sum_value << endl;
    }
    return 0;
}