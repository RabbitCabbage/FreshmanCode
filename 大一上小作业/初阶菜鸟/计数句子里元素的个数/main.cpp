#include <iostream>

using namespace std;

int main() {
    cout << "请输入一个句子" << endl;
    char ch;
    int letters = 0, yuanyin = 0, fuyin = 0, numbers = 0, space = 0, biaodian = 1;
    cin.get(ch);
    do {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            if (ch >= 'A' && ch <= 'Z')
                ch = ch - 'A' + 'a';
            if (ch >= 'a' && ch <= 'z')
                ++letters;
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
                ++yuanyin;
            else ++fuyin;
        } else if (ch >= '0' && ch <= '9') ++numbers;
        else if (ch == ' ') ++space;
        else ++biaodian;
        cin.get(ch);

    } while (ch != '.');
    //当while读到.的时候循环结束了，因此标点相当于少算了一个。这里用标点初始值为1.
    cout << "元音字母有" << yuanyin << "个" << endl;
    cout << "辅音字母有" << fuyin << "个" << endl;
    cout << "空格有" << space << "个" << endl;
    cout << "数字有" << numbers << "个" << endl;
    cout << "标点符号有" << biaodian << "个" << endl;
    cout << "字母有" << letters << "个" << endl;
    return 0;
}
