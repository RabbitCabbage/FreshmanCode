#include <iostream>
using namespace std;

int main()
{
    int sum = 0, input;
    cout << "Enter numbers: ";
    while (cin >> input)
           sum += input;

    cin.clear();
    char a =cin.get();
    cin >> input;

    cout << "Last value entered = " << input << endl;
    cout << "Sum = " << sum << endl;
    cout <<"a="<<a<<endl;

    return 0;
}