#include <iostream>

using namespace std;
int n;

void result(int *before, int *amid, int *after, int length);

int main() {
    cin >> n;
    int before[n], amid[n], after[n];
    for (int i = 0; i < n; ++i)cin >> before[i];
    for (int i = 0; i < n; ++i)cin >> amid[i];
    result(before, amid, after, n);
    for (int i = 0; i < n; ++i)cout << after[i] << ' ';
    cout << '\n';
    return 0;
}

//now we have a number sequence with the length of "length"
void result(int *before, int *amid, int *after, int length) {
    if (length == 1) {
        after[0] = before[0];
        return;
    }
    int root = *before;//the root;
    after[length - 1] = root;//put the root into the after-array;
    int left_size = 0;
    for (; amid[left_size] != root; ++left_size);
    //now left_size is the size of the left child of the tree;
    //the right part should be dealt with first;
    if (length - left_size - 1 > 0)
        result(before + 1 + left_size, amid + left_size + 1, after + left_size, length - left_size - 1);
    if (left_size > 0)result(before + 1, amid, after, left_size);
}